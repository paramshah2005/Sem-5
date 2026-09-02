// Implement parallel Odd-Even Transposition Sort using MPI.

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, value, received, n, partner, phase, i;
    int *arr = NULL;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    n = size;
    if (rank == 0){
        printf("Enter %d elements:\n", n);
        arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL){
            printf("Memory allocation failed.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        for (i = 0; i < n; i++){
            scanf("%d", &arr[i]);
        }
    }
    MPI_Scatter(arr,1,MPI_INT,&value,1,MPI_INT,0,MPI_COMM_WORLD);
    for (phase = 0; phase < n; phase++){
        partner = -1;
        if (phase % 2 == 0){
            if (rank % 2 == 0){
                partner = rank + 1;
            }
            else{
                partner = rank - 1;
            }
        }
        else{
            if (rank % 2 == 0){
                partner = rank - 1;
            }
            else{
                partner = rank + 1;
            }
        }

        if (partner >= 0 && partner < size){
            MPI_Sendrecv(&value,1,MPI_INT,partner,0,&received,1,MPI_INT,partner,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            if (rank < partner){
                if (received < value){
                    value = received;
                }
            }
            else{
                if (received > value) {
                    value = received;
                }
            }
        }
    }
    MPI_Gather(&value,1,MPI_INT,arr,1,MPI_INT,0,MPI_COMM_WORLD);
    if (rank == 0){
        printf("Sorted elements:\n");
        for (i = 0; i < n; i++){
            printf("%d ", arr[i]);
        }
        printf("\n");
        free(arr);
    }
    MPI_Finalize();
    return 0;
}
