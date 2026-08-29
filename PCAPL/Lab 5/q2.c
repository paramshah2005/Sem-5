#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int rank, size, m;
    int a[100], part[20], i;
    float avg, result[20], total = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0){
        printf("Enter M: ");
        scanf("%d", &m);
        printf("Enter %d values: ", size * m);
        for (i = 0; i < size * m; i++)
            scanf("%d", &a[i]);
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(a, m, MPI_INT, part, m, MPI_INT,0, MPI_COMM_WORLD);
    avg = 0;
    for (i = 0; i < m; i++){
        avg += part[i];
    }
    avg /= m;
    printf("Process %d: Average = %.2f\n", rank, avg);
    MPI_Gather(&avg, 1, MPI_FLOAT, result, 1, MPI_FLOAT,0, MPI_COMM_WORLD);
    if (rank == 0){
        for (i = 0; i < size; i++){
            total += result[i];
		}
        printf("Total Average = %.2f\n", total / size);
    }
    MPI_Finalize();
    return 0;
}
