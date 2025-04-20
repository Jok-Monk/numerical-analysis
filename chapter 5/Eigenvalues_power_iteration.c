#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// 输入矩阵A,rows,cols,初始向量x0,dim,最大迭代次数maxtime,误差eps,输出按模最大实特征值M,Rayleigh_Quotient=1则进行rayleigh_quotient加速
int EigenValVec_power(double *A, int rows, int cols, double *x0, int dim, int maxtime, double eps, double *M, int rayleigh_quotient);
// 返回向量 x 中绝对值最大者
double maxv(double *x, int dim);

int EigenValVec_power(double *A, int rows, int cols, double *x0, int dim, int maxtime, double eps, double *M, int rayleigh_quotient)
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
    double m = 0;
    *M = 0;
    double *x = (double *)malloc(dim * sizeof(double)); // 存储Ax0
    if (rayleigh_quotient == 1)
    { // 检查是否为对称矩阵
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j <= i - 1; j++)
            {
                if (A[i * cols + j] != A[j * cols + i])
                {
                    printf("Error: Matrix A is not symmetric.\n");
                    return 0;
                }
            }
        }
        double s;
        // 进入迭代
        for (int times = 0; times < maxtime; times++)
        {
            // 计算x=A*x0
            for (int i = 0; i < rows; i++)
            {
                x[i] = 0;
                for (int j = 0; j < cols; j++)
                {
                    x[i] += A[i * cols + j] * x0[j];
                }
            }
            m = maxv(x, dim);
            for (int i = 0; i < dim; i++)
            {
                x0[i] = x[i] / m; // 归一化
            }
            // 计算rayleigh_quotient,储存在m中
            m = 0.0;
            s = 0.0;
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    m += x0[i] * A[i * cols + j] * x0[j];
                }
                s += x0[i] * x0[i];
            }
            m /= s;
            if (fabs(*M - m) < eps) // 两次计算结果误差小于eps则认为收敛
            {
                *M = m;
                free(x);
                return 1; // 迭代收敛
            }
            *M = m;
        }
    }
    else
    {
        // 进入迭代
        for (int times = 0; times < maxtime; times++)
        {
            // 计算x=A*x0
            for (int i = 0; i < rows; i++)
            {
                x[i] = 0;
                for (int j = 0; j < cols; j++)
                {
                    x[i] += A[i * cols + j] * x0[j];
                }
            }
            m = maxv(x, dim);
            if (fabs(*M - m) < eps) // 两次计算结果误差小于eps则认为收敛
            {
                *M = m;
                free(x);
                return 1; // 迭代收敛
            }
            for (int i = 0; i < dim; i++)
            {
                x0[i] = x[i] / m; // 归一化
            }
            *M = m;
        }
    }
    printf("Error: Maximum number of iterations reached without convergence.\n");
    free(x);
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
    double A[4 * 4] = {1, 2, 1, 2,
                       2, 2, -1, 1,
                       1, -1, 1, 1,
                       2, 1, 1, 1};
    double x0[4] = {1, 1, 1, 1};
    double M;
    if (EigenValVec_power(A, 4, 4, x0, 4, 1000, 1e-10, &M, 1))
    {
        printf("The largest eigenvalue is: %f\n", M);
    }
    else
    {
        printf("Eigenvalue computation did not converge.\n");
    }
    return 0;
}