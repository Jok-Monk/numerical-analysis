/* ==== matrix.c 源文件 ==== */
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Matrix *matrix_create(int rows, int cols) // 输入矩阵行,列数,返回相应规模的矩阵结构体指针.若创建失败则返回NULL
{
    if (rows <= 0 || cols <= 0)
        return NULL; // 若行数或列数<=0,则返回NULL

    Matrix *mat = (Matrix *)malloc(sizeof(Matrix)); // 为矩阵结构体分配地址
    if (!mat)
        return NULL; // 若矩阵结构体地址分配失败，则返回NULL

    mat->rows = rows;                                           // 为矩阵结构体中的行数赋值
    mat->cols = cols;                                           // 为矩阵结构体中的列数赋值
    mat->data = (double *)malloc(rows * cols * sizeof(double)); // 为矩阵数据mat->data分配地址

    if (!mat->data) // 若mat->data地址分配失败，则释放mat并返回NULL
    {
        free(mat);
        return NULL;
    }
    return mat; // 返回mat指针
}

void matrix_free(Matrix *mat) // 释放输入的矩阵结构体指针，无返回值
{
    if (mat) // 若输入的矩阵结构体非空则进行释放
    {
        if (mat->data) // 若矩阵数据mat->data指针非空则释放mat->data
            free(mat->data);
        free(mat); // 释放矩阵结构体指针
    }
}

void matrix_print(const Matrix *mat) // 打印输入的矩阵结构体指针
{
    for (int i = 0; i < mat->rows; i++) // 遍历矩阵的行
    {
        for (int j = 0; j < mat->cols; j++) // 在每一行内遍历矩阵的列
        {
            printf("%8.4f ", mat->data[i * mat->cols + j]); // 以8个字符宽度和4位小数精度输出矩阵元素
        }
        printf("\n");
    }
}

void matrix_get(Matrix *mat) // 从标准输入获取矩阵数据
{
    for (int i = 0; i < mat->rows; i++) // 遍历矩阵的行
    {
        for (int j = 0; j < mat->cols; j++) // 在每一行内遍历矩阵的列
        {
            scanf("%lf", &mat->data[i * mat->cols + j]); // 输入矩阵元素
        }
    }
}

int Is_upper(const Matrix *mat) // 检查矩阵mat是否为上三角,是则返回1,否则返回0,矩阵不存在或数据不存在则返回-1
{
    if (mat == NULL) // 检查矩阵是否存在，否则返回-1
        return -1;
    if (mat->data == NULL) // 检查矩阵数据是否存在，否则返回-1
        return -1;
    if (mat->cols != mat->rows) // 检查矩阵是否为方阵，否则返回0
        return 0;

    /*检查矩阵是否为上三角*/

    for (int i = 1; i < mat->rows; i++) // 遍历矩阵的行
    {
        for (int j = 0; j < mat->rows; j++) // 在每一行内遍历矩阵的列
        {
            if (mat->data[i * (mat->cols) + j] != 0) // 检查上三角矩阵的下三角元素是否为0，否则返回0
                return 0;
        }
    }
}

Matrix *solve_upper_triangular(const Matrix *U, const Matrix *b) // 解上三角线性方程组 Ux = b,输入矩阵U和b的结构体指针,返回解(列)向量指针x.若传入参数错误或创建解向量失败则返回NULL
{
    if ((U == NULL) || (b == NULL)) // 检查U,b是否为空指针,否则返回NULL
        return NULL;
    if ((U->cols != U->rows) || (U->cols != b->cols)) // 检查U,b参数是否符合要求，否则返回NULL
        return NULL;
    if (Is_upper(U)==0) // 检查U是否为上三角矩阵，否则返回NULL
        return NULL;
    Matrix *x;
    x = matrix_create(U->rows, 1);
    if (x == NULL) // 检查x是否创建成功，否则返回NULL
        return NULL;
    
}