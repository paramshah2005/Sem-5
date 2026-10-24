#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
__global__ void addRow(int *a, int *b, int *c, int n) {
    int row = threadIdx.x;
    for (int j = 0; j < n; j++) {
        c[row * n + j] = a[row * n + j] + b[row * n + j];
    }
}
__global__ void addCol(int *a, int *b, int *c, int m, int n) {
    int col = threadIdx.x;
    for (int i = 0; i < m; i++) {
        c[i * n + col] = a[i * n + col] + b[i * n + col];
    }
}
__global__ void addElement(int *a, int *b, int *c, int n) {
    int row = threadIdx.y;
    int col = threadIdx.x;
    c[row * n + col] = a[row * n + col] + b[row * n + col];
}
void printMatrix(int *mat, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", mat[i * n + j]);
        }
        printf("\n");
    }
}
int main(void) {
    int *a, *b, *c, m, n, i;
    int *d_a, *d_b, *d_c;
    printf("Enter the value of m and n: ");
    scanf("%d %d", &m, &n);
    int size = sizeof(int) * m * n;
    a = (int*)malloc(size);
    b = (int*)malloc(size);
    c = (int*)malloc(size);
    printf("Enter input matrix A:\n");
    for (i = 0; i < m * n; i++) scanf("%d", &a[i]);
    printf("Enter input matrix B:\n");
    for (i = 0; i < m * n; i++) scanf("%d", &b[i]);
    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
    addRow<<<1, m>>>(d_a, d_b, d_c, n);
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
    printf("\nResult (1a - By Row):\n");
    printMatrix(c, m, n);
    addCol<<<1, n>>>(d_a, d_b, d_c, m, n);
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
    printf("\nResult (1b - By Column):\n");
    printMatrix(c, m, n);
    dim3 block_conf(n, m);
    addElement<<<1, block_conf>>>(d_a, d_b, d_c, n);
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
    printf("\nResult (1c - By Element):\n");
    printMatrix(c, m, n);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(a);
    free(b);
    free(c);
    return 0;
}
