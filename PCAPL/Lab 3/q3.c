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
    printf("Enter n\n");
    scanf("%d", &n);

    double start, end;

    start = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for(int i = 1; i <= n; i++)
    {
        if(isPrime(i))
        {
            printf("Static: %d\n", i);
        }
    }
    end = omp_get_wtime();
    printf("Static Time = %f\n", end - start);


    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic)
    for(int i = 1; i <= n; i++)
    {
        if(isPrime(i))
        {
            printf("Dynamic: %d\n", i);
        }
    }
    end = omp_get_wtime();
    printf("Dynamic Time = %f\n", end - start);


    start = omp_get_wtime();
    #pragma omp parallel for schedule(guided)
    for(int i = 1; i <= n; i++)
    {
        if(isPrime(i))
        {
            printf("Guided: %d\n", i);
        }
    }
    end = omp_get_wtime();
    printf("Guided Time = %f\n", end - start);

    return 0;
}
