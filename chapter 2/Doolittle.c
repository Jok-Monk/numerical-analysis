#include<stdio.h>
#include<math.h>
#include"mat_print.h"

#define EPSILON 1e-10
#define N 4
// Doolittle 法求矩阵的LU分解
int Doolittle(double *mat ,int n );    //输入n*n的矩阵mat，并用doolittle算法分解为LU矩阵，分别存于mat的左下方，右上方，check=1则逐步输出计算结果，计算成功则放回1

int Doolittle(double *mat ,int n )
{
    for(int k=0;k<n;k++)
    {
        if(fabs(mat[k*n+k])<EPSILON)
        {
            printf("ERROR\n");
            return 0;
        }
        //   计算u_kk->u_kn
        //   计算l_(k+1)k->l_nk
        for(int j=0;j<k-1;j++)
        {
            mat[k*n+k]-=mat[k*n]*mat[k];
            for(int i=k+1;i<n;i++)
            {
                mat[k*n+i]-=mat[k*n+j]*mat[j*n+i];
                mat[i*n+k]-=mat[i*n+j]*mat[j*n+k];
                if(j==k-2)
                {
                    mat[i*n+k]/=mat[k*n+k];
                }
            }
        }
    }
    return 1;
}
        
int main()
{
   double A[N*N]= {1,2,1,-2,2,5,3,-2,-2,-2,3,5,1,3,2,3};
    Doolittle(A,N);
    mat_print(A,N,N);
    return 0;
}

