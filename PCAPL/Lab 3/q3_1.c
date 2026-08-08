#include <stdio.h>
#include <omp.h>

int isPrime(int num)
{
    if(num < 2) return 0;
    for(int i = 2; i * i <= num; i++)
    {
        if(num % i == 0) return 0;
    }
    return 1;
}

int main()
{
    int n;

    printf("Enter value of N: ");
    scanf("%d", &n);

    double start = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for(int i = 1; i <= n; i++)
    {
        if(isPrime(i))
        {
            int tid = omp_get_thread_num();
            printf("Prime %d found by thread %d\n", i, tid);
        }
    }

    double end = omp_get_wtime();
    printf("Time = %f\n", end - start);

    return 0;
}
