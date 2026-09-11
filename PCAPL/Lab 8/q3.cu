#include <stdio.h>
#include <cuda.h>

__global__ void rankSort(int *a, int *b, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int rank = 0;

    if (i < n)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[j] < a[i] || (a[j] == a[i] && j < i))
                rank++;
        }
        b[rank] = a[i];
    }
}

int main()
{
    int n, i;
    int *a, *b;
    int *d_a, *d_b;

    printf("Enter N: ");
    scanf("%d", &n);

    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    cudaMalloc((void **)&d_a, n * sizeof(int));
    cudaMalloc((void **)&d_b, n * sizeof(int));

    cudaMemcpy(d_a, a, n * sizeof(int), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n + threads - 1) / threads;

    rankSort<<<blocks, threads>>>(d_a, d_b, n);

    cudaMemcpy(b, d_b, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted array:\n");
    for (i = 0; i < n; i++)
        printf("%d ", b[i]);
    printf("\n");

    cudaFree(d_a);
    cudaFree(d_b);

    free(a);
    free(b);

    return 0;
}
