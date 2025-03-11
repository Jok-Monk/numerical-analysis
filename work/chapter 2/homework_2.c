// 用Gauss消元法求矩阵  1 1
//                     1 2 1
//                       1 3 1
//                         1 4 1
//                           1 5    (5x5)
//的LU分解
#include<stdio.h>
#include<math.h>
#include"gauss&&LU.h"
int main() 
{
    double A[5*5]={1,1,0,0,0,1,2,1,0,0,0,1,3,1,0,0,0,1,4,1,0,0,0,1,5};
    double b[5];    //空参数
    gauss(A,b,5);
    printf("L:\n");
    for (int i = 0; i < 5; i++) //逐行输出
    {
        for (int j = 0; j < 5; j++) //遍历列
        {
            if (j < i)
            {
            printf("%10.6lf ", A[i * 5 + j]);
            }
            if (j == i)
            {
            printf("%10.6lf ", 1.0);
            }
            if (j > i)
            {
            printf("%10s ", " ");
            }
        }
        printf("\n");
        }
        printf("U:\n");
        for (int i = 0; i < 5; i++) //逐行输出
        {
        for (int j = 0; j < 5; j++) //遍历列
        {
            if (j >= i)
            {
            printf("%10.6lf ", A[i * 5 + j]);
            }
            if (j < i)
            {
            printf("%10s ", " ");
            }
        }
        printf("\n");
    }
    
    return 0;
}
