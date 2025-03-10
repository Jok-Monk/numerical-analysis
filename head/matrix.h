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

Matrix matrix_create(int rows, int cols);  // 输入矩阵行,列数,返回相应规模的矩阵结构体指针.若创建失败则返回NULL
void matrix_free(Matrix mat);  // 释放输入的矩阵结构体指针，无返回值



// 功能实现

// 解上三角线性方程组 Ux = b,输入矩阵U和b的结构体指针,将解(列)向量传入x的结构体指针,
// 参数错误则返回ERROR_INVALID_ARG,
// 矩阵不符合要求则返回ERROR_NUMERICAL,
// 成功求解则返回SUCCESS,
// 方程无解则返回FAILURE
int solve_upper_triangular(const Matrix U, const Matrix x, const Matrix b);  

// 可以继续添加其他函数声明...

#endif