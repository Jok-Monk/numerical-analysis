/*计算Householder变换*/
/*输入矩阵mat,cols,start_row,end_row,start_col,end_col,计算相应householder变换矩阵H=I-beta*v*vT,使得Hy=-sign(y1)||y||e1,并将v归一使得v[0]=1,v(1:dim-1)存储在mat对应的列中,返回beta*/
/*未调试*/
#include <stdio.h>
#include <math.h>
#include "mat_option.h"
#include "Norm.h"

#define HOUSEHOLDER_DE_BUG 0 // 1 调试该文件 0 取消调试
#if (HOUSEHOLDER_DE_BUG == 0)
#pragma once
#endif
// 输入矩阵mat,cols,start_row,end_row,start_col,end_col,计算相应householder变换矩阵H=I-beta*v*vT,使得Hy=-sign(y1)||y||e1,并将v归一使得v[0]=1,v(1:dim-1)存储在mat对应的列中,返回beta
int Householder(double *mat, int cols, int start_row, int end_row, int start_col, int end_col, double *beta);
// 计算householder变换矩阵对矩阵的作用,输入矩阵H,cols,H_start_row,H_end_row,H_start_col,H_end_col,beta,A,cols,A_start_row,A_end_row,A_start_col,A_end_col,计算H*A,这里默认输入的householder变换矩阵对应的列向量首一位为1
int Householder_mult(double *H, int H_cols, int H_start_row, int H_end_row, int H_start_col, int H_end_col, double beta, double *A, int A_rows, int A_cols, int A_start_row, int A_end_row, int A_start_col, int A_end_col);
int Householder(double *mat, int cols, int start_row, int end_row, int start_col, int end_col, double *beta)
{
    // 检查输入是否为矩阵mat的某个列
    if (start_col != end_col)
    {
        printf("Error: The input is not a column vector.\n");
        return 0;
    }
    int dim = end_row - start_row + 1; // 计算向量维数
    if (dim <= 0)
    {
        printf("Error: The input is not a column vector.\n");
        return 0;
    }
    // 计算无穷范数
    double eta = fabs(mat[start_row * cols + start_col]);
    for (int i = 1; i < dim; i++)
    {
        if (fabs(mat[(start_row + i) * cols + start_col]) > eta)
        {
            eta = fabs(mat[(start_row + i) * cols + start_col]);
        }
    }
    // 按无穷范数归一化
    for (int i = 0; i < dim; i++)
    {
        mat[(start_row + i) * cols + start_col] /= eta;
    }
    // 计算列向量的后dim-1个元素的平方和
    double sigma = 0;
    for (int i = 1; i < dim; i++)
    {
        sigma += mat[(start_row + i) * cols + start_col] * mat[(start_row + i) * cols + start_col];
    }
    if (sigma == 0)
    {
        *beta = 0;
        return 1;
    }
    else
    {
        double alpha = sqrt(mat[start_row * cols + start_col] * mat[start_row * cols + start_col] + sigma);
        if (mat[start_row * cols + start_col] <= 0)
        {
            mat[start_row * cols + start_col] -= alpha;
        }
        else
        {
            mat[start_row * cols + start_col] += alpha;
        }
        *beta = 2 * mat[start_row * cols + start_col] * mat[start_row * cols + start_col] / (mat[start_row * cols + start_col] * mat[start_row * cols + start_col] + sigma);
        //将householder变换向量首一化
        for (int i = 1; i < dim; i++)
        {
            mat[(start_row + i) * cols + start_col] /= mat[start_row * cols + start_col];
        }
        return 1;
    }
}
int Householder_mult(double *H, int H_cols, int H_start_row, int H_end_row, int H_start_col, int H_end_col, double beta, double *A, int A_rows, int A_cols, int A_start_row, int A_end_row, int A_start_col, int A_end_col)
{
    // 检查输入是否为矩阵mat的某个列
    if (H_start_col != H_end_col)
    {
        printf("Error: The input is not a column vector.\n");
        return 0;
    }
    // 检查矩阵乘法是否可以进行
    int H_dim = H_end_row - H_start_row + 1;
    int _A_rows = A_end_row - A_start_row + 1;
    int _A_cols = A_end_col - A_start_col + 1;
    if (H_dim != _A_rows)
    {
        printf("Error: cannot multiply");
        return 0;
    }
    // 计算w=beta*AT*v
    double w[_A_cols];
    for (int i = 0; i < _A_cols; i++)
    {
        w[i] = 0;
        for (int j = 0; j < H_dim; j++)
        {
            if (j == 0)
            {
                w[i] += A[(A_start_row + j) * A_cols + A_start_col + i] * 1.0;
            }
            else
            {
                w[i] += A[(A_start_row + j) * A_cols + A_start_col + i] * H[(H_start_row + j) * H_cols + H_start_col];
            }
        }
        w[i] *= beta;
    }
    // 计算A=A-vwT
    for (int i = 0; i < _A_rows; i++)
    {
        for (int j = 0; j < _A_cols; j++)
        {
            if (i==0)
            {
                A[(A_start_row + i) * A_cols + A_start_col + j] -= w[j] * 1.0;
            }
            else
            {
                A[(A_start_row + i) * A_cols + A_start_col + j] -= w[j] * H[(H_start_row + i) * H_cols + H_start_col];
            }            
        }
    }
}
/*测试样例*/
#if HOUSEHOLDER_DE_BUG
int main()
{
    double A[3 * 2] = {2, 3,
                       1, -1,
                       -2, 4};
    double beta;
    Householder(A, 2, 0, 2, 0, 0, &beta);
    Householder_mult(A, 2, 0, 2, 0, 0, beta, A, 3, 2, 0, 2, 1, 1);
    return 0;
}
#endif