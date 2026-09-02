#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]){
    int rank, size, matrix[4][4], local_row[4], result_row[4], result_matrix[4][4];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 4){
        if (rank == 0){
            printf("Please run the program with exactly 4 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }
    if (rank == 0){
        printf("Enter the 4 x 4 matrix:\n");
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                scanf("%d", &matrix[i][j]);
            }
        }
    }
    MPI_Scatter(matrix,4,MPI_INT,local_row,4,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scan(local_row,result_row,4,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    MPI_Gather(result_row,4,MPI_INT,result_matrix,4,MPI_INT,0,MPI_COMM_WORLD);
    if (rank == 0){
        printf("\nOutput matrix:\n");
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                printf("%d ", result_matrix[i][j]);
            }
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}
