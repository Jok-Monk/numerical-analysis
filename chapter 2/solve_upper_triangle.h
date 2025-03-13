/*上三角方程求解*/
#ifndef SOLVE_UPPER_TRIANGLE_H
#define SOLVE_UPPER_TRIANGLE_H

#include <stdio.h>
#include <math.h>
#include"mat_option.h"
#define EPSILON 1e-10

#define SOLVE_UPPER_TRIANGLE_DE_BUG 0    // 1 调试该文件 0 取消调试
#if SOLVE_UPPER_TRIANGLE_DE_BUG
#define N 3
#endif
int solve_upper_triangle(double *U, double *b, int n);    //U[n][n],x[n],b[n],计算结果储存在b中


int solve_upper_triangle(double *U, double *b, int n)    //U[n][n],x[n],b[n]
{
    //不检查U是否为上三角
    for (int j = n - 1; j >= 0; j--)
    {
        if (fabs(U[j * n + j]) < EPSILON) // 判断是否为奇异矩阵
        {
            printf("The matrix is singular\n");
            return 0;
        }
        b[j]/=U[j*n+j];
        for (int i = 0; i < j; i++)
        {
            b[i]-=U[i*n+j]*b[j];
        }
    }
    return 1;
}

/*测试样例*/
#if SOLVE_UPPER_TRIANGLE_DE_BUG
int main()
{
    double mat[N * N] = {1, 2, 3, 0, 4, 5, 0, 0, 6}; // 上三角矩阵 测试样例
    double b[N] = {1, 2, 3};                               // 右端向量 测试样例
    solve_upper_triangle(mat, b, N);
    mat_print(b,N,1);

    return 0;
}
#endif
#endif 