#include <stdio.h>
#include <cuda.h>

__global__ void add(int *a, int *b, int *c, int n)
{
    int i = threadIdx.x;

    if (i < n)
        c[i] = a[i] + b[i];
}

int main()
{
    int n, i;
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;

    printf("Enter N: ");
    scanf("%d", &n);

    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    c = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
    {
        a[i] = i + 1;
        b[i] = i + 1;
    }

    cudaMalloc((void **)&d_a, n * sizeof(int));
    cudaMalloc((void **)&d_b, n * sizeof(int));
    cudaMalloc((void **)&d_c, n * sizeof(int));

    cudaMemcpy(d_a, a, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, n * sizeof(int), cudaMemcpyHostToDevice);

    add<<<1, n>>>(d_a, d_b, d_c, n);

    cudaMemcpy(c, d_c, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Result:\n");

    for (i = 0; i < n; i++)
        printf("%d ", c[i]);
    printf("\n");
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    free(a);
    free(b);
    free(c);

    return 0;
}
