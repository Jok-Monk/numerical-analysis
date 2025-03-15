/*输入方阵A,代求置换p,求A的PLU分解PA=LU并返回p,LU. LU储存在A中*/
/*p[i]表示第i+1次消元列主元所在行数*/
/*未调试*/
#pragma once
#include<stdio.h>
#include<math.h>
#include"mat_option.h"


#define PLU_DE_BUG 0    // 1 调试该文件 0 取消调试
#if PLU_DE_BUG 
#define 
#endif
int PLU(double *mat, double *p, int n);// A[n][n],p[n]

int PLU(double *mat, double *p, int n)
{
    for (int i = 0; i < n - 1; i++) // 逐行消元
    {
        p[i] = chooseColumnPivot(mat, n, n, i, i); // 选取并记录列主元
        if (p[i] != i)                             // 若列主元与当前i元不一致，则交换行
        {
            swapRows(mat, n, n, p[i], i);
        }
        if (fabs(mat[i * n + i]) < EPSILON) // 判断主元是否为0
        {
            printf("The matrix is singular\n");
            return 0;
        }
        for (int j = i + 1; j < n; j++)
        {
            mat[j * n + i] /= mat[i * n + i]; // 将消去系数储存在mat的左下角
            for (int k = i + 1; k < n; k++)   // 用第i行消去第j行
            {
                mat[j * n + k] -= mat[j * n + i] * mat[i * n + k];
            }
        }
    }
}

/*测试样例*/
#if PLU_DE_BUG 
int main()
{

    return 0;
}
#endif
