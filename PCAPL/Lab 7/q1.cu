#include <stdio.h>
#include <cuda.h>

int main()
{
    int count, i;
    cudaDeviceProp prop;

    cudaGetDeviceCount(&count);

    printf("Number of CUDA devices: %d\n", count);

    for (i = 0; i < count; i++)
    {
        cudaGetDeviceProperties(&prop, i);

        printf("Device %d\n", i);
        printf("Device Name: %s\n", prop.name);
        printf("Number of SMs: %d\n", prop.multiProcessorCount);
        printf("Maximum threads per block: %d\n", prop.maxThreadsPerBlock);

        printf("Maximum thread dimensions: %d x %d x %d\n",
               prop.maxThreadsDim[0],
               prop.maxThreadsDim[1],
               prop.maxThreadsDim[2]);

        printf("Maximum grid dimensions: %d x %d x %d\n",
               prop.maxGridSize[0],
               prop.maxGridSize[1],
               prop.maxGridSize[2]);

        printf("Clock frequency: %.2f GHz\n",
               prop.clockRate / 1000000.0);
    }

    return 0;
}
