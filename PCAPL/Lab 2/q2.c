#include<stdio.h>
#include<omp.h>
int main(){
	int n=5;
	int A[n][n], B[n][n];
	printf("Enter the matrix: ");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%d",&A[i][j]);
		}
	}
	
	#pragma omp parallel for
	for(int i=0;i<n;i++){
		int tid = omp_get_thread_num();
		int max = A[i][0], min = A[i][0];
		for(int j=1;j<n;j++){
			if(A[i][j]>max){
				max = A[i][j];
			}
			if(A[i][j]<min){
				min = A[i][j];
			}
		}
		for(int j=0;j<5;j++){
            if(i==j){
                B[i][j]=0;
            }
            else if(i>j){
                B[i][j]=max;
            }
            else{
                B[i][j]=min;
            }
        }
		printf("Row %d processed by Thread %d\n",i,tid);
	}
	
	printf("\nMatrix A:\n");
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++)
            printf("%4d",A[i][j]);
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++)
            printf("%4d",B[i][j]);
        printf("\n");
    }
    return 0;
}

