#ifndef MAT_OPTION_H
#define MAT_OPTION_H
#include <stdio.h>
#include <math.h>

#define MAT_OPTION_DE_BUG 0 // 1 调试该文件 0 取消调试
#if MAT_OPTION_DE_BUG
#define
#endif

#define EPSILON 1e-10 // 定义误差范围

/*声明*/
// 打印矩阵mat,行数rows,列数cols
void mat_print(double *mat, int rows, int cols);
// 交换rows*cols矩阵mat的row_1,row_2行
void swapRows(double *mat, int rows, int cols, int row_1, int row_2);
// 选rows*cols矩阵mat第startCol列自第startRow行起的主元,返回主元所在行号
int chooseColumnPivot(double *mat, int rows, int cols, int startRow, int startCol);
// 计算矩阵乘法,mat1(start_row1:end_row1,start_col1:end_col1)*mat2(start_row2:end_row2,start_col2:end_col2)=mat3(start_row3:end_row3,start_col3:end_col3),mat1行数rows1,列数cols1,mat2行数rows2,列数cols2
int mat_mult(double *mat1, int cols1, int start_rows1, int end_rows1, int start_cols1, int end_cols1, double *mat2, int cols2, int start_rows2, int end_rows2, int start_cols2, int end_cols2, double *mat3, int cols3, int start_rows3, int end_rows3, int start_cols3, int end_cols3);
// 计算矩阵转置,mat1=mat2的转置,mat1行数rows1,列数cols1,mat2行数rows2,列数cols2
int mat_transpose(double *mat1, double *mat2, int rows1, int cols1, int rows2, int cols2);
// 返回最大值
double _max(double a, double b);

/*定义*/
void swapRows(double *mat, int rows, int cols, int row_1, int row_2)
{
    for (int i = 0; i < cols; i++)
    {
        double temp = mat[row_1 * cols + i];
        mat[row_1 * cols + i] = mat[row_2 * cols + i];
        mat[row_2 * cols + i] = temp;
    }
}

int chooseColumnPivot(double *mat, int rows, int cols, int startRow, int startCol)
{
    double max = fabs(mat[startRow * cols + startCol]);
    int maxRow = startRow;
    for (int i = startRow + 1; i < rows; i++)
    {
        if (fabs(mat[i * cols + startCol]) > max)
        {
            max = fabs(mat[i * cols + startCol]);
            maxRow = i;
        }
    }
    return maxRow;
}

void mat_print(double *mat, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%10.6lf ", mat[i * cols + j]);
        }
        printf("\n");
    }
}

double _max(double a, double b)
{
    return ((a > b) ? a : b);
}

int mat_mult(double *mat1, int cols1, int start_rows1, int end_rows1, int start_cols1, int end_cols1, double *mat2, int cols2, int start_rows2, int end_rows2, int start_cols2, int end_cols2, double *mat3, int cols3, int start_rows3, int end_rows3, int start_cols3, int end_cols3)
{
    int lenrows1 = end_rows1 - start_rows1 + 1;
    int lencols1 = end_cols1 - start_cols1 + 1;
    int lenrows2 = end_rows2 - start_rows2 + 1;
    int lencols2 = end_cols2 - start_cols2 + 1;
    int lenrows3 = end_rows3 - start_rows3 + 1;
    int lencols3 = end_cols3 - start_cols3 + 1;
    if (lenrows1 != lenrows3 || lencols1 != lenrows2 || lencols2 != lencols3)
    {
        printf("Error: Matrix multiplication not possible.\n");
        return 0;
    }
    for (int i = 0; i < lenrows3; i++)
    {
        for (int j = 0; j < lencols3; j++)
        {
            mat3[(start_rows3 + i) * cols3 + (start_cols3 + j)] = 0;
            for (int k = 0; k < lencols1; k++)
            {
                mat3[(start_rows3 + i) * cols3 + (start_cols3 + j)] += mat1[(start_rows1 + i) * cols1 + (start_cols1 + k)] * mat2[(start_rows2 + k) * cols2 + (start_cols2 + j)];
            }
        }
    }
}

int mat_transpose(double *mat1, double *mat2, int rows1, int cols1, int rows2, int cols2)
{
    if (rows1 != cols2 || cols1 != rows2)
    {
        printf("Error: Matrix transpose not possible.\n");
        return 0;
    }
    if (mat1 == mat2)
    {
        printf("Error: Matrix transpose in-place not possible.\n");
        return 0;
    }
    else
    {
        for (int i = 0; i < rows1; i++)
        {
            for (int j = 0; j < cols1; j++)
            {
                mat2[j * rows1 + i] = mat1[i * cols1 + j];
            }
        }
        return 1;
    }
}
/*测试样例*/
#if MAT_OPTION_DE_BUG
int main()
{

    return 0;
}
#endif
#endif
