/* ==== matrix.c 源文件 ==== */
#include "matrix.h"
#include "num_debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct MATRIX
{
    int rows;     // 行数
    int cols;     // 列数
    double *data; // 使用一维数组存储，按行优先存储
};

// 检查操作

int Is_upper(const Matrix mat) // 检查矩阵mat是否为上三角,是则返回YES,否则返回NO,矩阵不存在或数据不存在则返回ERROR_INVALID_ARG
{
    if (mat == NULL) // 检查矩阵是否存在，否则返回FAILURE
    {
        LOG("矩阵不存在\n");
        return FAILURE;
    }
    if (mat->data == NULL) // 检查矩阵数据是否存在，否则返回FAILURE
    {
        LOG("矩阵数据不存在\n");
        return FAILURE;
    }
    if (mat->cols != mat->rows) // 检查矩阵是否为方阵，否则返回NFAILURE
    {
        LOG("矩阵不是方阵\n");
        return FAILURE;
    }

    /*检查矩阵是否为上三角*/

    for (int i = 1; i < mat->rows; i++) // 遍历矩阵的行
    {
        for (int j = 0; j < mat->rows - 1; j++) // 在每一行内遍历矩阵的列
        {
            if (mat->data[i * (mat->cols) + j] != 0) // 检查上三角矩阵的下三角元素是否为0，否则返回NO
            {
                LOG("矩阵不是上三角\n");
                return FAILURE;
            }
        }
    }

    return SUCCESS; // 检查无误返回YES
}

// 调试操作

void matrix_print(const Matrix mat) // 打印输入的矩阵结构体指针
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

void matrix_get(Matrix mat) // 从标准输入获取矩阵数据
{
    for (int i = 0; i < mat->rows; i++) // 遍历矩阵的行
    {
        for (int j = 0; j < mat->cols; j++) // 在每一行内遍历矩阵的列
        {
            scanf("%lf", &mat->data[i * mat->cols + j]); // 输入矩阵元素
        }
    }
}

// 基础操作

int matrix_create(Matrix *mat, int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
    {
        LOG("行数或列数<=0\n");
        return FAILURE; // 若行数或列数<=0,则返回FAILURE
    }

    if (*mat != NULL)
    {
        LOG("矩阵已经创建\n");
        return FAILURE; // 若矩阵已经创建，则返回FAILURE
    }

    *mat = (Matrix)malloc(sizeof(struct MATRIX)); // 为矩阵结构体分配地址
    if (!(*mat))
    {
        LOG("内存分配失败\n");
        return FAILURE; // 若矩阵结构体地址分配失败，则返回FAILURE
    }
    (*mat)->rows = rows;                                           // 为矩阵结构体中的行数赋值
    (*mat)->cols = cols;                                           // 为矩阵结构体中的列数赋值
    (*mat)->data = (double *)malloc(rows * cols * sizeof(double)); // 为矩阵数据mat->data分配地址

    if (!(*mat)->data) // 若mat->data地址分配失败，则释放mat并返回NULL
    {
        LOG("内存分配失败\n");
        free(*mat);
        *mat = NULL;
        return FAILURE;
    }
    return SUCCESS;
}

int matrix_free(Matrix *mat) // 释放输入的矩阵结构体指针，无返回值
{
    if (mat && *mat) // 若输入的矩阵结构体非空则进行释放
    {
        if ((*mat)->data) // 若矩阵数据mat->data指针非空则释放mat->data
            free((*mat)->data);
        free(*mat); // 释放矩阵结构体指针
        *mat = NULL; // 将指针置为NULL
        return SUCCESS;
    }
    LOG("矩阵已经释放或不存在\n");
    return FAILURE;
}

// 功能实现

int solve_upper_triangular(const Matrix U, const Matrix x, const Matrix b)
{
    if ((U == NULL) || (b == NULL)) // 检查U,b是否为空指针,否则返回FAILURE
    {
        LOG("矩阵不存在\n");
        return FAILURE;
    }
    if ((U->cols != U->rows) || (U->cols != x->rows) || (U->rows != b->rows)) // 检查U,x,b参数是否符合要求，否则返回FAILURE
    {
        LOG("参数错误\n");
        return FAILURE;
    }
    if (Is_upper(U) != SUCCESS) // 检查U是否为上三角矩阵，若否则退出
    {
        return FAILURE;
    }
    double sum;                            // 定义累加器
    for (int i = U->rows - 1; i >= 0; i--) // 从最后一行开始逐行求解
    {
        sum = 0;
        if (FLOAT_EQ(U->data[i*(U->cols)+i],0)) // 判断被除数是否过小，避免除小数
        {
            LOG("方程无解\n");
            return FAILURE;
        }
        for (int j = i + 1; j < U->rows; j++) // 计算已知解的线性组合
        {
            sum += (U->data[i * (U->cols) + j]) * (x->data[j]);
        }
        x->data[i] = (b->data[i] - sum) / U->data[i * (U->cols) + i]; // 求解第i个未知数
    }
    return SUCCESS;
}

int gauss(const Matrix A, const Matrix b, const Matrix U, const Matrix c)
{
    if((A==NULL)||(b==NULL)||(U==NULL)||(c==NULL)) //检查矩阵是否存在
    {
        LOG("矩阵不存在\n");
        return FAILURE;
    }
    if ((A->rows != A->cols) || (A->cols != b->rows)||(U->rows!=U->cols)||(U->cols!=c->rows)||(A->rows!=U->rows)) //检查输入
    {
        LOG("参数错误\n");
        return FAILURE;
    }
    for (int i = 0; i < A->rows-1; i++) 
    {

        if (FLOAT_EQ(A->data[i*(A->cols)+i],0)) // 判断被除数是否过小，避免除小数
        {
            LOG("gauss消元无法进行\n");
            return FAILURE;
        }
        for (int j = i + 1; j < A->rows; j++) 
        {
            double factor = A->data[j * (A->cols) + i] / A->data[i * (A->cols) + i];
            
            for (int k = i; k < A->cols; k++)
            {
                A->data[j * (A->cols) + k] -= factor * A->data[i * (A->cols) + k];
            }
            b->data[j] -= factor * b->data[i];
        }
    }
    
    
}