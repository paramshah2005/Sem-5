#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
__global__ void transform(int *A, int *B, int rows, int cols) {
    int i = blockIdx.y * blockDim.y + threadIdx.y;
    int j = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < rows && j < cols) {
        int value = A[i * cols + j];
        int result = 1;
        for (int k = 0; k <= i; k++) {
            result *= value;
        }
        B[i * cols + j] = result;
    }
}
int main() {
    int rows, cols;
    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);
    int size = rows * cols * sizeof(int);
    int *A = (int *)malloc(size);
    int *B = (int *)malloc(size);
    printf("Enter matrix:\n");
    for (int i = 0; i < rows * cols; i++)
        scanf("%d", &A[i]);
    int *d_A, *d_B;
    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_B, size);
    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    dim3 threads(16, 16);
    dim3 blocks((cols + 15) / 16, (rows + 15) / 16);
    transform<<<blocks, threads>>>(d_A, d_B, rows, cols);
    cudaMemcpy(B, d_B, size, cudaMemcpyDeviceToHost);
    printf("Resultant Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", B[i * cols + j]);
        }
        printf("\n");
    }
    cudaFree(d_A);
    cudaFree(d_B);
    free(A);
    free(B);
    return 0;
}
