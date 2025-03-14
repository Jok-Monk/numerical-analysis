/*三对角矩阵的追赶法*/
// 求解方程:
// Ax=b, 其中
// A = e_0 f_0                          ... 0
//     d_0 e_1 f_1                      ... 0
//     0   d_1 e_2 f_2                  ...
//          ...                 ...
//                  d_(n-3) e_(n-2) f_(n-2)
//     0                    d_(n-2) e_(n-1)
// 为n*n方阵
// step 1 将A做LU分解:
// L = 1                    ...     0
//     l_0  1               ...
//     0    l_1  1          ...
//          0    l_2  1     ...
//          ...
//     0                l_(n-1)  1
//
// U = r_0 f_0                      0
//         r_1 f_1
//             r_2 f_2
//                  ...
//                     r_(n-2) f_(n-2)
//                             r_(n-1)
// 结果l,r分别储存于d,e中
// step 2 分别解方程: Ly=b Ux=y

#pragma once
#include <stdio.h>
#include <math.h>
#include "mat_option.h"
#define EPSILON 1e-10

#define SOLVELOWERTRIANGULAR_DE_BUG 0 // 1 调试该文件 0 取消调试
#if SOLVELOWERTRIANGULAR_DE_BUG
#define N 4
#endif

// f:(n-1)*1 e:n*1 d:(n-1)*1 b:n*1 choose=1则解方程,choose=0则仅作LU分解(不改变b)
int solveLowerTriangular(double *upl, double *ml, double *lowl, double *b, int n, int choose);

int solveLowerTriangular(double *f, double *e, double *d, double *b, int n,int choose)
{
    // LU分解(Doolittle算法)
    for (int i = 0; i < n - 1; i++)
    {
        if (fabs(e[i]) < EPSILON)
        {
            printf("ERROR\n");
            return 0;
        }
        d[i] /= e[i];
        e[i + 1] -= d[i] * f[i];
    }
    if (choose==0)
    {
        return 1;
    }
    
    // Ly=b , 结果y储存在b中
    for (int i = 1; i < n; i++)
    {
        b[i] -= d[i - 1] * b[i - 1];
    }
    // Ux=y , 结果x储存在b中
    if (fabs(e[n - 1]) < EPSILON)
    {
        printf("ERROR\n");
        return 0;
    }
    b[n-1]/=e[n-1];
    for (int i = n - 2; i >= 0; i--)
    {
        if (fabs(e[i]) < EPSILON)
        {
            printf("ERROR\n");
            return 0;
        }
        b[i]-=f[i]*b[i+1];
        b[i]/=e[i];
    }
    return 1;
}

/*测试样例*/
#if SOLVELOWERTRIANGULAR_DE_BUG
int main() 
{
    double f[N-1]={-1,-1,-1};
    double e[N]={2,2,2,2};
    double d[N-1]={-1,-1,-1};
    double b[N]={0,0,0,5};
    solveLowerTriangular(f,e,d,b,N,1);
    /* for (int i = 0; i < N-1; i++)
    {
        printf("f[%d]:%f\n",i,f[i]);
    }
    for (int i = 0; i < N; i++)
    {
        printf("e[%d]:%f\n",i,e[i]);
    }
    for (int i = 0; i < N-1; i++)
    {
        printf("d[%d]:%f\n",i,d[i]);
    } */
   mat_print(b,N,1);
    return 0;
}
#endif