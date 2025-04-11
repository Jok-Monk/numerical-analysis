/*Gauss-seidel迭代法阶=解非奇异矩阵方程组 Ax=b*/
#include <stdio.h>
#include <math.h>
#include "Norm.h"
#include "mat_option.h"

#define GAUSS_SEIDEL_DE_BUG 0 // 1 调试该文件 0 取消调试
#if GAUSS_SEIDEL_DE_BUG == 0
#pragma once
#endif
// 解方程mat*x=b , n为矩阵维数 , 输入x为迭代初始向量 , maxtime为最大迭代次数 , ERR为误差范围 , 最后结果存储于x中
int Gauss_seidel(double *mat, double *b, double *x, int n, int maxtime, double ERR);

int Gauss_seidel(double *mat, double *b, double *x, int n, int maxtime, double ERR)
{
    int cnt = 0;     // 循环计数
    double err = 10; // 记录误差
    double tmp;      // 记录迭代值
    while ((err >= ERR) && (cnt <= maxtime) && (!isinf(err)))
    {
        // 判断迭代是否可以进行
        for (int i = 0; i < n; i++)
        {
            if (fabs(mat[i * n + i]) < EPSILON)
            {
                printf("Fail.");
                return 0;
            }
        }
        err = 0;
        for (int i = 0; i < n; i++)
        {
            // 迭代
            tmp = b[i];
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    tmp -= mat[i * n + j] * x[j];
                }
            }
            tmp /= mat[i * n + i];

            // 计算误差
            //err = _max(err, fabs(tmp - x[i])/(fabs(tmp)+1.0));//计算相对误差
            err = _max(err, fabs(tmp - x[i]));//计算绝对误差
            x[i] = tmp; // 更新x[i]
        }
        cnt++; // 更新迭代次数
    }
    if (cnt > maxtime || isinf(err))
    {
        printf("Fail.");
        return 0;
    }
    return 1;
}

// 算例
#if GAUSS_SEIDEL_DE_BUG
int main()
{
    double A[] = {8, -1, 1,
                  2, 10, -1,
                  1, 1, -5};
    double b[] = {1, 4, 3};
    double x[3];
    if (Gauss_seidel(A,b,x,3,100,1e-6))
    {
        mat_print(x,3,1);
    }
    return 0;
}
#endif