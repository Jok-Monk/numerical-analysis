#ifndef MAT_OPTION_H
#define MAT_OPTION_H
#include<stdio.h>

#define MAT_OPTION_DE_BUG 0    // 1 调试该文件 0 取消调试
#if MAT_OPTION_DE_BUG 
#define 
#endif

#define EPSILON 1e-10 // 定义误差范围

/*声明*/
void mat_print(double *mat ,int rows, int cols); // 打印矩阵
// 交换rows*cols矩阵mat的row_1,row_2行
void swapRows(double *mat, int rows, int cols, int row_1, int row_2); 
// 选rows*cols矩阵mat第startCol列自第startRow行起的主元,返回主元所在行号
int chooseColumnPivot(double *mat, int rows, int cols, int startRow, int startCol); 

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

void mat_print(double *mat ,int rows, int cols)
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

/*测试样例*/
#if MAT_OPTION_DE_BUG 
int main() 
{
    
    return 0;
}
#endif
#endif
