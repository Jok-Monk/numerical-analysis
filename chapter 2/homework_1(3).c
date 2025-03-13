// 求解方程:
// 3 -1  2 = -3
// 1  1  1 = -4
// 2  1 -1 = -3
#include<stdio.h>
#include<math.h>
#include"gauss_LU.h"
#include"solve_upper_triangle.h"
#include"mat_option.h"
#define n 3
int main() 
{
    double A[n*n]={3,-1,2,1,1,1,2,1,-1};
    double x[n];
    double b[n]={-3,-4,-3};
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