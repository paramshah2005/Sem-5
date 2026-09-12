#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>
#include <time.h>

#define THREADS 256

__global__ void distance(float *a, float *b, float *result, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
    {
        float x = a[i] - b[i];
        atomicAdd(result, x * x);
    }
}

int main()
{	
	srand(time(NULL));
    int n, i;
    float *a, *b;
    float result = 0;

    float *d_a, *d_b, *d_result;

    printf("Enter N: ");
    scanf("%d", &n);

    a = (float *)malloc(n * sizeof(float));
    b = (float *)malloc(n * sizeof(float));

    for (i = 0; i < n; i++)
    {
        a[i] = rand() % 10;
        b[i] = rand() % 10;
    }

    cudaMalloc((void **)&d_a, n * sizeof(float));
    cudaMalloc((void **)&d_b, n * sizeof(float));
    cudaMalloc((void **)&d_result, sizeof(float));

    cudaMemcpy(d_a, a, n * sizeof(float),
               cudaMemcpyHostToDevice);

    cudaMemcpy(d_b, b, n * sizeof(float),
               cudaMemcpyHostToDevice);

    cudaMemcpy(d_result, &result, sizeof(float),
               cudaMemcpyHostToDevice);

    int blocks = (n + THREADS - 1) / THREADS;

    printf("Threads per block = %d\n", THREADS);
    printf("Number of blocks = %d\n", blocks);

    distance<<<blocks, THREADS>>>(d_a, d_b, d_result, n);

    cudaMemcpy(&result, d_result, sizeof(float),
               cudaMemcpyDeviceToHost);

    result = sqrt(result);

    printf("Euclidean Distance = %f\n", result);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_result);

    free(a);
    free(b);

    return 0;
}
