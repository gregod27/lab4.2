#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

void swap (int*a, int*b);
void arr_fill(int **arr, int x_size,int y_size);
void arr_make(int **arr, int x_size,int y_size);
void arr_print(int **arr, int x_size, int y_size);
void arr_print_num (int **arr, int x_size, int y_size);
void arr_clear (int **arr, int x_n);

void max_min ( int **A, int A_size, int *max_a , int *min_a );
int **arr_transpon (int **B, int n_b, int m_b );
int **arr_mult_a_b (int **A,int A_size, int **B, int B_rows, int B_columns);
int arr_sum (int **A,int A_size, int **B, int B_rows, int B_columns);
void arr_sort(int **A, int A_size, int var);

#define ARR_Size 7

int main ()
{
    int min_a, max_a, var;
    const int A_size = ARR_Size;
    const int B_rows = ARR_Size;
    int B_columns = 0;
    char do_again;

    printf("columns = ");
    scanf("%d", &B_columns);

    int **A= (int **)malloc(A_size * sizeof(int *));
    for (int i =0; i<A_size; i++)
        A[i]= (int *)malloc(A_size * sizeof(int));

    int **B=(int **) malloc(B_rows * sizeof(int *));
    for (int i =0; i<B_rows; i++)
        B[i]= (int *)malloc(B_columns * sizeof(int));
    int **C;

    arr_fill(A,A_size,A_size);
    arr_print_num(A,A_size,A_size);
    arr_fill(B,B_rows,B_columns);
    arr_print_num(B,B_rows,B_columns);

    printf("1|max_min\n2|transpon\n3|mult_a_b\n4|sort\n5|sum\nChoose a method");
    scanf("%d",&var );
    switch(var)
    {
    case 1:
        max_min(A,A_size,&min_a,&max_a);
        printf("min & max number,below the main diagonal\n min=&d; max = %d\n", min_a, max_a);
        break;

    case 2:
            C = arr_transpon(B, B_rows, B_columns);
            arr_print_num(C, B_columns, B_rows);
            arr_clear(C, B_columns);
            break;

    case 3:
            C = arr_mult_a_b(A, A_size, B, B_rows, B_columns);
            arr_print_num(C,B_rows,B_columns);
            arr_clear(C,B_rows);
            break;

    case 4:

          printf("enter row for sort, or \"1\", for sort matrix");
          scanf("%d", &var);
          arr_sort(A,A_size,var);
          arr_print_num(A,A_size,A_size);
          break;

    case 5:

          printf("total_sum = %d\n", arr_sum(A,A_size,B,B_rows,B_columns));
          break;

    }

    arr_clear(A,A_size);
    arr_clear(B,B_rows);
    printf("Enter\"s\" for stop program, or \"p\",for do again all");
    scanf("%s", &do_again);
    if (do_again == 'p')
        return main();
    getch();
    return 0;

}

void swap(int*a, int*b)
{
    int pp = *b;
    *b = *a;
    *a = pp;
}

void arr_fill(int**arr, int x_size, int y_size)
{
    for(int i=0; i<x_size; i++)
    for(int j=0; j<y_size; j++)
    arr[i][j]= 7 - i*j;

}

void arr_print_num(int **arr, int x_size, int y_size)
{
   printf("%2d",0);
   for(int j=1; j<=y_size; j++)
   printf("%5d",j);
   printf("\n");
   for(int i=0; i<x_size;i++)
   {
       printf("%2d||",i+1);
       for(int j=0; j<y_size;j++)
       printf("%5d",arr[i][j]);
       printf("||\n");
   }
    printf("\n");
}

void arr_clear(int **arr, int x_size)
{
    for(int i=0; i<x_size; i++)
    free(arr[i]);
    free(arr);
}

void max_min(int **A, int A_size, int *max_a, int *min_a)
{
    if(A_size>1)
    {
        *max_a = *min_a = A[1][0];
        for(int i=2; i<A_size; i++)
        {
            for(int j=0; j<i; j++)
            {
                if(A[i][j]<*min_a)
                    *max_a = A[i][j];
                else if (A[i][j]>*min_a)
                    *max_a = A[i][j];
            }
        }

    }
    else
        printf("wrong matrix");

}

int **arr_transpon(int **B, int B_rows, int B_columns)
{
    int C_rows = B_columns, C_columns = B_rows;
    int **C = (int **)malloc(C_rows * sizeof(int *));
    for(int i=0; i<C_rows; i++)
        C[i]=  (int *)malloc(C_columns * sizeof(int));
    for(int i=0; i<C_rows; i++)
    for(int j=0; j<C_columns; j++)
    C[i][j]=B[j][i];
    return C;
}

int **arr_mult_a_b(int **A, int A_size, int **B, int B_rows, int B_columns)
{
    if(A_size == B_rows)
    {
        int C_rows = A_size, C_columns = B_columns;
        int **C =(int **)malloc(C_rows * sizeof(int *));
        for(int i=0; i<C_rows;i++)
            C[i]=(int *)malloc(C_columns * sizeof(int));

        for(int i=0; i<C_rows; i++)
            for(int j=0; j<C_columns; j++)
            for(int n=0; n<A_size; n++)
            C[i][j] += A[i][n]*B[n][j];
        return C;

    }
    else
    {
        printf("not agreed\n");
        return 0;
    }

}

void arr_sort(int **A, int A_size, int var)
{
    printf("\n\n");
    if(var == 0)
    {
        int mink = A[0][0], *ind = &A[0][0];
        for(int i = 0; i< A_size; i++)
            for(int j = 0; j< A_size; j++)
        {
            mink = A[i][j];
            ind = &A[i][j];
            for(int ii=i, jj=j; ii<A_size; ii++, jj=0)
                for(jj; jj<A_size; jj++)
                if(A[ii][jj]<mink)
            {
                mink= A[ii][jj];
                ind= &A[ii][jj];
            }
        swap(&A[i][j],ind);
        }
    }
    else
    {
        int mink = A[var-1][0], *ind= &A[var-1][0];
        for(int j=0; j<A_size; j++)
        {
            mink= A[var-1][j];
            ind= &A[var-1][j];
            for(int jj=j; jj<A_size; jj++)
                if(A[var-1][jj]<mink)
            {
                mink = A[var-1][jj];
                ind = &A[var-1][jj];
            }
            swap(&A[var-1][j],ind);

        }

    }

}

int arr_sum(int **A, int A_size, int **B, int B_rows, int B_columns)
{
    int total_sum = 0;
    for(int i=0; i<A_size; i++)
        for(int j=0; j<A_size; j++)
        total_sum += A[i][j];
    for(int j=0; j<B_columns; j++)
        for(int i=0; i<B_rows; i++)
            total_sum += B[i][j];
    return total_sum;

}

