#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mat_option.h"
#include "Norm.h"
#include "Householder.h"

#define QR_HOUSEHOLDER_DE_BUG 1 // 1 调试该文件 0 取消调试
#if QR_HOUSEHOLDER_DE_BUG == 0
#pragma once
#endif
// householder方法求矩阵A的QR分解，输入A,rows,cols,计算结果R储存于A的右上方,不储存Q
int QR_Householder(double *A, int rows, int cols);
int QR_Householder(double *A, int rows, int cols)
{
    double beta;  // householder变换的beta
    double alpha; // QR分解后的对角元
    for (int i = 0; i < cols; i++)
    {
        alpha = 0;
        for (int j = i; j < rows; j++)
        {
            alpha += A[j * cols + i] * A[j * cols + i];
        }
        alpha = sqrt(alpha);
        if (A[i * cols + i] > 0)
        {
            alpha = -alpha;
        }
        if (Householder(A, cols, i, rows - 1, i, i, &beta) == 0)
        {
            return 0;
        }
        A[i * cols + i] = alpha;
        if (Householder_mult(A, cols, i, rows - 1, i, i, beta, A, rows, cols, i, rows - 1, i+1, cols - 1) == 0)
        {
            return 0;
        }
    }
    return 1;
}
// 测试样例
#if QR_HOUSEHOLDER_DE_BUG
int main()
{
    double A[3 * 2] = {2, 3,
                       1, -1,
                       -2, 4};
    QR_Householder(A, 3, 2);
    mat_print(A, 3, 2);
    return 0;
}
#endif