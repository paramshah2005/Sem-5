#include <stdio.h>
#include <math.h>
#include <cuda.h>

__global__ void sine(float *a, float *b, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
        b[i] = sin(a[i]);
}

int main()
{
    int n, i;
    float *a, *b;
    float *d_a, *d_b;

    printf("Enter N: ");
    scanf("%d", &n);

    a = (float *)malloc(n * sizeof(float));
    b = (float *)malloc(n * sizeof(float));

    printf("Enter angles in radians:\n");

    for (i = 0; i < n; i++)
        scanf("%f", &a[i]);

    cudaMalloc((void **)&d_a, n * sizeof(float));
    cudaMalloc((void **)&d_b, n * sizeof(float));

    cudaMemcpy(d_a, a, n * sizeof(float),
               cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n + threads - 1) / threads;

    sine<<<blocks, threads>>>(d_a, d_b, n);

    cudaMemcpy(b, d_b, n * sizeof(float),
               cudaMemcpyDeviceToHost);

    printf("Sine values:\n");

    for (i = 0; i < n; i++)
        printf("%f ", b[i]);

    printf("\n");

    cudaFree(d_a);
    cudaFree(d_b);

    free(a);
    free(b);

    return 0;
}