#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    int rank, numranks, tag = 0, elements = ( (1024*1024*1024) / sizeof(int) );
    int* data = (int*) malloc(elements * sizeof(int));
    MPI_Comm_size(MPI_COMM_WORLD,&numranks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Status stat;
    
    if (rank == 0) {
        double beggining = MPI_Wtime();

        for (int i = 1; i < numranks; i++) {
            MPI_Send(data, elements, MPI_INT, i, tag, MPI_COMM_WORLD);
            MPI_Recv(data, elements, MPI_INT, i, tag, MPI_COMM_WORLD);
        }
      
      double end = MPI_Wtime();
      double avr = (begging + end) / numranks;

      printf("Average time is: %f\n", avr);
    } 
    else {
       MPI_Recv(&number, 1, MPI_INT, 0, tag, MPI_COMM_WORLD,&stat);
       MPI_Send(&number, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}