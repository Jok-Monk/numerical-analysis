#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Norm.h"
#include "Gauss_seidel.h"
#include "mat_option.h"
#define N 10
int main()
{
    double A[N * N]; // 矩阵A
    double b[N];
    double x[N] = {0}; // 初值为0
    // 为A赋值
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                A[i * N + j] = 3.0;
            }
            else if (i == j - 1)
            {
                A[i * N + j] = 1.0;
            }
            else if (i == j + 1)
            {
                A[i * N + j] = 9.0;
            }
            else
            {
                A[i * N + j] = 0.0;
            }
        }
    }
    // 为b赋值
    for (int i = 0; i < N; i++)
    {
        if (i == 0)
        {
            b[i] = 4.0;
        }
        else if (i == N-1)
        {
            b[i] = 12.0;
        }
        else
        {
            b[i] = 13.0;
        }
    }
    // 调用Gauss_seidel函数
    int result = Gauss_seidel(A, b, x, N, 1000, 1e-6);
    if (result == 1)
    {
        printf("Success.\n");
        mat_print(x, 1, 100); // 打印结果
    }
    else
    {
        printf("Fail.\n");
    }
    return 0;
}
