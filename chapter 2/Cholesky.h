/*计算对称正定矩阵的Cholesky分解*/
/*结果存储于原矩阵的右下方*/
/*未调试*/
#pragma once
#include <stdio.h>
#include <math.h>
#include "mat_option.h"

#define EPSILON 1e-10

#define CHOLESKY_DE_BUG 0    // 1 调试该文件 0 取消调试
#if CHOLESKY_DE_BUG 
#define 
#endif
// 输入n*n方阵
int Cholesky(double *mat, int n);

int Cholesky(double *mat, int n)
{
    // 逐列计算
    for (int k = 0; k < n; k++)
    {
        // 计算第 k 列
        for (int i = k; i < n; i++)
        {
            for (int j = 0; j < k; j++)
            {
                mat[i * n + k] -= mat[i * n + j] * mat[k * n + j];
            }
        }
        if (mat[k * n + k] < 0 || fabs(mat[k * n + k]) < EPSILON)
        {
            printf("ERROR\n");
            return 0;
        }
        mat[k * n + k] = sqrt(mat[k * n + k]);
        for (int i = k + 1; i < n; i++)
        {
            mat[i * n + k] /= mat[k * n + k];
        }
    }
    return 1;
}

/*测试样例*/
#if CHOLESKY_DE_BUG
int main() 
{
    
    return 0;
}
#endif