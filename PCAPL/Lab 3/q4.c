#include <stdio.h>
#include <omp.h>

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n], arr_copy[n];

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        arr_copy[i] = arr[i];
    }

    double start, end;

    start = omp_get_wtime();

    for(int size = 1; size < n; size *= 2)
    {
        for(int left = 0; left < n - 1; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? left + 2 * size - 1 : n - 1;

            if(mid < right)
                merge(arr, left, mid, right);
        }
    }

    end = omp_get_wtime();
    printf("Serial Time = %f\n", end - start);

    start = omp_get_wtime();

    for(int size = 1; size < n; size *= 2)
    {
        #pragma omp parallel for
        for(int left = 0; left < n - 1; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? left + 2 * size - 1 : n - 1;

            if(mid < right)
                merge(arr_copy, left, mid, right);
        }
    }

    end = omp_get_wtime();
    printf("Parallel Time = %f\n", end - start);

    for(int i = 0; i < n; i++)
        printf("%d ", arr_copy[i]);

    printf("\n");

    return 0;
}
