/* ==== matrix.h 头文件 ==== */
#ifndef MATRIX_H
#define MATRIX_H

#include "D:\numerical analysis\head\num_debug.h"
 
//矩阵结构体定义

typedef struct  MATRIX* Matrix; // 内含矩阵行数,列数,数据指针的结构体

// 检查操作

int Is_upper(const Matrix mat); // 检查矩阵mat是否为上三角,是则返回YES,否则返回NO,矩阵不存在或数据不存在则返回ERROR


// 调试操作

void matrix_get(Matrix mat);   // 从标准输入获取矩阵数据
void matrix_print(const Matrix mat);   // 打印输入的矩阵结构体指针

// 基础操作

// 矩阵的创建和释放，需输入矩阵地址

int matrix_create( Matrix* A, int rows, int cols);  // 输入矩阵地址,行数,列数,创建相应规模的矩阵结构体指针，返回SUCCESS或FAILURE
int matrix_free(Matrix* mat);  // 释放输入的矩阵地址，返回SUCCESS或FAILURE



// 功能实现

// 解上三角线性方程组 Ux = b,输入矩阵U和b的结构体指针,将解(列)向量传入x的结构体指针,
// 成功求解则返回SUCCESS,
// 方程无解或其他错误则返回FAILURE
int solve_upper_triangular(const Matrix U, const Matrix x, const Matrix b);  

// 将一般的增广矩阵用高斯消元法化成上三角矩阵
// 输入增广矩阵(A,b)和待输入矩阵(U,c)
// 成功解出则返回SUCCESS
// 无解或其他错误则返回FAILURE
int gauss(const Matrix A, const Matrix b, const Matrix U, const Matrix c);

// 可以继续添加其他函数声明...

#endif