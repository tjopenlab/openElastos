/*
 * kun/mm/slab.c
 *
 * Author:  Zheng Kun
 * Date:    2006.3
 *
 */

#include <kun/mm.h>
#include <kun/list.h>
#include <kun/misc.h>
#include <kun/align.h>
#include <kun/sizes.h>
#include <arch/cache.h>
#include <arch/paging.h>
#include <arch/interrupt.h>

struct mutex
{
};

#define mutex_init(x)
#define mutex_lock(x)
#define mutex_unlock(x)

struct spinlock
{
};

#define spinlock_init(x)
#define spinlock_lock(x)
#define spinlock_unlock(x)

#ifndef ARCH_KMALLOC_MINALIGN
#define ARCH_KMALLOC_MINALIGN   L1_CACHE_BYTES
#endif

#define BREAK_ALLOC_ORDER_HI 1
#define BREAK_ALLOC_ORDER_LO 0

typedef unsigned int mem_bufctl;

#define BUFCTL_END  (((mem_bufctl)(~0U))-0)
#define BUFCTL_FREE (((mem_bufctl)(~0U))-1)
#define SLAB_LIMIT  (((mem_bufctl)(~0U))-2)

struct slab
{
    list_node       list;
    unsigned long   color_off;
    void*           mem;
    unsigned int    inuse;
    mem_bufctl      free;
};

#define slab_bufctl(sl) ((mem_bufctl*)((struct slab*)(sl) + 1))

struct mem_list
{
    list_node   free_slabs;
    list_node   partial_slabs;
    list_node   full_slabs;

    ulong       free_objects;
};

struct mem_cache
{
    /* 1) touched by every alloc/free from the backend */
    struct mem_list     lists;
    unsigned int        objsize;
    unsigned int        flags;
    unsigned int        num;
    unsigned int        free_limit;
    struct spinlock     spinlock;

    /* 2) cache grow/shrink */
    unsigned int        alloc_order;
    unsigned int        alloc_flags;

    size_t              color;
    unsigned int        color_off;
    unsigned int        color_next;
    mem_cache*          slab_cache;
    unsigned int        slab_size;

    /* 3) cache creation/removal */
    list_node           next;
};

struct cache_sizes
{
    size_t      size;
    mem_cache*  cache;
    mem_cache*  dma_cache;
};

struct cache_sizes kmalloc_sizes[] = {
#define SLAB_CACHE(x) { x, 0, 0 },
#include "kmalloc_sizes.h"
#undef SLAB_CACHE
    { 0, 0, 0 }
};

static mem_cache        cache_cache;
static int              slab_break_alloc_order = BREAK_ALLOC_ORDER_LO;
static unsigned long    off_slab_limit;
static struct mutex     cache_chain_mutex;
static list_node        cache_chain;

static void __fastcall
mem_list_init (struct mem_list* ml)
{
    list_init (&ml->free_slabs);
    list_init (&ml->partial_slabs);
    list_init (&ml->full_slabs);
    ml->free_objects = 0;
}

inline void
set_slab_attr (mem_cache* cache, struct slab* slab, void* obj)
{
    set_page_slab (VA_PAGE(obj), cache, slab);
}

inline struct slab*
get_obj_slab (void* obj)
{
    return get_page_slab (VA_PAGE (obj));
}

inline mem_cache*
get_obj_cache (void* obj)
{
    return get_page_cache (VA_PAGE (obj));
}

inline boolean
is_off_slab (mem_cache* cache)
{
    return cache->flags & SLAB_OFFSLAB;
}

inline void*
get_pages (mem_cache* cache)
{
    void* addr;

    addr = allocate_kernel_pages (cache->alloc_order, cache->alloc_flags);

    return addr;
}

inline void
release_pages (mem_cache* cache, void* addr)
{
    if (addr)
        free_kernel_pages (addr, cache->alloc_order);
}

static struct slab* __fastcall
alloc_slab_management (mem_cache* cache, void* obj,
                       int color_off, boolean nogrow)
{
    struct slab* slab;

    if (is_off_slab (cache))
    {
        /* slab management obj is off-slab */
        slab = (struct slab*)mem_cache_alloc (cache->slab_cache, nogrow);
        if (slab == NULL)
            return NULL;
    }
    else
    {
        slab = (struct slab*)((char*)obj + color_off);
        color_off += cache->slab_size;
    }
    slab->inuse = 0;
    slab->color_off = color_off;
    slab->mem = (char*)obj + color_off;

    return slab;
}

