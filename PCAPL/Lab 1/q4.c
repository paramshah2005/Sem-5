#include<stdio.h>
#include<omp.h>

int main(){
	int n;
	printf("Enter array size: ");
	scanf("%d",&n);
	int arr1[n];
	int arr2[n];
	int totArr[n];
	printf("Enter array 1: \n");
	for(int i=0;i<n;i++){
		scanf("%d",&arr1[i]);
	}
	printf("Enter array 2: \n");
	for(int i=0;i<n;i++){
		scanf("%d",&arr2[i]);
	}
	int i;
	#pragma omp parallel for private(i)
	for(i=0;i<n;i++){
		totArr[i] = arr1[i] + arr2[i];
		printf("Thread %d computed element %d\n", omp_get_thread_num(), i);
	}
	printf("Resultant Array: ");
	for(int i=0;i<n;i++){
		printf("%d ",totArr[i]);
	}
}
