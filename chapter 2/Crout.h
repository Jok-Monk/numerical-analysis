#pragma once
#include <stdio.h>
#include <math.h>
#include "mat_option.h"

#define EPSILON 1e-10

#define CROUT_DE_BUG 0    // 1 调试该文件 0 取消调试
#if CROUT_DE_BUG 
#define N 5
#endif

int Crout(double *mat, int n);

int Crout(double *mat, int n)
{
    if (fabs(mat[0]) < EPSILON)
    {
        printf("ERROR\n");
        return 0;
    }

    for (int i = 1; i < n; i++)
    {
        mat[i] /= mat[0];
    }

    for (int k = 1; k < n; k++)
    {
        if (fabs(mat[k * n + k]) < EPSILON)
        {
            printf("ERROR\n");
            return 0;
        }
        for (int j = 0; j < k; j++)
        {
            mat[k * n + k] -= mat[j * n + k] * mat[k * n + j];
            for (int i = k + 1; i < n; i++)
            {
                mat[i * n + k] -= mat[j * n + k] * mat[i * n + j];
                mat[k * n + i] -= mat[j * n + i] * mat[k * n + j];
                if (j == k - 1)
                {
                    mat[k * n + i] /= mat[k * n + k];
                }
            }
        }
    }
    return 1;
}

#if CROUT_DE_BUG
int main()
{
    double A[N * N] = {0.288, 0.148,0.256,0.064,0,
                       1.04,0.288,0.2368,0.4096,0.064,
                       0.8992,0.576,0.16,0.2048,0.256,
                       0.3008,0.266,0.064,0.032,0.128,
                       0.0592,0.064,0.016,0,0.032};
    Crout(A, N);
    mat_print(A, N, N);
    return 0;
}
#endif