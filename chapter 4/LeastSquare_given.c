#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct
{
    int i;
    int j;
    double c;
    double s;
} GIVENS; // given 矩阵 G_ij(theta),其中i<j

// 给定实数a,b,计算满足  c s  a  =  sqrt(a^2+b^2)  的参数c s
//                     -s c  b     0
int givens_get(int i, int j, double a, double b, GIVENS *givens);
// 输入给定的Givens矩阵,计算Givens矩阵乘以矩阵A的第start_col列
int givens_mult(GIVENS *givens, double *A, int A_rows, int A_cols, int A_start_col);
// 输入给定矩阵A和向量b,计算Ax=b的QR分解,这里A_rows>=A_cols
int QR_givens(double *A, double *b, int A_rows, int A_cols, int b_rows);
// 输入上三角矩阵R和向量c,Rx=c,结果储存在c中,其中R_rows>=R_cols
int solve_upper_triangle(double *R, int R_rows, int R_cols, double *c, int c_rows);
// 输入给定矩阵A和向量b,用QR分解法计算Ax=b的最小二乘解,结果储存在b中,这里A_rows>=A_cols
int least_squares(double *A, double *b, int A_rows, int A_cols, int b_rows);

int givens_get(int i, int j, double a, double b, GIVENS *givens)
{
    if (i >= j)
    {
        printf("Error: givens->i must be less than givens->j.\n");
        return 0;
    }
    givens->i = i;
    givens->j = j;
    double t;
    if (b == 0)
    {
        givens->c = 1.0;
        givens->s = 0.0;
        return 1;
    }
    if (fabs(b) > fabs(a))
    {
        t = a / b;
        givens->s = 1.0 / sqrt(1 + t * t);
        givens->c = givens->s * t;
        return 1;
    }
    t = b / a;
    givens->c = 1.0 / sqrt(1 + t * t);
    givens->s = givens->c * t;
    return 1;
}
int givens_mult(GIVENS *givens, double *A, int A_rows, int A_cols, int A_start_col)
{
    int i, j;
    i = givens->i;
    j = givens->j;
    if (i >= A_rows || j >= A_rows)
    {
        printf("Error: givens->i or givens->j out of bounds.\n");
        return 0;
    }
    if (A_start_col < 0 || A_start_col >= A_cols)
    {
        printf("Error: A_start_col out of bounds.\n");
        return 0;
    }
    double c, s;
    c = givens->c;
    s = givens->s;
    double a, b;
    a = A[i * A_cols + A_start_col];
    b = A[j * A_cols + A_start_col];
    A[i * A_cols + A_start_col] = c * a + s * b;
    A[j * A_cols + A_start_col] = -s * a + c * b;
    return 1;
}
int QR_givens(double *A, double *b, int A_rows, int A_cols, int b_rows)
{
    if (A_rows != b_rows)
    {
        printf("Error: A_rows must be equal to b_rows.\n");
        return 0;
    }
    if (A_rows < A_cols)
    {
        printf("Error: A_rows must be greater than or equal to A_cols.\n");
        return 0;
    }
    GIVENS givens;
    for (int j = 0; j < A_cols; j++)
    {
        for (int i = j; i < A_rows-1; i++)
        {
            // 若A[i+1][j]元非零,则计算Givens矩阵,并将其乘以A,b
            if (A[(i + 1) * A_cols + j] != 0)
            {
                if (givens_get(j, i + 1, A[j * A_cols + j], A[(i + 1) * A_cols + j], &givens) == 0)
                {
                    return 0;
                }
                for (int k = j; k < A_cols; k++)
                {
                    if (givens_mult(&givens, A, A_rows, A_cols, k) == 0)
                    {
                        return 0;
                    }
                }
                if (givens_mult(&givens, b, b_rows, 1, 0) == 0)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}
int solve_upper_triangle(double *R, int R_rows, int R_cols, double *c, int c_rows)
{
    if (R_rows != c_rows)
    {
        printf("Error: R_rows must be equal to c_rows.\n");
        return 0;
    }
    if (R_rows < R_cols)
    {
        printf("Error: R_rows must be greater than or equal to R_cols.\n");
        return 0;
    }
    int n = R_cols;
    for (int j = n - 1; j >= 0; j--)
    {
        if (fabs(R[j * n + j]) < 1e-12) // 判断是否为奇异矩阵
        {
            printf("The matrix is singular\n");
            return 0;
        }
        c[j] /= R[j * n + j];
        for (int i = 0; i < j; i++)
        {
            c[i] -= R[i * n + j] * c[j];
        }
    }
    return 1;
}
int least_squares(double *A, double *b, int A_rows, int A_cols, int b_rows)
{
    // 计算QR分解
    if (QR_givens(A, b, A_rows, A_cols, b_rows) == 0)
    {
        return 0;
    }
    // 计算Ax=b的最小二乘解
    if (solve_upper_triangle(A, A_rows, A_cols, b, b_rows) == 0)
    {
        return 0;
    }
    return 1;
}
// 测试样例
int main()
{
    double A[3 * 2];
    double b[3] = {1, -4, 1};
    double karple=10000.0;
    A[0*2 + 0] = 3*karple/(2*sqrt(2))+0.5;
    A[0*2 + 1] = -sqrt(3)*karple/(2*sqrt(2))+sqrt(3)/2.0;
    A[1*2 + 0] = -0.5;
    A[1*2 + 1] = -sqrt(3)/2.0;
    A[2*2 + 0] = -3*karple/(2*sqrt(2))+0.5;
    A[2*2 + 1] = sqrt(3)*karple/(2*sqrt(2))+sqrt(3)/2.0;
    if(least_squares(A, b, 3, 2, 3) == 0)
    {
        printf("Error: least_squares failed.\n");
        return 0;
    }
    printf("The least squares solution is: %lf, %lf\n", b[0], b[1]);
    return 0;
}