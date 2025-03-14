/*列主元消去法解方程*/
#ifndef GAUSSCOLUMNPIVOT_H
#define GAUSSCOLUMNPIVOT_H
#include <stdio.h>
#include <math.h>
#include"mat_option.h"
#define GAUSSCOLUMNPIVOT_DE_BUG 0    // 1 调试该文件 0 取消调试
#if GAUSSCOLUMNPIVOT_DE_BUG 
#define N 2
#endif
#define EPSILON 1e-10
// 输入n*n矩阵mat和n*1右端向量b，并将结果储存在b中
int gaussColumnPivot(double *mat, double *b, int n);


int gaussColumnPivot(double *mat, double *b, int n) 
{
    int maxRow;                     // 记录住元所在行
    for (int i = 0; i < n - 1; i++) // 逐行消元
    {
        maxRow = chooseColumnPivot(mat, n, n, i, i); // 选取列主元
        if (maxRow != i)                             // 若列主元与当前i元不一致，则交换行
        {
            swapRows(mat, n, n, maxRow, i);
            swapRows(b, n, 1, maxRow, i);
        }
        if (fabs(mat[i * n + i]) < EPSILON) // 判断主元是否为0
        {
            printf("The matrix is singular\n");
            return 0;
        }
        for (int j = i + 1; j < n; j++)
        {
            mat[j * n + i] /= mat[i * n + i]; // 将消去系数储存在mat的左下角
            for (int k = i + 1; k < n; k++)   // 用第i行消去第j行
            {
                mat[j * n + k] -= mat[j * n + i] * mat[i * n + k];
            }
            b[j] -= mat[j * n + i] * b[i];
        }
    }
    //求解
    for (int i = n - 1; i >= 0; i--)
    {
        if (fabs(mat[i * n + i]) < EPSILON) // 判断是否为奇异矩阵
        {
            printf("The matrix is singular\n");
            //printf("mat:%d %d",i,i);
            return 0;
        }
        b[i] /= mat[i * n + i];
        for (int j = i - 1; j >= 0; j--)
        {
            b[j] -= mat[j * n + i] * b[i];
        }
    }
    return 1;
}

#if GAUSSCOLUMNPIVOT_DE_BUG
int main()
{
    double A[N * N] = {0.0001, 1, 1, 1}; //测试矩阵
    double b[N] = {1, 2};
    if (gaussColumnPivot(A, b, N))
    {
        for (int i = 0; i < N; i++)
        {
            printf("%lf ", b[i]);
        }
    }
    else
    {
        printf("ERROR\n");
    }

    return 0;
}
#endif
#endif