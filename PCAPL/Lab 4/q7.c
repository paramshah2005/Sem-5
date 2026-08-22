#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	int rank,size,val;
	int *buffer;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	buffer = malloc(size * (sizeof(int) + MPI_BSEND_OVERHEAD));
	MPI_Buffer_attach(buffer,size * (sizeof(int) + MPI_BSEND_OVERHEAD));
	if(rank == 0){
		int a[size];
		printf("Enter array: ");
		for(int i=0;i<size;i++)
			scanf("%d", &a[i]);
		for(int i=1;i<size;i++)
			MPI_Bsend(&a[i-1], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		val = a[0];
	}
	else{
		MPI_Recv(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		if(rank % 2 ==0){
			printf("Process %d Received %d Squared %d\n" , rank, val,val*val);
		}
		else{
			printf("Process %d Received %d Cubed %d\n" , rank, val,val*val*val);
		}
	}
	MPI_Buffer_detach(&buffer, &size);
    free(buffer);
	MPI_Finalize();
	return 0;
}
