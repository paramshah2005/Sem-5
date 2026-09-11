#include <stdio.h>
#include <string.h>
#include <cuda.h>

__device__ int isVowel(char c)
{
    c = (c >= 'A' && c <= 'Z') ? c + 32 : c;
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

__global__ void replaceVowels(int *s, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
    {
        if (isVowel((char)s[i]))
            atomicExch(&s[i], (int)'*');
    }
}

int main()
{
    char str[1000];
    int n, i;
    int *s, *d_s;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    n = strlen(str);

    s = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        s[i] = (int)str[i];

    cudaMalloc((void **)&d_s, n * sizeof(int));
    cudaMemcpy(d_s, s, n * sizeof(int), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n + threads - 1) / threads;

    replaceVowels<<<blocks, threads>>>(d_s, n);

    cudaMemcpy(s, d_s, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Output String RS: ");
    for (i = 0; i < n; i++)
        printf("%c", (char)s[i]);
    printf("\n");

    cudaFree(d_s);
    free(s);

    return 0;
}
