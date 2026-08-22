#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int value;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    if (rank == 0){
        printf("Enter an integer: ");
        scanf("%d", &value);
        printf("Process 0: Initial value = %d\n", value);
        value++;
        MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);
        printf("Process 0: Final value = %d\n", value);
    }
    else{
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        printf("Process %d: Received %d\n", rank, value);
        value++;
        if (rank == size - 1)
            MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        else
            MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
