#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size, n, count = 0;
    int result[20], i;
    char str[100], part[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        printf("Enter string: ");
        scanf("%s", str);

        n = strlen(str);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(str, n / size, MPI_CHAR,part, n / size, MPI_CHAR,0, MPI_COMM_WORLD);
    for (i = 0; i < n / size; i++){
        if (part[i] != 'a' && part[i] != 'e' &&
            part[i] != 'i' && part[i] != 'o' &&
            part[i] != 'u')
            count++;
    }
    printf("Process %d: Non-vowels = %d\n", rank, count);
    MPI_Gather(&count, 1, MPI_INT, result, 1, MPI_INT,0, MPI_COMM_WORLD);
    if (rank == 0){
        count = 0;
        for (i = 0; i < size; i++){
            count += result[i];
		}
        printf("Total non-vowels = %d\n", count);
    }
    MPI_Finalize();
    return 0;
}
