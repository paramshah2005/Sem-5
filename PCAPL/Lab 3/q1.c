#include <stdio.h>
#include <omp.h>

int main()
{
    int n;
    printf("Enter N");
    scanf("%d",&n);

    int sum_shared = 0;
    #pragma omp parallel for shared(sum_shared)
    for(int i = 1; i <= n; i++)
    {
        sum_shared += i;
    }
    printf("Shared Sum = %d\n", sum_shared);
    
    int sum_private = 0;
    #pragma omp parallel for private(sum_private)
    for(int i = 1; i <= n; i++)
    {
        sum_private += i;
    }
    printf("Private Sum = %d\n", sum_private);

    int sum_firstprivate = 0;
    #pragma omp parallel for firstprivate(sum_firstprivate)
    for(int i = 1; i <= n; i++)
    {
        sum_firstprivate += i;
    }
    printf("Firstprivate Sum = %d\n", sum_firstprivate);

    int sum_lastprivate = 0;
    #pragma omp parallel for lastprivate(sum_lastprivate)
    for(int i = 1; i <= n; i++)
    {
        sum_lastprivate = i;
    }
    printf("Lastprivate Value = %d\n", sum_lastprivate);

    int sum_reduction = 0;
    #pragma omp parallel for reduction(+:sum_reduction)
    for(int i = 1; i <= n; i++)
    {
        sum_reduction += i;
    }
    printf("Reduction Sum = %d\n", sum_reduction);
    return 0;
}
