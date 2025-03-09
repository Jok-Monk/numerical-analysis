/* ==== matrix.h 头文件 ==== */
#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;   // 行数
    int cols;   // 列数
    double* data;  // 使用一维数组存储，按行优先存储
} Matrix;

// 检查操作

int Is_upper(const Matrix* mat); // 检查矩阵mat是否为上三角,是则返回1,否则返回0,矩阵不存在或数据不存在则返回-1

// 调试操作

void matrix_get(Matrix* mat);   // 从标准输入获取矩阵数据
void matrix_print(const Matrix* mat);   // 打印输入的矩阵结构体指针

// 基础操作
Matrix* matrix_create(int rows, int cols);  // 输入矩阵行,列数,返回相应规模的矩阵结构体指针.若创建失败则返回NULL
void matrix_free(Matrix* mat);  // 释放输入的矩阵结构体指针，无返回值



// 高级操作
Matrix* solve_upper_triangular(const Matrix* U, const Matrix* b);  // 解上三角线性方程组 Ux = b,输入矩阵U和b的结构体指针,返回解(列)向量指针x.若传入参数错误，则返回NULL

// 可以继续添加其他函数声明...

#endif