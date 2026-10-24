#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
__global__ void mulRow(int *a, int *b, int *c, int n, int p) {
    int row = threadIdx.x;
    for (int col = 0; col < p; col++) {
        int sum = 0;
        for (int k = 0; k < n; k++) {
            sum += a[row * n + k] * b[k * p + col];
        }
        c[row * p + col] = sum;
    }
}
__global__ void mulCol(int *a, int *b, int *c, int m, int n, int p) {
    int col = threadIdx.x;
    for (int row = 0; row < m; row++) {
        int sum = 0;
        for (int k = 0; k < n; k++) {
            sum += a[row * n + k] * b[k * p + col];
        }
        c[row * p + col] = sum;
    }
}
__global__ void mulElement(int *a, int *b, int *c, int n, int p) {
    int row = threadIdx.y;
    int col = threadIdx.x;
    int sum = 0;
    for (int k = 0; k < n; k++) {
        sum += a[row * n + k] * b[k * p + col];
    }
    c[row * p + col] = sum;
}
void printMatrix(int *mat, int m, int p) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%d\t", mat[i * p + j]);
        }
        printf("\n");
    }
}
int main(void) {
    int *a, *b, *c, m, n, p, i;
    int *d_a, *d_b, *d_c;
    printf("Enter dimensions of Matrix A (m x n): ");
    scanf("%d %d", &m, &n);
    printf("Enter columns of Matrix B (p): ");
    scanf("%d", &p);
    int sizeA = sizeof(int) * m * n;
    int sizeB = sizeof(int) * n * p;
    int sizeC = sizeof(int) * m * p;
    a = (int*)malloc(sizeA);
    b = (int*)malloc(sizeB);
    c = (int*)malloc(sizeC);
    printf("Enter Matrix A (%d x %d):\n", m, n);
    for (i = 0; i < m * n; i++) scanf("%d", &a[i]);
    printf("Enter Matrix B (%d x %d):\n", n, p);
    for (i = 0; i < n * p; i++) scanf("%d", &b[i]);
    cudaMalloc((void**)&d_a, sizeA);
    cudaMalloc((void**)&d_b, sizeB);
    cudaMalloc((void**)&d_c, sizeC);
    cudaMemcpy(d_a, a, sizeA, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, sizeB, cudaMemcpyHostToDevice);
    mulRow<<<1, m>>>(d_a, d_b, d_c, n, p);
    cudaMemcpy(c, d_c, sizeC, cudaMemcpyDeviceToHost);
    printf("\nResult (2a - By Row):\n");
    printMatrix(c, m, p);
    mulCol<<<1, p>>>(d_a, d_b, d_c, m, n, p);
    cudaMemcpy(c, d_c, sizeC, cudaMemcpyDeviceToHost);
    printf("\nResult (2b - By Column):\n");
    printMatrix(c, m, p);
    dim3 block_conf(p, m);
    mulElement<<<1, block_conf>>>(d_a, d_b, d_c, n, p);
    cudaMemcpy(c, d_c, sizeC, cudaMemcpyDeviceToHost);
    printf("\nResult (2c - By Element):\n");
    printMatrix(c, m, p);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(a);
    free(b);
    free(c);
    return 0;
}