static void __fastcall
init_objs (mem_cache* cache, struct slab* slab)
{
    int i;

    for (i = 0; i < cache->num; ++i)
    {
        void* obj = (char*)slab->mem + cache->objsize * i;
        slab_bufctl(slab) [i] = i + 1;
    }
    slab_bufctl(slab) [i-1] = BUFCTL_END;
    slab->free = 0;
}

/*
 * grow the number of slabs within a cache. This is called by
 * mem_cache_alloc () when there are no active objs left in a cache.
 */
static boolean __fastcall
grow_cache (mem_cache* cache, boolean nogrow)
{
    struct slab* slab;
    void* obj;
    size_t offset;

    /* Be lazy and only check for valid flags here,
     * keeping it out of the critical path in Alloc().
     */
    if (nogrow)
        return FALSE;

    check_irq_off ();
    spinlock_lock (&cache->spinlock);

    /* get color for the slab, and calc the next value */
    offset = cache->color_next;
    cache->color_next++;
    if (cache->color_next >= cache->color)
        cache->color_next = 0;
    offset *= cache->color_off;

    spinlock_unlock (&cache->spinlock);

    /* get mem for the objs */
    obj = get_pages (cache);
    if (obj == NULL)
        goto L_FAIL;

    /* get slab management */
    slab = alloc_slab_management (cache, obj, offset, nogrow);
    if (slab == NULL)
        goto L_OPPS1;

    set_slab_attr (cache, slab, obj);
    init_objs (cache, slab);

    check_irq_off ();
    spinlock_lock (&cache->spinlock);

    /* make slab active */
    list_append (&cache->lists.free_slabs, &slab->list);
    cache->lists.free_objects += cache->num;
    spinlock_unlock (&cache->spinlock);
    return TRUE;

L_OPPS1:
    release_pages (cache, obj);

L_FAIL:
    return FALSE;
}

static void* __fastcall
alloc__ (mem_cache* cache, boolean nogrow)
{
    ulong save_flags;
    void* obj;
    struct slab* slab;
    struct mem_list* l3;
    list_node* entry;

    l3 = &cache->lists;

L_RETRY:
    save_flags = disable_interrupt ();
    entry = list_first (&l3->partial_slabs);
    if (entry == &l3->partial_slabs)
    {
        entry = list_first (&l3->free_slabs);
        if (entry == &l3->free_slabs)
            goto L_MUST_GROW;
    }
    slab = list_node_entry (entry, struct slab, list);
    list_node_detach (&slab->list);
    ++slab->inuse;
    obj = slab->mem + slab->free * cache->objsize;
    slab->free = slab_bufctl(slab)[slab->free];

    if (slab->free == BUFCTL_END)
    {
        /* slab now full: move slab to full list */
        list_insert_first (&l3->full_slabs, &slab->list);
    }
    else
    {
        list_insert_first (&l3->partial_slabs, &slab->list);
    }

    restore_interrupt (save_flags);
    return obj;

L_MUST_GROW:
    if (grow_cache (cache, nogrow))
        goto L_RETRY;
    restore_interrupt (save_flags);
    return NULL;
}

static void __fastcall
destroy_slab (mem_cache* cache, struct slab* slab)
{
    release_pages (cache, (char*)slab->mem - slab->color_off);
    if (is_off_slab (cache))
    {
        mem_cache_free (cache->slab_cache, slab);
    }
}

static void __fastcall
free__ (mem_cache* cache, void* obj)
{
    struct slab* slab;
    unsigned int n;
    struct mem_list* l3;

    check_irq_off ();

    l3 = &cache->lists;
    l3->free_objects++;

    slab = get_obj_slab (obj);
    list_node_detach (&slab->list);
    n = ((char*)obj - (char*)slab->mem) / cache->objsize;
    slab_bufctl (slab)[n] = slab->free;
    slab->free = n;
    slab->inuse--;

    /* fixup slab chains */
    if (slab->inuse == 0)
    {
        if (l3->free_objects > cache->free_limit)
        {
            l3->free_objects -= cache->num;
            destroy_slab (cache, slab);
        }
        else
        {
            list_insert_first (&l3->free_slabs, &slab->list);
        }
    }
    else
    {
        /* Unconditionlly move a slab to the end of the
         * partial list on free - maximum time for the
         * other objects to be freed, too.
         */
        list_append (&l3->partial_slabs, &slab->list);
    }
}

