#include <windows.h>
#include <stdio.h>

int BatCap[11][3] = {
    {4090, 10, 4},//90%
    {4002,  9, 4},//80%
    {3942,  8, 4},//70%
    {3880,  7, 3},//60%
    {3821,  6, 3},//50%
    {3791,  5, 3},//40%
    {3767,  4, 2},//30%
    {3734,  3, 2},//20%
    {3680,  2, 1},//10%
    {3661,  1, 1},//5%
    {3495,  0, 0},//1%
};

int per(int mv)
{
    int i;
    for(i = 0; i < 10; i++) {
        if (mv > BatCap[i+1][0]) break;
    }
    return BatCap[i][1];
}

int level(int v)
{
    int i;
    for(i = 0; i < 10; i++) {
        if (v >= BatCap[i][1]) break;
    }
    return BatCap[i][2];
}

int v = 0;
int u = 1;
double eu=0, ev=0, eu2=0, ev2=0, euv=0;
double beta = 0, alpha = 0;

void BatInput(int mv)
{
    v = per(mv);

    eu += u;
    eu2 += u * u;
    ev += v;
    euv += u * v;
    u++;
}

int BatOutput(int mv)
{
    int n = u - 1;
    beta = (n * euv - eu * ev) / (n * eu2 - eu * eu);
    alpha = ev / n - beta * eu / n;

    if (mv == 0) {
        printf("n %.4f\teu %.4f, eu2 %.4f,\t ev %.4f, euv %.4f \n", (double)n, eu, eu2, ev, euv);
        printf("beta %.4f, alpha %.4f\n", beta, alpha);
    }

    double t = beta * u + alpha;
    int j = (int)(t + 0.5);
    printf("---%05d---\t%d\t(%2d)\t---\t%2d (%d)\t\t%.2f%%\n", u, mv, v, j, level(j), t*10);
    return (int)(t*10);
}

void BatInit(int mv)
{
    u = 1;eu = ev = eu2 = euv = 0;
    beta  = 0; alpha = 0;

    BatInput(mv);
}

int z3[50000];
void test()
{
    int n = 1;
    int i;
    for(n = 1; n <= 50000; n++) {
        int dd = 0;
        scanf("%d", &dd);
        if (dd == 0) break;
        z3[n] = dd;
        //printf("%5.0f\t%d\n", z3[n], percent((int)z3[n]));
        //z3[n] = percent((int)z3[n]);
    }
    n--;
    printf("n = %d\n", n);
//    return ;

    BatInit(z3[1]);
    BatInput(z3[2]);

    for(i = 3; i <= n; i++) {
        BatInput(z3[i]);
        BatOutput(z3[i]);
    }
}

int __cdecl main()
{
    test();
    return 0;
}
