/*=========== 原点位移反幂法 ============*/
#include <stdio.h>
#include <math.h>
#define EPSILON 1e-10
int gauss(double *mat, int n);                         // mat[n][n],b[n],将矩阵 mat 化为上三角矩阵 左下角为LU分解的L矩阵
int solve_lower_triangle(double *L, double *b, int n); // L[n][n],x[n],b[n],计算结果储存在b中,这里假设L的主对角线全为1
int solve_upper_triangle(double *U, double *b, int n); // U[n][n],x[n],b[n],计算结果储存在b中
double maxv(double *x, int dim);                       // 返回向量 x 中绝对值最大者
double _max(double a, double b);
double IPower(double *mat, int n, double *x0, double lambda, int maxstep); //
int gauss(double *mat, int n)                                              // mat[n][n],b[n],将矩阵 mat 化为上三角矩阵 左下角为LU分解的L矩阵
{
    for (int i = 0; i < n - 1; i++) // 用第i行进行消元
    {
        if (fabs(mat[i * n + i]) < EPSILON) // 判断主元是否为0
        {
            printf("The matrix is singular\n");
            return 0;
        }
        for (int j = i + 1; j < n; j++)
        {
            mat[j * n + i] /= mat[i * n + i]; // 将消去系数储存在mat的左下角 即L
            for (int k = i + 1; k < n; k++)   // 用第i行消去第j行
            {
                mat[j * n + k] -= mat[j * n + i] * mat[i * n + k];
            }
        }
    }
    return 1;
}

int solve_lower_triangle(double *L, double *b, int n) // L[n][n],x[n],b[n]
{
    // 不检查L是否为下三角
    for (int j = 0; j < n; j++)
    {
        for (int i = j + 1; i < n; i++)
        {
            b[i] -= L[i * n + j] * b[j];
        }
    }
    return 1;
}

int solve_upper_triangle(double *U, double *b, int n) // U[n][n],x[n],b[n]
{
    // 不检查U是否为上三角
    for (int j = n - 1; j >= 0; j--)
    {
        if (fabs(U[j * n + j]) < EPSILON) // 判断是否为奇异矩阵
        {
            printf("The matrix is singular\n");
            return 0;
        }
        b[j] /= U[j * n + j];
        for (int i = 0; i < j; i++)
        {
            b[i] -= U[i * n + j] * b[j];
        }
    }
    return 1;
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

double _max(double a, double b)
{
    return ((a > b) ? a : b);
}

double IPower(double *A, int n, double *x0, double lamda, int maxstep)
{
    int i, j, k;
    int cnt = 0;
    double err = 10;
    double m = 1.0, m_;
    // 原点位移
    for (i = 0; i < n; i++)
    {
        A[i * n + i] -= lamda;
    }
    // 将A做LU分解
    gauss(A, n);
    // 进入循环
    while (err > EPSILON && cnt <= maxstep)
    {
        err = 0.0;
        // 解A*y=x,解储存在x0中
        solve_lower_triangle(A, x0, n);
        solve_upper_triangle(A, x0, n);
        m_ = maxv(x0, n);
        for (i = 0; i < n; i++)
        {
            x0[i] /= m_;
        }
        err = fabs(m - m_);
        m = m_;
        cnt++;
    }
    if (cnt > maxstep)
    {
        printf("Maximum number of iterations reached without convergence.\n");
        return 0;
    }
    return lamda + 1 / m;
}

// 测试
int main()
{
    double A[3 * 3] = {6, 2, 1,
                       2, 3, 1,
                       1, 1, 1};
    double x0[3] = {1, 0, 0};
    double lamda = 5;
    printf("%lf\n", IPower(A, 3, x0, lamda, 200));
    return 0;
}