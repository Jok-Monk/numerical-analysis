#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// 输入矩阵A,rows,cols,初始向量x0,dim,最大迭代次数maxtime,误差eps,输出按模最大实特征值M
int EigenValVec(double *A, int rows, int cols, double *x0, int dim, int maxtime, double eps, double *M);
// 返回向量 x 中绝对值最大者
double maxv(double *x, int dim);

int EigenValVec(double *A, int rows, int cols, double *x0, int dim, int maxtime, double eps, double *M)
{
    // 检查A*x0是否有意义
    if (cols != dim)
    {
        printf("Error: The dimensions of matrix A and vector x0 do not match.\n");
        return 0;
    }
    // 检查矩阵A是否是方阵
    if (rows != cols)
    {
        printf("Error: Matrix A is not square.\n");
        return 0;
    }
    double m = -1;
    double *x = (double *)malloc(dim * sizeof(double)); // 存储Ax0
    // 进入迭代
    for (int times = 0; times < maxtime; times++)
    {
        for (int i = 0; i < rows; i++)
        {
            x[i] = 0;
            for (int j = 0; j < cols; j++)
            {
                x[i] += A[i * cols + j] * x0[j];
            }
        }
        if (fabs(m - maxv(x, dim)) < eps)
        {
            *M = m;
            free(x);
            return 1; // 迭代收敛
        }
        for (int i = 0; i < dim; i++)
        {
            x0[i] = x[i] / maxv(x, dim); // 归一化
        }
        m = maxv(x, dim); // Ax0的绝对值最大者
    }
}
double maxv(double *x, int dim) // 返回向量 x 中绝对值最大者
{

    int index = 0;
    for (int i = 0; i < dim; i++)
    {
        index = fabs(x[index]) > fabs(x[i]) ? index : i;
    }

    return x[index];
}
// 测试样例
int main()
{
    double A[3 * 3] = {-4, 14, 0,
                       -5, 13, 0,
                       -1, 0, 2};
    double x0[3] = {1, 1, 1};
    double M;
    if (EigenValVec(A, 3, 3, x0, 3, 1000, 1e-10, &M))
    {
        printf("The largest eigenvalue is: %f\n", M);
    }
    else
    {
        printf("Eigenvalue computation did not converge.\n");
    }
    return 0;
}