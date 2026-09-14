#include <stdio.h>
#include <cuda.h>

__global__ void convolution_1D_basic_kernel(float *N, float *M, float *P, int mask, int width)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    float value = 0;
    int start = i - mask / 2;

    if (i < width)
    {
        for (int j = 0; j < mask; j++)
        {
            if (start + j >= 0 && start + j < width)
            {
                value += N[start + j] * M[j];
            }
        }
        P[i] = value;
    }
}

int main()
{
    int width, mask_width;
    float *N, *M, *P, *d_N, *d_M, *d_P;

    printf("Enter width of input array: ");
    scanf("%d", &width);
    N = (float *)malloc(width * sizeof(float));
    P = (float *)malloc(width * sizeof(float));

    printf("Enter %d elements of input array:\n", width);
    for (int i = 0; i < width; i++)
    {
        scanf("%f", &N[i]);
    }

    printf("Enter mask width (odd number): ");
    scanf("%d", &mask_width);
    M = (float *)malloc(mask_width * sizeof(float));

    printf("Enter %d elements of mask array:\n", mask_width);
    for (int i = 0; i < mask_width; i++)
    {
        scanf("%f", &M[i]);
    }

    cudaMalloc((void **)&d_N, width * sizeof(float));
    cudaMalloc((void **)&d_M, mask_width * sizeof(float));
    cudaMalloc((void **)&d_P, width * sizeof(float));
    cudaMemcpy(d_N, N, width * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, M, mask_width * sizeof(float), cudaMemcpyHostToDevice);

    const int threads = 256;
    int blocks = (width + threads - 1) / threads;
    convolution_1D_basic_kernel<<<blocks, threads>>>(d_N, d_M, d_P, mask_width, width);
    cudaMemcpy(P, d_P, width * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Resultant array P:\n");
    for (int i = 0; i < width; i++)
    {
        printf("%.2f ", P[i]);
    }
    printf("\n");

    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);
    free(N);
    free(M);
    free(P);
    return 0;
}
