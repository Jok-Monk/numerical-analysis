/* === 解上三角方程组 === */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "D:\numerical analysis\head\matrix.h"
#define N 5 // 方程组的阶数

int main()
{
    Matrix *A, *x, *y;               // 解方程组 Ax=y,其中A为N阶上三角矩阵,x,y为N维列向量
    A = matrix_create(N, N);         // 创建N阶上三角矩阵A
    x = matrix_create(N, 1);         // 创建N维列向量x
    y = matrix_create(N, 1);         // 创建N维列向量y
    printf("A\n");
    matrix_get(A);                   // 从标准输入获取矩阵A
    printf("y\n");
    matrix_get(y);                   // 从标准输入获取列向量y

    for (int i = N - 1; i >= 0; i--) // 从最后一行开始逐行求解
    {
        double sum = 0;
        for (int j = i + 1; j < N; j++) // 计算已知解的线性组合
            sum += (A->data[i * N + j]) * (x->data[j]);
        x->data[i] = (y->data[i] - sum) / A->data[i * N + i]; // 求解第i个未知数
    }
    
    matrix_print(x); // 打印解向量x
    matrix_free(A);  // 释放矩阵A
    matrix_free(x);  // 释放向量x
    matrix_free(y);  // 释放向量y
    return 0;
}