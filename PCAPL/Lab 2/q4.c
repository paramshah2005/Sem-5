#include <stdio.h>
#include <omp.h>

int main() {
    int N;
    printf("Enter the size N: ");
    scanf("%d", &N);

    int A[N][N], x[N], b[N];

    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of vector x:\n");
    for (int i = 0; i < N; i++) {
        scanf("%d", &x[i]);
    }

    double start_time = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        b[i] = 0;
        for (int j = 0; j < N; j++) {
            b[i] += A[i][j] * x[j];
        }
    }

    double end_time = omp_get_wtime();

    printf("Result vector b:\n");
    for (int i = 0; i < N; i++) {
        printf("%d\n", b[i]);
    }

    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
