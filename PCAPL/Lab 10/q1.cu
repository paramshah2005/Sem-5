
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define MASK_WIDTH 3

__constant__ int M[MASK_WIDTH];

__global__ void convolution(int *N, int *P, int width) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int sum = 0;

    if (i < width) {
        for (int j = 0; j < MASK_WIDTH; j++) {
            int idx = i + j - MASK_WIDTH / 2;

            if (idx >= 0 && idx < width)
                sum += N[idx] * M[j];
        }

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

    convolution<<<(width + 255) / 256, 256>>>(d_N, d_P, width);

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

