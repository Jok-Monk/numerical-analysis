/*上三角方程求解*/
#ifndef UPPER_TRIANGLE_LINEAR_SYSTEM_H
#define UPPER_TRIANGLE_LINEAR_SYSTEM_H

#include <stdio.h>
#include <math.h>
#define EPSILON 1e-10
//#define N 3
int upper_triangle_linear_system(double *U, double *x, double *b, int n);    //U[n][n],x[n],b[n]


int upper_triangle_linear_system(double *U, double *x, double *b, int n)    //U[n][n],x[n],b[n]
{
    //不检查U是否为上三角
    for (int i = n - 1; i >= 0; i--)
    {
        if (fabs(U[i * n + i]) < EPSILON) // 判断是否为奇异矩阵
        {
            printf("The matrix is singular\n");
            return 0;
        }

        double sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            sum += U[i * n + j] * x[j];
        }
        x[i] = (b[i] - sum) / U[i * n + i];
    }
    return 1;
}

/* int main()
{
    int const rows = N, cols = N;                          // 上三角矩阵的行数和列数
    double mat[N * N] = {1, 2, 3, 0, 4, 5, 0, 0, 6}; // 上三角矩阵 测试样例
    double x[rows];                                        // 解向量
    double b[N] = {1, 2, 3};                               // 右端向量 测试样例
    upper_triangle_linear_system(mat, x, b, rows);
    for (int i = 0; i < N; i++)
    {
        printf("x[%d]=%f\n", i, x[i]);
    }

    return 0;
} */

#endif // UPPER_TRIANGLE_LINEAR_SYSTEM_H