/*LDU分解,输入方阵A,计算其LDU分解*/
/*其中L,U主对角线为1,故A主对角线可用于存储D,其余部分存储L,U*/

#pragma once
#include <stdio.h>
#include <math.h>
#include "Doolittle.h"
#include "mat_option.h"


#define LDU_DE_BUG 0    // 1 调试该文件 0 取消调试
#if LDU_DE_BUG 
#define N 3
#endif

int LDU(double *mat, int n); // 输入n*n方阵

int LDU(double *mat, int n)
{
    if (!Doolittle(mat, n)) // 先用Doolittle算法计算LU分解
    {
        printf("ERROR\n");
        return 0;
    }
    for (int i = 0; i < n - 1; i++)
    {
        if (fabs(mat[i * n + i]) < EPSILON)
        {
            printf("ERROR\n");
            return 0;
        }
        for (int j = i + 1; j < n; j++)
        {
            mat[i * n + j] /= mat[i * n + i];
        }
    }
    return 1;
}

/*测试样例*/
#if LDU_DE_BUG
int main()
{
    double A[N * N] = {2, 1, -2,
                       1, -1, 2,
                       4, 1, -1};
    LDU(A,N);
    mat_print(A,N,N);
    return 0;
}
#endif