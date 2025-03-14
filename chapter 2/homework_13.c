// 设有n阶方程组
// 3 1          x_1     = 4
// 9 3 1        x_2     = 13
// ...          ...     = 13
//      9 3 1   x_(n-1) = 13
//        9 3   x_n     = 12
// 取n=10和100,分别用Gauss消元法和列主元消去法求解
// PS. 由于该矩阵的第二阶顺序主子式为0,故无法使用Gauss消元法
// n 较大时，使用列主元消去法数值不稳定?
// n 较大时，列主元消去法得到的矩阵前n-1个对角元均为9，而D_n~3^n，因此最后一个主元极小(若矩阵非异)，出现小数作为分母的情况
// 方阵行列式满足递推关系式 D_n = 3*D_(n-1) - 9*D_(n-2) , D_1 = 3 , D_2 = 0
// 令F_n=D_n/(3^n),则 F_n = F_(n-1) - F_(n-2) , F_1 = 1 , F_2  = 0
// F_1 F_2 F_3 F_4 F_5 F_6 F_7 F_8
// 1   0   -1  -1  0   1   1   0  
// 6-循环
// 100 == 4 (mod 6)
// 故 D_100 = -3^100
// 列主元消去法得到的 A_(100,100) = D_100/9^99 = 3^(-98)

#include <stdio.h>
#include <math.h>
#include "mat_option.h"
#include "gauss_LU.h"
#include "gaussColumnPivot.h"

#define n 60    // 代求方程组阶数
#define choice 0 // 1 为Gauss消元法 , 0 为列主元消去法
int main()
{
    /* // 预计算A的行列式(错误，D_n~3^n，n较大时数字溢出)
    long long D1 = 3;
    long long D2 = 0;
    for (int i = 1; i <= n - 2; i++)
    {
        D1 = 3 * D2 - 9 * D1;
        D1 = D1 + D2;
        D2 = D1 - D2;
        D1 = D1 - D2;
        //printf("%d\n", D2);
    }
    printf("det(A)=%d\n", D2);*/

    // 对矩阵和向量赋值
    double A[n * n];
    double b[n];
    for (int i = 0; i < n; i++)
    {
        // 给b赋值
        if (i == 0)
        {
            b[i] = 4;
        }
        else if (i == n - 1)
        {
            b[i] = 12;
        }
        else
        {
            b[i] = 13;
        }
        // 给A赋值
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                A[i * n + j] = 3;
            }
            else if (i == j - 1)
            {
                A[i * n + j] = 1;
            }
            else if (i == j + 1)
            {
                A[i * n + j] = 9;
            }
            else
            {
                A[i * n + j] = 0;
            }
        }
    }
    if (choice == 1)
    {
        if (!gauss(A, b, n))
        {
            printf("ERROR\n");
        }
        else
        {
            mat_print(b, n, 1);
        }
    }
    else
    {
        if (!gaussColumnPivot(A, b, n))
        {
            printf("ERROR\n");
        }
        else
        {
            mat_print(b, n, 1);
        }
    }
    return 0;
}
