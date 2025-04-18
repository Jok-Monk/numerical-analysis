#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mat_option.h"
#include "Cholesky.h"
#include "solve_upper_triangle.h"
#include "solve_lower_triangle.h"
// 正则化解最小二乘问题
// 输入A,b,rows,cols,输出x
int normal_equations(double *A, double *b, double *x, int rows, int cols);
int normal_equations(double *A, double *b, double *x, int rows, int cols)
{
    double *At = (double *)malloc(sizeof(double) * cols * rows);  // At为A的转置
    double *AtA = (double *)malloc(sizeof(double) * cols * cols); // AtA为At*A
    double *Atb = (double *)malloc(sizeof(double) * cols);        // Atb为At*b
    if (At == NULL || AtA == NULL || Atb == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 0;
    }
    if (mat_transpose(A, At, rows, cols, cols, rows) == 0)
    {
        printf("Error: Matrix transpose failed.\n");
        free(At);
        free(AtA);
        free(Atb);
        return 0;
    }
    if (mat_mult(At,rows,0,cols-1,0,rows-1,A,cols,0,rows-1,0,cols-1,AtA,cols,0,cols-1,0,cols-1) == 0)
    {
        printf("Error: Matrix multiplication failed.\n");
        free(At);
        free(AtA);
        free(Atb);
        return 0;
    }
    if (mat_mult(At,rows,0,cols-1,0,rows-1,b,1,0,rows-1,0,0,Atb,1,0,cols-1,0,0) == 0)
    {
        printf("Error: Matrix multiplication failed.\n");
        free(At);
        free(AtA);
        free(Atb);
        return 0;
    }
    if (Cholesky(AtA, cols) == 0)
    {
        printf("Error: Cholesky decomposition failed.\n");
        free(At);
        free(AtA);
        free(Atb);
        return 0;
    }
    //将AtA变为对称矩阵
    for (int i = 0; i < cols-1; i++)
    {
        for(int j = i + 1; j < cols; j++)
        {
            AtA[i * cols + j] = AtA[j * cols + i];
        }
    }
    // 求解下三角和上三角方程
    if (solve_lower_triangle(AtA, Atb, cols) == 0)
    {
        printf("Error: Solving lower triangle matrix failed.\n");
        free(At);
        free(AtA);
        free(Atb);
        return 0;
    }
    if (solve_upper_triangle(AtA, Atb, cols) == 0)
    {
        printf("Error: Solving upper triangle matrix failed.\n");
        free(At);
        free(AtA);
        free(Atb);
        return 0;
    }   
    // 将结果存储到x中
    for (int i = 0; i < cols; i++)
    {
        x[i] = Atb[i];
    }
    free(At);
    free(AtA);
    free(Atb);
    return 1;
}
// 测试样例
int main()
{
    double A[3 * 2] = {2, 3,
                       1, -1,
                       -2, 4};
    double b[3] = {5, -10, -15};
    double x[2];
    if (normal_equations(A, b, x, 3, 2) == 0)
    {
        printf("Error: Normal equations failed.\n");
        return 0;
    }
    mat_print(x, 2, 1); // 打印结果
    return 0;
}
//正确解为3,-1
