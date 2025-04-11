#include <stdio.h>
#include <math.h>
#include "Norm.h"
#include "Gauss_seidel.h"
#include "mat_option.h"
int main()
{
    double A[] = {8, -1, 1,
                  2, 10, -1,
                  1, 1, -5};
    double b[] = {1, 4, 3};
    double x[3];
    if (Gauss_seidel(A,b,x,3,100,1e-6))
    {
        mat_print(x,3,1);
    }
    return 0;
}