static void __fastcall
estimate (ulong alloc_order, size_t size, size_t align,
          int flags, size_t* left_over, uint* num)
{
    int i;
    size_t wastage = PAGE_SIZE << alloc_order;
    size_t extra = 0;
    size_t base = 0;

    if (!(flags & SLAB_OFFSLAB))
    {
        base = sizeof (struct slab);
        extra = sizeof (mem_bufctl);
    }
    i = 0;
    while (i * size + ALIGN(base + i * extra, align) <= wastage)
        ++i;
    if (i > 0)
        --i;

    if (i > SLAB_LIMIT)
        i = SLAB_LIMIT;

    *num = i;
    wastage -= i * size;
    wastage -= ALIGN (base + i * extra, align);
    *left_over = wastage;
}

static mem_cache* __fastcall
find_general_cache (size_t size, int alloc_flags)
{
    struct cache_sizes* csize = kmalloc_sizes;

    /* This function could be moved to the header file, and
     * made inline so consumers can quickly determine what
     * cache pointer they require.
     */
    for (; csize->size; ++csize)
    {
        if (size > csize->size)
            continue;
        break;
    }
    return (alloc_flags & ALLOC_DMA) ? csize->dma_cache : csize->cache;
}

static boolean __fastcall
shrink (mem_cache* cache)
{
    struct slab* slab;
    int ret;

    check_irq_on ();
    spinlock_lock (&cache->spinlock);

    for (;;)
    {
        list_node* p;

        p = list_last (&cache->lists.free_slabs);
        if (p == &cache->lists.free_slabs)
            break;

        slab = list_node_entry (p, struct slab, list);
        list_node_detach (&slab->list);

        cache->lists.free_objects -= cache->num;
        spinlock_unlock (&cache->spinlock);
        destroy_slab (cache, slab);
        spinlock_lock (&cache->spinlock);
    }
    ret = list_empty (&cache->lists.full_slabs)
        && list_empty (&cache->lists.partial_slabs);

    spinlock_unlock (&cache->spinlock);
    return ret;
}

EXTERN_C void __stdcall
init_mem_cache (void)
{
    size_t left_over;
    struct cache_sizes* sizes;

    /*
     * initialize cache_cache
     */

    mem_list_init (&cache_cache.lists);
    cache_cache.objsize = ALIGN (sizeof (mem_cache), get_cache_line_size ());
    cache_cache.flags = SLAB_NOREAP;
    cache_cache.free_limit = 0;
    spinlock_init (&cache_cache.spinlock);
    cache_cache.alloc_order = 0;
    cache_cache.alloc_flags = ALLOC_KERNEL;
    cache_cache.color_off = get_cache_line_size ();
    cache_cache.slab_cache = &cache_cache;
    estimate (0, cache_cache.objsize, get_cache_line_size (),
        cache_cache.flags, &left_over, &cache_cache.num);
    if (cache_cache.num == 0)
        BUG ();
    cache_cache.color = left_over / cache_cache.color_off;
    cache_cache.color_next = 0;
    cache_cache.slab_size = ALIGN (cache_cache.num * sizeof (mem_bufctl)
        + sizeof (struct slab), get_cache_line_size ());

    mutex_init (&cache_chain_mutex);
    list_init (&cache_chain);
    list_insert_first (&cache_chain, &cache_cache.next);

    /*
     * Fragmentation resistance on low memory - only use bigger
     * page orders on machines with more than 32MB of memory.
     */
    if (max_pfn > (SZ_32M >> PAGE_SHIFT))
        slab_break_alloc_order = BREAK_ALLOC_ORDER_HI;

    /*
     * initialize kmalloc cache
     */

    sizes = kmalloc_sizes;
    while (sizes->size)
    {
        /* For performance, all the general caches are L1 aligned.
         * This should be particularly beneficial on SMP boxes, as it
         * eliminates "false sharing".
         * Note for systems short on memory removing the alignment will
         * allow tighter packing of the smaller caches. */
        sizes->cache = mem_cache_create (sizes->size,
            ARCH_KMALLOC_MINALIGN, SLAB_PANIC);

        /* Inc off-slab bufctl limit until the ceiling is hit */
        if (!is_off_slab (sizes->cache))
        {
            off_slab_limit = sizes->size - sizeof (struct slab);
            off_slab_limit /= sizeof (mem_bufctl);
        }

        sizes->dma_cache = mem_cache_create (sizes->size,
            ARCH_KMALLOC_MINALIGN, SLAB_CACHE_DMA | SLAB_PANIC);

        ++sizes;
    }
}

