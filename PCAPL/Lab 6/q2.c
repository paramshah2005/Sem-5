#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]){
    int rank, size, matrix[3][3], row[3], key, local_count=0, total_count=0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 3){
        if (rank == 0){
            printf("Run the program using exactly 3 processes.\n");
		}
        MPI_Finalize();
        return 0;
    }
    if (rank == 0){
        printf("Enter the elements of the 3 x 3 matrix:\n");
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                scanf("%d", &matrix[i][j]);
            }
        }
        printf("Enter the element to be searched: ");
        scanf("%d", &key);
    }
    MPI_Scatter(matrix, 3, MPI_INT,row, 3, MPI_INT,0, MPI_COMM_WORLD);
    MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < 3; i++){
        if (row[i] == key){
            local_count++;
        }
    }
    MPI_Reduce(&local_count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0){
        printf("Number of occurrences of %d = %d\n", key, total_count);
	}
    MPI_Finalize();
    return 0;
}
