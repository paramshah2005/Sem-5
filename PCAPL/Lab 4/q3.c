#include <mpi.h>
#include <stdio.h>

int factorial(int a){
	int f = 1;
	for(int i=1;i<=a;i++){
		f*=i;
	}
	return f;
}


int fibonacci(int n)
{
    int a=0, b=1, c;
    for(int i=0;i<n;i++){
    	c = a+b;
    	a=b;
    	b=c;
    }
    return a;
}

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if(rank%2==0){
    	printf("Process %d Factorial = %d\n",rank,factorial(rank));
    }    
    else{
    	printf("Process %d Fibonacci = %d\n",rank,fibonacci(rank));
    }
    MPI_Finalize();
    return 0;
}
