#include <stdio.h>
#include <omp.h>

int main() 
{
    int n;

    printf("Enter array size: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter array elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    long long serialSum = 0, parallelSum = 0;
    double start, end;
    double serialTime, parallelTime;

    start = omp_get_wtime();

    for (int i = 0; i < n; i++) {
        serialSum += a[i];
    }

    end = omp_get_wtime();
    serialTime = end - start;

    start = omp_get_wtime();

    #pragma omp parallel for 
		for (int i = 0; i < n; i++) {
		    parallelSum += a[i];
		}
    end = omp_get_wtime();
    parallelTime = end - start;

    printf("Serial Sum = %lld\n", serialSum);
    printf("Parallel Sum = %lld\n", parallelSum);
    printf("Serial Time = %f seconds\n", serialTime);
    printf("Parallel Time = %f seconds\n", parallelTime);

    return 0;
}

