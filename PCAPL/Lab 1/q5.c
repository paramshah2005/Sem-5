#include <stdio.h>
#include <omp.h>

int main() {
    int m, n;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &m, &n);

    int a[m][n], b[m][n], c[m][n];

    printf("Enter Matrix 1:\n");
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    printf("Enter Matrix 2:\n");
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &b[i][j]);
        }
    }
    #pragma omp parallel for
    for(int i = 0; i < m; i++) {
        int tid = omp_get_thread_num();
        for(int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
        printf("Row %d computed by Thread %d\n", i, tid);
    }
    printf("Resultant Matrix:\n");
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            printf("%4d", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}