EXTERN_C mem_cache* __stdcall
mem_cache_create (size_t obj_size, size_t align, uint flags)
{
    size_t left_over, slab_size;
    mem_cache* cache = NULL;
 
    /*
     * sanity checks... these are all serious usage bugs
     */
    if (in_interrupt ()
      || (obj_size < BYTES_PER_WORD)
      || (obj_size > (1 << MAX_ORDER) * PAGE_SIZE)
      || (align < 0))
    {
        print_string (L"mem_cache_create: early error in slab\n");
        BUG ();
    }

    /*
     * Always checks flags, a caller might be expecting debug
     * support which isn't available.
     */
    if (flags & ~SLAB_CREATE_MASK)
        BUG ();

    if (align)
    {
        /* combinations of forced alignment and advanced debugging is
         * not yet implemented.
         */
        flags &= ~(SLAB_REDZONE | SLAB_STORE_USER);
    }
    else
    {
        if (flags & SLAB_HWCACHE_ALIGN)
        {
            /* Default alignment: as specified by the arch code.
             * Except if an object is really small, then squeeze multiple
             * into one cacheline.
             */
             align = get_cache_line_size ();
             while (obj_size <= align / 2)
                align /= 2;
        }
        else
        {
            align = BYTES_PER_WORD;
        }
    }

    /* get cache's description obj */
    cache = (mem_cache*)mem_cache_alloc (&cache_cache, FALSE);
    if (cache == NULL)
        goto L_OPPS;
    set (cache, 0, sizeof (mem_cache));
    mem_list_init (&cache->lists);

    /* Check that size is in terms of words.  This is needed to avoid
     * unaligned accesses for some archs when redzoning is used, and makes
     * sure any on-slab bufctl's are also correctly aligned.
     */
    if (obj_size & (BYTES_PER_WORD - 1))
    {
       obj_size = DATA_ALIGN (obj_size);
    }

    /* determine if the slab management is 'on' or 'off' slab */
    if (obj_size >= (PAGE_SIZE>>3))
    {
       /*
        * Size is large, assume best to place the slab management obj
        * off-slab (should allow better packing of objs).
        */
        flags |= SLAB_OFFSLAB;
    }

    obj_size = ALIGN (obj_size, align);

    if ((flags & SLAB_RECLAIM_ACCOUNT) && obj_size <= PAGE_SIZE)
    {
        /*
         * A VFS-reclaimable slab tends to have most allocations
         * as GFP_NOFS and we really don't want to have to be allocating
         * higher-order pages when we are unable to shrink dcache.
         */
        cache->alloc_order = 0;
        estimate (cache->alloc_order, obj_size, align, flags,
            &left_over, &cache->num);
    }
    else
    {
        /*
         * Calculate obj_size (in pages) of slabs, and the num of objs per
         * slab.  This could be made much more intelligent.  For now,
         * try to avoid using high page-orders for slabs.  When the
         * alloc_pages() funcs are more friendly towards high-order requests,
         * this should be changed.
         */
        do {
            unsigned int break_flag = 0;
L_CAL_WASTAGE:
            estimate(cache->alloc_order, obj_size, align, flags,
                        &left_over, &cache->num);
            if (break_flag)
                break;
            if (cache->alloc_order >= MAX_ORDER)
                break;
            if (cache->num == 0)
                goto L_NEXT;
            if ((flags & SLAB_OFFSLAB)
              && cache->num > off_slab_limit) {
                /* This num of objs will cause problems. */
                cache->alloc_order--;
                break_flag++;
                goto L_CAL_WASTAGE;
            }

            /*
             * Large num of objs is good, but v. large slabs are
             * currently bad for the gfp()s.
             */
            if (cache->alloc_order >= slab_break_alloc_order)
                break;

            if ((left_over*8) <= (PAGE_SIZE<<cache->alloc_order))
                break;    /* Acceptable internal fragmentation. */
L_NEXT:
            cache->alloc_order++;
        } while (1);
    }

    if (cache->num == 0)
    {
        print_string (L"mem_cache_create: couldn't create cache.\n");
        mem_cache_free (&cache_cache, cache);
        cache = NULL;
        goto L_OPPS;
    }
    slab_size = ALIGN(cache->num*sizeof(mem_bufctl)
        + sizeof(struct slab), align);

    /*
     * If the slab has been placed off-slab, and we have enough space then
     * move it on-slab. This is at the expense of any extra coloring.
     */
    if ((flags & SLAB_OFFSLAB) && (left_over >= slab_size))
    {
        flags &= ~SLAB_OFFSLAB;
        left_over -= slab_size;
    }

    if (flags & SLAB_OFFSLAB)
    {
        /* really off slab. No need for manual alignment */
        slab_size = cache->num*sizeof(mem_bufctl)+sizeof(struct slab);
    }

    cache->color_off = get_cache_line_size();
    /* Offset must be a multiple of the alignment. */
    if (cache->color_off < align)
        cache->color_off = align;
    cache->color = left_over / cache->color_off;
    cache->slab_size = slab_size;
    cache->flags = flags;
    cache->alloc_flags = ALLOC_KERNEL;
    if (flags & SLAB_CACHE_DMA)
        cache->alloc_flags = ALLOC_DMA;
    spinlock_init (&cache->spinlock);
    cache->objsize = obj_size;

    if (flags & SLAB_OFFSLAB)
        cache->slab_cache = find_general_cache (slab_size, ALLOC_KERNEL);

    mutex_lock (&cache_chain_mutex);

    /* cache setup completed, link it into the list */
    list_insert_first (&cache_chain, &cache->next);
    mutex_unlock (&cache_chain_mutex);

L_OPPS:
    if (cache == NULL && (flags & SLAB_PANIC))
        panic(L"mem_cache_create (): failed to create slab\n");
    return cache;
}

