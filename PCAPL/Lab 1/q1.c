#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel
    {
        int total = omp_get_num_threads();
        int id = omp_get_thread_num();
        if(id==0){
        	printf("Total number of threads = %d\n", total);
        }
    }

    return 0;
}
