// 用追赶法求解下列n阶方程组
// -4   1               =  -27
//  1  -4  1            =  -15
//    ...   ...         =  ...
//       1  -4   1      =  -15
//           1  -4      =  -15
// n 取 10 和 100


#include <stdio.h>
#include <math.h>
#include "mat_option.h"
#include "Thomas.h"
#define n 100
int main()
{
    double f[n - 1]; // 上对角线
    double e[n];     // 主对角线
    double d[n - 1]; // 下对角线
    double b[n];     // 右端向量
    // 为矩阵和向量赋值
    f[0] = 1;
    d[0] = 1;
    e[0] = -4;
    b[0] = -27;
    for (int i = 1; i < n - 1; i++)
    {

        f[i] = 1;
        d[i] = 1;
        e[i] = -4;
        b[i] = -15;
    }
    e[n - 1] = -4;
    b[n - 1] = -15;
    if (Thomas(f, e, d, b, n, 1))
    {
        mat_print(b, n, 1);
    }
    else
    {
        printf("ERROR\n");
    }
    return 0;
}