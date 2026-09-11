#include <stdio.h>
#include <string.h>
#include <cuda.h>

#define MAX_WORDS 100
#define WORD_LEN 50

__global__ void countWord(char *words, char *target, unsigned int *count,
                           int numWords, int wordLen)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < numWords)
    {
        char *word = words + i * wordLen;
        int j = 0;
        int match = 1;

        while (word[j] != '\0' || target[j] != '\0')
        {
            if (word[j] != target[j])
            {
                match = 0;
                break;
            }
            j++;
        }

        if (match)
            atomicAdd(count, 1);
    }
}

int main()
{
    char sentence[1000];
    char target[WORD_LEN];
    char words[MAX_WORDS][WORD_LEN];
    int numWords = 0;
    unsigned int count = 0;

    char *d_words, *d_target;
    unsigned int *d_count;

    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0';

    printf("Enter the word to count: ");
    scanf("%s", target);

    char *token = strtok(sentence, " ");
    while (token != NULL && numWords < MAX_WORDS)
    {
        strcpy(words[numWords], token);
        numWords++;
        token = strtok(NULL, " ");
    }

    cudaMalloc((void **)&d_words, MAX_WORDS * WORD_LEN * sizeof(char));
    cudaMalloc((void **)&d_target, WORD_LEN * sizeof(char));
    cudaMalloc((void **)&d_count, sizeof(unsigned int));

    cudaMemcpy(d_words, words, numWords * WORD_LEN * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_target, target, WORD_LEN * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &count, sizeof(unsigned int), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (numWords + threads - 1) / threads;

    countWord<<<blocks, threads>>>(d_words, d_target, d_count, numWords, WORD_LEN);

    cudaMemcpy(&count, d_count, sizeof(unsigned int), cudaMemcpyDeviceToHost);

    printf("Word \"%s\" occurs %u times\n", target, count);

    cudaFree(d_words);
    cudaFree(d_target);
    cudaFree(d_count);

    return 0;
}
