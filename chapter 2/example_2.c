// 应用实例
// LU分解法求方程组：
// 0.288  1.04    0.8992  0.3008  0.0592   = 598
// 0.148  0.288   0.576   0.266   0.064    = 288
// 0.256  0.2368  0.16    0.064   0.016    = 222
// 0.064  0.4096  0.2048  0.032   0        = 170
// 0,     0.064   0.256   0.128   0.032    = 82
#include <stdio.h>
#include <math.h>
#include "solve_upper_triangle.h"
#include "solve_lower_triangle.h"
#include "Doolittle.h"
#include "mat_option.h"
#define N 5
int main()
{
    double A[N * N] = {0.288, 1.04, 0.8992, 0.3008, 0.0592,
                       0.148, 0.288, 0.576, 0.266, 0.064,
                       0.256, 0.2368, 0.16, 0.064, 0.016,
                       0.064, 0.4096, 0.2048, 0.032, 0,
                       0, 0.064, 0.256, 0.128, 0.032};
    double b[N] = {598, 288, 222, 170, 82};
    // 用Doolitt算法得到LU分解: A=LU
    Doolittle(A,N);
    // L储存在A中，但是主对角线被U覆盖，无法直接调用solve_lower_triangle 需重新赋值
    double L[N*N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            L[i*N+j]=A[i*N+j];
        }
        L[i*N+i]=1;
    }
    // 求解Ly=b,结果y储存在b中
    solve_lower_triangle(L,b,N);
    // 求解Ux=y(b),结果储存在b中
    solve_upper_triangle(A,b,N);
    // 输出结果
    mat_print(b,N,1);
    return 0;
}