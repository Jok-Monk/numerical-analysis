// 求解方程:
// 1 -2 = 3
// 2  1 = 4
#include<stdio.h>
#include<math.h>
#include"gauss.h"
#include"upper triangle linear system.h"
#define n 2
int main() 
{
    double A[n*n]={1,-2,2,1};
    double x[n];
    double b[n]={3,4};
    if(gauss(A,b,n))
    {
        if(upper_triangle_linear_system(A,x,b,n))
        {
            for (int i = 0; i < n; i++)
            {
                printf("%lf ",x[i]);
            }
        }
        else
        {
            printf("ERROR: upper_triangle_linear_system");
        }
    }
    else
    {
        printf("ERROR: gauss");
    }
    return 0;
}