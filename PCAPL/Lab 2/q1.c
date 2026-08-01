#include <stdio.h>
#include <omp.h>

int main() {
    int m,n,i,j;
    printf("Enter rows and columns: ");
    scanf("%d%d",&m,&n);

    int A[m][n],B[m][n],C[m][n],D[m][n];

    printf("Enter Matrix A:\n");
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%d",&A[i][j]);
		}
	}
	
    printf("Enter Matrix B:\n");
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%d",&B[i][j]);
        }
    }

    double ss=omp_get_wtime();
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            C[i][j]=A[i][j]+B[i][j];
        }
    }    
    
    double se=omp_get_wtime();
    double ps=omp_get_wtime();
    
    #pragma omp parallel for private(j)
    for(i=0;i<m;i++){
        int tid=omp_get_thread_num();
        printf("Row %d processed by Thread %d\n",i,tid);
        for(j=0;j<n;j++)
            D[i][j]=A[i][j]+B[i][j];
    }
    double pe=omp_get_wtime();

    printf("\nResult Matrix:\n");
    for(i=0;i<m;i++){
        for(j=0;j<n;j++)
            printf("%4d",D[i][j]);
        printf("\n");
    }

    printf("\nSerial Time: %lf s\n",se-ss);
    printf("Parallel Time: %lf s\n",pe-ps);
    return 0;
}
