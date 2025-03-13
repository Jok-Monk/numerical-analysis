// 求解方程:
// 1 -2 = 3
// 2  1 = 4
#include<stdio.h>
#include<math.h>
#include"gauss_LU.h"
#include"solve_upper_triangle.h"
#include"mat_option.h"
#define n 2
int main() 
{
    double A[n*n]={1,-2,2,1};
    double x[n];
    double b[n]={3,4};
    if(gauss(A,b,n))
    {
        if(solve_upper_triangle(A,b,n))
        {
            mat_print(x,n,1);
        }
        else
        {
            printf("ERROR: solve_upper_triangle");
        }
    }
    else
    {
        printf("ERROR: gauss");
    }
    return 0;
}