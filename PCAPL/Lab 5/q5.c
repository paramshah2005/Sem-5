#include <mpi.h>
#include <stdio.h>

void selectionSort(int a[], int n){
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++){
        min = i;
        for (j = i + 1; j < n; j++){
            if (a[j] < a[min]){
                min = j;
            }
        }
        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

void merge(int a[], int l, int m, int r){
    int temp[100];
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r){
        if (a[i] < a[j]){
            temp[k] = a[i];
            i++;
        }
        else{
            temp[k] = a[j];
            j++;
        }
        k++;
    }

    while (i <= m){
        temp[k] = a[i];
        i++;
        k++;
    }

    while (j <= r){
        temp[k] = a[j];
        j++;
        k++;
    }
    for (i = l, k = 0; i <= r; i++, k++){
        a[i] = temp[k];
    }
}

void mergeSort(int a[], int l, int r){
    int m;

    if (l < r){
        m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int main(int argc, char *argv[]){
    int rank, size, n;
    int a[100], part[100], i;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0){
        printf("Enter number of elements: ");
        scanf("%d", &n);
        printf("Enter elements: ");
        for (i = 0; i < n; i++){
            scanf("%d", &a[i]);
        }
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(a, n / size, MPI_INT,part, n / size, MPI_INT,0, MPI_COMM_WORLD);
    selectionSort(part, n / size);
    MPI_Gather(part, n / size, MPI_INT,a, n / size, MPI_INT,0, MPI_COMM_WORLD);
    if (rank == 0){
        mergeSort(a, 0, n - 1);
        printf("Sorted array: ");
        for (i = 0; i < n; i++){
            printf("%d ", a[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}
