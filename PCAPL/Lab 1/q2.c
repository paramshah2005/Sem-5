#include <stdio.h>
#include <omp.h>

int main()
{
    int n;

    printf("Enter number of threads: ");
    scanf("%d", &n);

    omp_set_num_threads(n);

    #pragma omp parallel
    {
        printf("Hello from Thread %d\n", omp_get_thread_num());
    }

    return 0;
}
