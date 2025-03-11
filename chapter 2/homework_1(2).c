// 求解方程:
// 1 1 -1 =  3
// 2 -1 3 =  0
//-1 -2 1 = -5
#include<stdio.h>
#include<math.h>
#include"gauss.h"
#include"upper triangle linear system.h"
#define n 3
int main() 
{
    double A[n*n]={1,1,-1,2,-1,3,-1,-2,1};
    double x[n];
    double b[n]={3,0,-5};
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