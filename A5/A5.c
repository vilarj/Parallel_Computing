#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

// TO COMPILE:    mpicc  -o  A5  A5.c  -lm
/**
 * Tasks:
 * 1) Use TAU and Paraprof to analyze the performance in serial.
 * 2) Use MPI to parallelize the application.
 * 3) Verify that the code still produces the correct result.
 * 4) Use TAU and Paraprof to analyze the performance of your parallel version. 
 */

int is_prime(int n);

int main(int argc, char** argv){
    int rank, numranks;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numranks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int n, elements, start, end, result;
    int numprimes = 0;

    if (rank == 0) {
        n = 10000000;
    }
    
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    elements = n / numranks;
    start = rank * elements;
    end = start + (elements - 1);

    for (int i = 1; i <= n; i++) {
        if (is_prime(i) == 1) {numprimes++;}
    }

    result = 0;

    MPI_Reduce(&numprimes, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {printf("Number of Primes: %d\n", numprimes);}

    MPI_Finalize();
}

int is_prime(int n) {
    /* handle special cases */
    if (n == 0) {return 0;}
    else if (n == 1) {return 0;}
    else if (n == 2) {return 1;}

    int i;
    for(i = 2; i <= (int)(sqrt((double) n)); i++) {
        if (n % i == 0) {return 0;}
    }
    return 1;
}