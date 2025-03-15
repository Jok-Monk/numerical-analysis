/*Doolittle法求矩阵的LU分解*/
/*没有检查输入矩阵是否为方阵*/
#pragma once
#include <stdio.h>
#include <math.h>
#include "mat_option.h"



#define DOOLITTLE_DE_BUG 0    // 1 调试该文件 0 取消调试
#if DOOLITTLE_DE_BUG 
#define N 5
#endif

// 输入n*n的矩阵mat，并用doolittle算法分解为LU矩阵，分别存于mat的左下方，右上方
int Doolittle(double *mat, int n);

int Doolittle(double *mat, int n)
{
    for (int k = 0; k < n; k++)
    {
        if (fabs(mat[k * n + k]) < EPSILON)
        {
            printf("ERROR\n");
            return 0;
        }
        //   计算u_kk->u_kn
        //   计算l_(k+1)k->l_nk
        for (int j = 0; j < k; j++)
        {
            mat[k * n + k] -= mat[k * n + j] * mat[j * n + k];
            for (int i = k + 1; i < n; i++)
            {
                mat[k * n + i] -= mat[k * n + j] * mat[j * n + i];
                mat[i * n + k] -= mat[i * n + j] * mat[j * n + k];
            }
        }
        for (int i = k + 1; i < n; i++)
        {
            mat[i * n + k] /= mat[k * n + k];
        }
    }
    return 1;
}



#if DE_BUG
// p27 算例

int main()
{
    double A[N * N] = {0.288, 1.04, 0.8992, 0.3008, 0.0592,
                       0.148, 0.288, 0.576, 0.266, 0.064,
                       0.256, 0.2368, 0.16, 0.064, 0.016,
                       0.064, 0.4096, 0.2048, 0.032, 0,
                       0, 0.064, 0.256, 0.128, 0.032};
    Doolittle(A, N);
    mat_print(A, N, N);
    return 0;
}
#endif
