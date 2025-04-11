/*Jacobi迭代法阶=解非奇异矩阵方程组 Ax=b*/
#include <stdio.h>
#include <math.h>
#include "Norm.h"
#include "mat_option.h"

#define JACOBI_DE_BUG 0 // 1 调试该文件 0 取消调试
#if JACOBI_DE_BUG == 0
#pragma once
#endif

// 解方程mat*x=b , n为矩阵维数 , 输入x为迭代初始向量 , maxtime为最大迭代次数 , 最后结果存储于x中
int Jacobi(double *mat, double *b, double *x, int n, int maxtime);

int Jacobi(double *mat, double *b, double *x, int n, int maxtime)
{
    double x_0[n];
    double delta_x[n];
    // 判断对角元是否为0
    for (int i = 0; i < n; i++)
    {
        if (fabs(mat[i * n + i]) < EPSILON)
        {
            printf("Error: Zero pivot encountered at row %d.\n", i);
            return 0;
        }
    }
    // 开始迭代
    for (int k = 0; k < maxtime; k++)
    {
        // 记录上一次迭代结果x_0
        for (int i = 0; i < n; i++)
        {
            x_0[i]=x[i];
        }
        // 进行新一轮迭代
        for (int i = 0; i < n; i++)
        {
            x[i] = b[i];
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    x[i] -= mat[i * n + j] * x[j];
                }
            }
            x[i] /= mat[i * n + i];
        }
        // 计算相邻结果误差
        for (int i = 0; i < n; i++)
        {
            delta_x[i]=x[i]-x_0[i];
        }
        // 若误差足够小则退出
        if (vec_inf_norm(delta_x,n)<EPSILON)
        {
            return 1;
        }
    }
    // 否则退出并输出错误信息
    printf("Error: Maximum number of iterations reached without convergence.\n");
    return 0;
}

// 算例
#if JACOBI_DE_BUG
int main() 
{
    double A[]={
        8,-1,1,
        2,10,-1,
        1,1,-5
    };
    double b[]={1,4,3};
    double x[]={0.125,0.4,-0.6};
    if (Jacobi(A,b,x,3,10))
    {
        mat_print(x,3,1);
    }
    
    return 0;
}
#endif