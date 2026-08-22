#include<stdio.h>
#include<mpi.h>
#include<string.h>

int main(int argc, char *argv[]){
	int rank ,size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	char x[100];
	if(rank==0){
		printf("Enter String to Transmit: ");
		scanf("%s",x);
		printf("Process 0: Sending %s\n",x);
		MPI_Ssend(x, strlen(x)+1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Recv(x, 100, MPI_CHAR, 1, 1, MPI_COMM_WORLD, &status);
        printf("Process 0: Received toggled word = %s\n", x);
	}
	else if(rank == 1){
		MPI_Recv(x, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
		printf("Process 1: Received %s\n", x);
        for (int i = 0; x[i] != '\0'; i++)
        {
            if (x[i] >= 'A' && x[i] <= 'Z')
                x[i] += 32;
            else if (x[i] >= 'a' && x[i] <= 'z')
                x[i] -= 32;
        }
        MPI_Barrier(MPI_COMM_WORLD);
		MPI_Ssend(x, strlen(x) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
