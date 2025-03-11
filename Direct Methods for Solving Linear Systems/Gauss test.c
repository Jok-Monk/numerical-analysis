/* === 解上三角方程组 === */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "D:\numerical analysis\head\matrix.h"
#define N 2 // 方程组的阶数



int main()
{
    Matrix A=NULL;
   // Matrix x=NULL;
    Matrix b=NULL;                
    matrix_create(&A, N, N); // 创建N阶上三角矩阵A
    matrix_create(&b, N, 1); // 创建N维列向量b
    printf("A\n");
    matrix_get(A);         
    printf("b\n");
    matrix_get(b);
    

    matrix_free(&A);  // 释放矩阵A
    matrix_free(&b);  // 释放向量x
    return 0;
}