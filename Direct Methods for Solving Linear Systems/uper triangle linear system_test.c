/* === 解上三角方程组 === */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "D:\numerical analysis\head\matrix.h"
#define N 2 // 方程组的阶数



int main()
{
    Matrix A;
    Matrix x;
    Matrix y;                // 解方程组 Ax=y,其中A为N阶上三角矩阵,x,y为N维列向量
    A = matrix_create(N, N); // 创建N阶上三角矩阵A
    x = matrix_create(N, 1); // 创建N维列向量x
    y = matrix_create(N, 1); // 创建N维列向量y

    printf("A\n");
    matrix_get(A);         
    printf("y\n");
    matrix_get(y);
    int ANS=solve_upper_triangular(A, x, y);     // 解上三角线性方程组Ax=y
    matrix_print(x); // 打印解向量x
    matrix_free(A);  // 释放矩阵A
    matrix_free(x);  // 释放向量x
    matrix_free(y);  // 释放向量y
    printf("%d\n",ANS);
    return 0;
}