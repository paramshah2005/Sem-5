#include <stdio.h>
#include <omp.h>

int main()
{
    int n, i;

    printf("Enter the size of the vectors: ");
    scanf("%d", &n);

    int A[n], B[n], Add[n], Sub[n], Mul[n];

    printf("Enter elements of Vector A:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("Enter elements of Vector B:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &B[i]);

    double start = omp_get_wtime();

	#pragma omp parallel sections private(i)
	{
		#pragma omp section
		{
		    for(i = 0; i < n; i++)
		        Add[i] = A[i] + B[i];
		}

		#pragma omp section
		{
		    for(i = 0; i < n; i++)
		        Sub[i] = A[i] - B[i];
		}

		#pragma omp section
		{
		    for(i = 0; i < n; i++)
		        Mul[i] = A[i] * B[i];
		}
	}
    double end = omp_get_wtime();

    printf("\nA\tB\tAdd\tSub\tMul\n");
    for(i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\n", A[i], B[i], Add[i], Sub[i], Mul[i]);

    printf("\nExecution Time = %f seconds\n", end - start);

    return 0;
}