EXTERN_C boolean __stdcall
mem_cache_destroy (mem_cache* cache)
{
    if (in_interrupt ())
        BUG ();

    /* find the cache in the chain of caches */
    mutex_lock (&cache_chain_mutex);
    /*
     * the chain is never empty, cache_cache is never destroyed
     */
    list_node_detach (&cache->next);
    mutex_unlock (&cache_chain_mutex);

    if (!shrink (cache))
    {
        print_string (L"slab: can't free all objects");
        mutex_lock (&cache_chain_mutex);
        list_insert_first (&cache_chain, &cache->next);
        mutex_unlock (&cache_chain_mutex);
        return FALSE;
    }

    mem_cache_free (&cache_cache, cache);
    
    return TRUE;
}

EXTERN_C void* __stdcall
mem_cache_alloc (mem_cache* cache, boolean nogrow)
{
    return alloc__ (cache, nogrow);
}

EXTERN_C void __stdcall
mem_cache_free (mem_cache* cache, void* obj)
{
    ulong save_flags;

    save_flags = disable_interrupt ();
    free__ (cache, obj);
    restore_interrupt (save_flags);
}

EXTERN_C void* __stdcall
kmalloc (size_t size, uint flags)
{
    int i;
    mem_cache* cache;

    if (size == 0)
        return NULL;

#define SLAB_CACHE(x) \
    if (size <= x) \
        goto L_FOUND;
    else \
        ++i;
#include "kmalloc_sizes.h"
#undef SLAB_CACHE
    {
        panic (L"cannot kmalloc that much");
    }
L_FOUND:
    cache = (flags & ALLOC_DMA) ? kmalloc_sizes[i].dma_cache
        : kmalloc_sizes[i].cache;
 
    return mem_cache_alloc (cache, FALSE);
}

EXTERN_C void __stdcall
kfree (void* obj)
{
    mem_cache* cache;
    unsigned long save_flags;

    if (obj == NULL)
        return;

    save_flags = disable_interrupt ();
    cache = get_obj_cache (obj);
    free__ (cache, obj);
    restore_interrupt (save_flags);
}
