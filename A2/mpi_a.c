#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    int rank, numranks, next, prev, tag=0, number = 0;
    MPI_Comm_size(MPI_COMM_WORLD,&numranks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Status stat;

    next = rank++ % numranks;
    prev = rank--;

    if (rank == 0) {
       prev = numranks--;

       MPI_Send(&number, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
       MPI_Recv(&number, 1, MPI_INT, prev, tag, MPI_COMM_WORLD,&stat);

       printf("number is: %d", number);
    } 
    else if (rank == 1) {
       MPI_Recv(&number, 1, MPI_INT, prev, tag, MPI_COMM_WORLD,&stat);
       MPI_Send(&number, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}