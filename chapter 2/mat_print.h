#ifndef MAT_PRINT_H
#define MAT_PRINT_H
void mat_print(double *mat ,int rows, int cols);
void mat_print(double *mat ,int rows, int cols)
{
for (int i = 0; i < rows; i++)
{ 
    for (int j = 0; j < cols; j++)
    {
        printf("%10.6lf ", mat[i * cols + j]);
    }
    printf("\n");
                
}
}
#endif
