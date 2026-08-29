#include <mpi.h>
#include <stdio.h>

int factorial(int n)
{
    int f = 1, i;
    for(i = 1; i <= n; i++){
        f *= i;
    }
    return f;
}

int main(int argc, char *argv[])
{
    int r, s, x, a[100], res[100], sum = 0, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    if(r == 0){
        printf("Enter %d values: ", s);
        for(i = 0; i < s; i++){
            scanf("%d", &a[i]);
        }
    }

    MPI_Scatter(a, 1, MPI_INT, &x, 1, MPI_INT, 0, MPI_COMM_WORLD);
    x = factorial(x);
    printf("P%d: Factorial = %d\n", r, x);
    MPI_Gather(&x, 1, MPI_INT, res, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(r == 0){
        for(i = 0; i < s; i++){
            sum += res[i];
        }
        printf("Sum = %d\n", sum);
    }
    MPI_Finalize();
    return 0;
}
