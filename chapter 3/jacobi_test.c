#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mat_option.h"
#include "Jacobi.h" // 包含 Jacobi 迭代法实现

#define N 10000       // 矩阵规模
#define MAX_ITER 100 // 最大迭代次数

// 生成随机对角占优矩阵
void generateDiagonalDominantMatrix(double *mat, int n)
{
    srand((unsigned int)time(NULL)); // 设置随机种子
    for (int i = 0; i < n; i++)
    {
        double rowSum = 0.0;
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                mat[i * n + j] = (double)rand() / RAND_MAX * 9.0; // 随机生成 0 到 9 之间的浮点数
                rowSum += fabs(mat[i * n + j]);
            }
        }
        mat[i * n + i] = rowSum + (double)rand() / RAND_MAX * 9.0 + 1.0; // 确保对角占优
    }
}

// 生成随机向量
void generateRandomVector(double *vec, int n)
{
    srand((unsigned int)time(NULL)); // 设置随机种子
    for (int i = 0; i < n; i++)
    {
        vec[i] = (double)rand() / RAND_MAX * 99.0;
    }
}

int main()
{
    double *A = (double *)malloc(N * N * sizeof(double)); // 分配矩阵内存
    double *b = (double *)malloc(N * sizeof(double));     // 分配向量 b 内存
    double *x = (double *)malloc(N * sizeof(double));     // 分配解向量 x 内存

    if (!A || !b || !x)
    {
        printf("内存分配失败\n");
        return -1;
    }

    // 生成对角占优矩阵和随机向量
    generateDiagonalDominantMatrix(A, N);
    generateRandomVector(b, N);

    // 初始化解向量为 0
    for (int i = 0; i < N; i++)
    {
        x[i] = 0.0;
    }

    // 记录开始时间
    clock_t start = clock();

    // 调用 Jacobi 迭代法
    if (Jacobi(A, b, x, N, MAX_ITER))
    {
        printf("Jacobi 迭代法收敛\n");
    }
    else
    {
        printf("Jacobi 迭代法未收敛\n");
    }

    // 记录结束时间
    clock_t end = clock();
    double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("矩阵规模: %d\n", N);
    printf("运行时间: %.6f 秒\n", elapsedTime);

    // 释放内存
    free(A);
    free(b);
    free(x);

    return 0;
}
/*Jacobi 迭代法收敛
矩阵规模: 10000
运行时间: 3.322000 秒*/