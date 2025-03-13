/*下三角方程求解*/
/*未测试*/ 
#ifndef SOLVE_LOWER_TRIANGLE_H
#define SOLVE_LOWER_TRIANGLE_H

#include <stdio.h>
#include <math.h>
#include"mat_option.h"
#define EPSILON 1e-10

#define SOLVE_LOWER_TRIANGLE_DE_BUG 0    // 1 调试该文件 0 取消调试
#if SOLVE_LOWER_TRIANGLE_DE_BUG 
#define N 3
#endif
int solve_lower_triangle(double *L, double *b, int n);    //L[n][n],x[n],b[n],计算结果储存在b中


int solve_lower_triangle(double *L, double *b, int n)    //L[n][n],x[n],b[n]
{
    //不检查L是否为下三角
    for (int j = 0; j <n; j++)
    {
        if (fabs(L[j * n + j]) < EPSILON) // 判断是否为奇异矩阵
        {
            printf("The matrix is singular\n");
            return 0;
        }
        b[j]/=L[j*n+j];
        for (int i = j+1; i < n; i++)
        {
            b[i]-=L[i*n+j]*b[j];
        }
    }
    return 1;
}

/*测试样例*/
#if SOLVE_LOWER_TRIANGLE_DE_BUG
int main()
{

    return 0;
}
#endif
#endif 