#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int main(int argc, char *argv[]){
    int rank, size;
    int i;
    int fact = 1;
    int prefix_sum = 0;
    int error_code;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    for (i = 1; i <= rank + 1; i++){
        fact = fact * i;
    }
    error_code = MPI_Scan(&fact,&prefix_sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    if (error_code != MPI_SUCCESS){
        char error_string[MPI_MAX_ERROR_STRING];
        int error_length;
        MPI_Error_string(error_code,error_string,&error_length);
        printf("Process %d: MPI Error: %s\n",rank,error_string);
        MPI_Finalize();
        return 1;
    }
    if (rank == size - 1){
        printf("Sum of Factorials upto %d = %d\n",size,prefix_sum);
    }
    MPI_Finalize();
    return 0;
}	
