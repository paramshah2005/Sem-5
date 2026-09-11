#include <stdio.h>
#include <cuda.h>

__global__ void convolution_1D_basic_kernel(float *N, float *M, float *P,
                                             int Mask_Width, int Width)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    float Pvalue = 0;
    int N_start_point = i - (Mask_Width / 2);

    if (i < Width)
    {
        for (int j = 0; j < Mask_Width; j++)
        {
            if (N_start_point + j >= 0 && N_start_point + j < Width)
                Pvalue += N[N_start_point + j] * M[j];
        }
        P[i] = Pvalue;
    }
}

int main()
{
    int width, mask_width, i;
    float *N, *M, *P;
    float *d_N, *d_M, *d_P;

    printf("Enter width of input array: ");
    scanf("%d", &width);

    N = (float *)malloc(width * sizeof(float));
    P = (float *)malloc(width * sizeof(float));

    printf("Enter %d elements of input array:\n", width);
    for (i = 0; i < width; i++)
        scanf("%f", &N[i]);

    printf("Enter mask width (odd number): ");
    scanf("%d", &mask_width);

    M = (float *)malloc(mask_width * sizeof(float));

    printf("Enter %d elements of mask array:\n", mask_width);
    for (i = 0; i < mask_width; i++)
        scanf("%f", &M[i]);

    cudaMalloc((void **)&d_N, width * sizeof(float));
    cudaMalloc((void **)&d_M, mask_width * sizeof(float));
    cudaMalloc((void **)&d_P, width * sizeof(float));

    cudaMemcpy(d_N, N, width * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, M, mask_width * sizeof(float), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (width + threads - 1) / threads;

    convolution_1D_basic_kernel<<<blocks, threads>>>(d_N, d_M, d_P, mask_width, width);

    cudaMemcpy(P, d_P, width * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Resultant array P:\n");
    for (i = 0; i < width; i++)
        printf("%.2f ", P[i]);
    printf("\n");

    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);

    free(N);
    free(M);
    free(P);

    return 0;
}
