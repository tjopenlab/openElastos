/*
 * kun/mm/slab_sizes.h
 *
 * Author:  Zheng Kun
 * Date:    2006.3
 *
 */

#if (PAGE_SIZE == 4096)
    SLAB_CACHE(32)
#endif
    SLAB_CACHE(64)
#if L1_CACHE_BYTES < 64
    SLAB_CACHE(96)
#endif
    SLAB_CACHE(128)
#if L1_CACHE_BYTES < 128
    SLAB_CACHE(192)
#endif
    SLAB_CACHE(256)
    SLAB_CACHE(512)
    SLAB_CACHE(1024)
    SLAB_CACHE(2048)
    SLAB_CACHE(4096)
    SLAB_CACHE(8192)
    SLAB_CACHE(16384)
    SLAB_CACHE(32768)
    SLAB_CACHE(65536)
    SLAB_CACHE(131072)
