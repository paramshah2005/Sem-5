#include <stdio.h>
#include <omp.h>

int main()
{
    int n;
    printf("Enter size of array\n");
    scanf("%d", &n);

    int arr[n];
	printf("Enter the array\n");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int sum = 0;
    int even_count = 0;

    #pragma omp parallel
    {
        #pragma omp master
        {
            printf("Total Threads = %d\n", omp_get_num_threads());
        }
    }

    #pragma omp parallel
    {
        int local_sum = 0;
        int tid = omp_get_thread_num();

        #pragma omp for reduction(+:sum)
        for(int i = 0; i < n; i++)
        {
            sum += arr[i];
        }

        #pragma omp for
        for(int i = 0; i < n; i++)
        {
            if(arr[i] % 2 == 0)
            {
                #pragma omp atomic
                even_count++;
            }
        }

        #pragma omp for
        for(int i = 0; i < n; i++)
        {
            local_sum += arr[i];
        }

        #pragma omp critical
        {
            printf("Thread %d local sum = %d\n", tid, local_sum);
        }
    }

    #pragma omp parallel
    {
        #pragma omp master
        {
            printf("Final Sum = %d\n", sum);
            printf("Even Count = %d\n", even_count);
        }
    }

    return 0;
}
