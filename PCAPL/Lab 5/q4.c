#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size, n, i;
    char s1[100], s2[100];
    char p1[50], p2[50], result[200], part[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0){
        printf("Enter string 1: ");
        scanf("%s", s1);
        printf("Enter string 2: ");
        scanf("%s", s2);
        n = strlen(s1);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(s1, n / size, MPI_CHAR,p1, n / size, MPI_CHAR,0, MPI_COMM_WORLD);
    MPI_Scatter(s2, n / size, MPI_CHAR,p2, n / size, MPI_CHAR,0, MPI_COMM_WORLD);
    for (i = 0; i < n / size; i++){
        part[2 * i] = p1[i];
        part[2 * i + 1] = p2[i];
    }
    MPI_Gather(part, 2 * n / size, MPI_CHAR,result, 2 * n / size, MPI_CHAR,0, MPI_COMM_WORLD);

    if (rank == 0){
        result[2 * n] = '\0';
        printf("Resultant string: %s\n", result);
    }
    MPI_Finalize();
    return 0;
}
