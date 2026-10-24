
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define MASK_WIDTH 3
#define TILE_WIDTH 256

__constant__ int M[MASK_WIDTH];

__global__ void tiledConvolution(int *N, int *P, int width) {
    __shared__ int tile[TILE_WIDTH + MASK_WIDTH - 1];

    int tx = threadIdx.x;
    int i = blockIdx.x * blockDim.x + tx;
    int radius = MASK_WIDTH / 2;
    int start = blockIdx.x * blockDim.x - radius;

    for (int j = tx; j < TILE_WIDTH + MASK_WIDTH - 1; j += blockDim.x) {
        int idx = start + j;
        tile[j] = (idx >= 0 && idx < width) ? N[idx] : 0;
    }

    __syncthreads();

    if (i < width) {
        int sum = 0;

        for (int j = 0; j < MASK_WIDTH; j++)
            sum += tile[tx + j] * M[j];

        P[i] = sum;
    }
}

int main() {
    int width;

    printf("Enter array size: ");
    scanf("%d", &width);

    int size = width * sizeof(int);

    int *N = (int *)malloc(size);
    int *P = (int *)malloc(size);
    int mask[MASK_WIDTH];

    printf("Enter input array:\n");
    for (int i = 0; i < width; i++)
        scanf("%d", &N[i]);

    printf("Enter mask elements:\n");
    for (int i = 0; i < MASK_WIDTH; i++)
        scanf("%d", &mask[i]);

    int *d_N, *d_P;

    cudaMalloc((void **)&d_N, size);
    cudaMalloc((void **)&d_P, size);

    cudaMemcpy(d_N, N, size, cudaMemcpyHostToDevice);
    cudaMemcpyToSymbol(M, mask, MASK_WIDTH * sizeof(int));

    tiledConvolution<<<(width + TILE_WIDTH - 1) / TILE_WIDTH, TILE_WIDTH>>>(d_N, d_P, width);

    cudaMemcpy(P, d_P, size, cudaMemcpyDeviceToHost);

    printf("Result:\n");
    for (int i = 0; i < width; i++)
        printf("%d ", P[i]);

    printf("\n");

    cudaFree(d_N);
    cudaFree(d_P);
    free(N);
    free(P);

    return 0;
}

