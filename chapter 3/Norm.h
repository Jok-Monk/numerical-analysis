// 此文件包含向量，矩阵的1范数，无穷范数，向量的2范数


#include <stdio.h>
#include <math.h>
#include "mat_option.h"

#define NORM_DE_BUG 0    // 1 调试该文件 0 取消调试
#if NORM_DE_BUG==0 
#pragma once 
#endif

// 计算向量1范数
double vec_1_norm(double *vec, int n);
// 计算向量2范数
double vec_2_norm(double *vec, int n);
// 计算向量无穷范数
double vec_inf_norm(double *vec, int n);
// 计算矩阵1范数
double mat_1_norm(double *mat, int rows, int cols);
// 计算矩阵无穷范数
double mat_inf_norm(double *mat, int rows, int cols);

double vec_1_norm(double *vec, int n)
{
    double s = 0;
    for (int i = 0; i < n; i++)
    {
        s += fabs(vec[i]);
    }
    return s;
}

double vec_2_norm(double *vec, int n)
{
    double s = 0;
    for (int i = 0; i < n; i++)
    {
        s += fabs(vec[i]) * fabs(vec[i]);
    }
    s = sqrt(s);
    return s;
}

double vec_inf_norm(double *vec, int n)
{
    double s = 0;
    for (int i = 0; i < n; i++)
    {
        if (s < fabs(vec[i]))
        {
            s = fabs(vec[i]);
        }
    }
    return s;
}

double mat_1_norm(double *mat, int rows, int cols)
{
    double s = 0;
    double t;
    for (int j = 0; j < cols; j++)
    {
        t = 0;
        for (int i = 0; i < rows; i++)
        {
            t += fabs(mat[i * cols + j]);
        }
        if (t > s)
        {
            s = t;
        }
    }
    return s;
}

double mat_inf_norm(double *mat, int rows, int cols)
{
    double s = 0;
    double t;
    for (int i = 0; i < rows; i++)
    {
        t = 0;
        for (int j = 0; j < cols; j++)
        {
            t += fabs(mat[i * cols + j]);
        }
        if (t > s)
        {
            s = t;
        }
    }
    return s;
}

//算例
#if NORM_DE_BUG
int main() 
{
    double vec[] = {1.0, -2.0, 3.0};
    int vec_size = 3;

    double mat[] = {
        1.0, -2.0, 3.0,
        -4.0, 5.0, -6.0,
        7.0, -8.0, 9.0
    };
    int rows = 3, cols = 3;

    printf("Vector 1-norm: %f\n", vec_1_norm(vec, vec_size));
    printf("Vector 2-norm: %f\n", vec_2_norm(vec, vec_size));
    printf("Vector infinity norm: %f\n", vec_inf_norm(vec, vec_size));

    printf("Matrix 1-norm: %f\n", mat_1_norm(mat, rows, cols));
    printf("Matrix infinity norm: %f\n", mat_inf_norm(mat, rows, cols));
    return 0;
}
#endif