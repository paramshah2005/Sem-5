#include <stdio.h>
#include <omp.h>

int main()
{
    int a[5][5];

    #pragma omp parallel
    {
    	int j;
        #pragma omp for private(j)
        for(int i = 0; i < 5; i++){
        	int tid = omp_get_thread_num();
            for(j = 0; j < 5; j++){
                a[i][j] = i * 5 + j + 1;
            }
            printf("Row %d initialized by Thread %d\n", i, tid);
        }
    }
    printf("\nMatrix:\n");
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            printf("%3d ", a[i][j]);
		}
        printf("\n");
    }
    return 0;
}
