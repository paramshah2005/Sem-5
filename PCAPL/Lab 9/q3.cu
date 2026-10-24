#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void spmv(int *values, int *col_idx, int *row_ptr, int *x, int *y, int rows) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < rows) {
        int sum = 0;
        for (int j = row_ptr[i]; j < row_ptr[i + 1]; j++) {
            sum += values[j] * x[col_idx[j]];
        }
        y[i] = sum;
    }
}
int main() {
    int rows, cols, nnz = 0;
    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);
    int *A = (int *)malloc(rows * cols * sizeof(int));
    int *values = (int *)malloc(rows * cols * sizeof(int));
    int *col_idx = (int *)malloc(rows * cols * sizeof(int));
    int *row_ptr = (int *)malloc((rows + 1) * sizeof(int));
    int *x = (int *)malloc(cols * sizeof(int));
    int *y = (int *)malloc(rows * sizeof(int));
    printf("Enter matrix:\n");
    for (int i = 0; i < rows * cols; i++)
        scanf("%d", &A[i]);
    row_ptr[0] = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (A[i * cols + j] != 0) {
                values[nnz] = A[i * cols + j];
                col_idx[nnz] = j;
                nnz++;
            }
        }
        row_ptr[i + 1] = nnz;
    }
    printf("Enter vector:\n");
    for (int i = 0; i < cols; i++)
        scanf("%d", &x[i]);
    int *d_values, *d_col_idx, *d_row_ptr, *d_x, *d_y;
    cudaMalloc((void **)&d_values, nnz * sizeof(int));
    cudaMalloc((void **)&d_col_idx, nnz * sizeof(int));
    cudaMalloc((void **)&d_row_ptr, (rows + 1) * sizeof(int));
    cudaMalloc((void **)&d_x, cols * sizeof(int));
    cudaMalloc((void **)&d_y, rows * sizeof(int));
    cudaMemcpy(d_values, values, nnz * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_col_idx, col_idx, nnz * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_row_ptr, row_ptr, (rows + 1) * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, x, cols * sizeof(int), cudaMemcpyHostToDevice);
    spmv<<<(rows + 255) / 256, 256>>>(d_values, d_col_idx, d_row_ptr, d_x, d_y, rows);
    cudaMemcpy(y, d_y, rows * sizeof(int), cudaMemcpyDeviceToHost);
    printf("Result:\n");
    for (int i = 0; i < rows; i++)
        printf("%d ", y[i]);
    printf("\n");
    cudaFree(d_values);
    cudaFree(d_col_idx);
    cudaFree(d_row_ptr);
    cudaFree(d_x);
    cudaFree(d_y);
    free(A);
    free(values);
    free(col_idx);
    free(row_ptr);
    free(x);
    free(y);
    return 0;
}
