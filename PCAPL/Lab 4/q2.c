#include <mpi.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size;
    char str[] = "HELLO";
    char ch;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank < strlen(str)){
        ch = str[rank];

        if (islower(ch))
            ch = toupper(ch);
        else
            ch = tolower(ch);

        printf("Process %d: %c -> %c\n", rank, str[rank], ch);
    }
    MPI_Finalize();
    return 0;
}
