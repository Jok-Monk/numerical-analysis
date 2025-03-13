/*一般高斯消去法 同时存储LU矩阵*/
#ifndef GAUSS_LU_H
#define GAUSS_LU_H
#include <stdio.h>
#include <math.h>
#define EPSILON 1e-10

#define GAUSS_LU_DE_BUG 0    // 1 调试该文件 0 取消调试
#if GAUSS_LU_DE_BUG 
#define N 3
#endif
int gauss(double *mat, double *b, int n); // mat[n][n],b[n],将增广矩阵(mat,b)化为上三角矩阵 左下角为LU分解的L矩阵

int gauss(double *mat, double *b, int n) // mat[n][n],b[n],将增广矩阵(mat,b)化为上三角矩阵
{
    for (int i = 0; i < n - 1; i++) // 用第i行进行消元
    {
        if (fabs(mat[i * n + i]) < EPSILON) // 判断主元是否为0
        {
            printf("The matrix is singular\n");
            return 0;
        }
        for (int j = i + 1; j < n; j++)
        {
            mat[j * n + i] /= mat[i * n + i]; // 将消去系数储存在mat的左下角 即L
            for (int k = i + 1; k < n; k++)   // 用第i行消去第j行
            {
                mat[j * n + k] -= mat[j * n + i] * mat[i * n + k];
            }
            b[j] -= mat[j * n + i] * b[i];
        }

    }
    return 1;
}
/*测试*/
#if GAUSS_LU_DE_BUG
int main()
{
    double A[N * N] = {1, 1, -1, 2, -1, 3, -1, -2, 1}; // 3*3矩阵测试样例
    double b[N] = {3, 0, -5};                          // 3*1矩阵测试样例
    if (gauss(A, b, N))
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = i; j < N; j++)
            {
                printf("%lf ", A[i * N + j]);
            }
            printf("    %lf\n",b[i]);
        }
    }
    else
    {
        printf("ERROR");
    }
    return 0;
} 
#endif
#endif