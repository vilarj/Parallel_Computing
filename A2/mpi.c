#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    int rank,numranks;
    MPI_Comm_size(MPI_COMM_WORLD,&numranks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Status stat;
    int tag=0;
    
    int number=5; // number = 0
    if (rank == 0) {
       MPI_Send(&number, 1, MPI_INT, 1, tag, MPI_COMM_WORLD); // MPI_Send(&number, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
       MPI_Recv(&number, 1, MPI_INT, 1, tag, MPI_COMM_WORLD,&stat); // MPI_Recv(&number, 1, MPI_INT, n-1, tag, MPI_COMM_WORLD,&stat)
       printf("Rank 0 received number %d from rank 1\n", number); // printf("number is : %d\n, number);
    } else if (rank == 1) {
       MPI_Recv(&number, 1, MPI_INT, 0, tag, MPI_COMM_WORLD,&stat); // MPI_Recv(&number, 1, MPI_INT, 0, tag, MPI_COMM_WORLD,&stat);
       number +=1;
       MPI_Send(&number, 1, MPI_INT, 0, tag, MPI_COMM_WORLD); // MPI_Send(&number, 1, MPI_INT, n+1 (2 in this case), tag, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    /**
     * ======================= PART a =============================
     * int next = (rank + 1) % numranks;
     * int prev = rank - 1;
     * 
     * if (rank == 0) {
     * prev = numranks - 1;
     * 
     * MPI_Send(&number, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
     * MPI_Recv(&number, 1, MPI_INT, prev, tag, MPI_COMM_WORLD);
     * }
     * 
     * else {
     * MPI_Recv(&number, 1, MPI_INT, prev, tag, MPI_COMM_WORLD);
     * MPI_Send(&number, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
     * }
     * 
     * 
     * ======================= PART b =============================
     * double begining = MPI_Wtime();
     * double end = MPI_Wtime();
     * double runtime = begining - end;
     * 
     * printf("number is: %d", runtime);
     * 
     * ======================= PART c =============================
     * int elements = ( (1024*1024*1024) / sizeof(int) ); // 1Gb of data
     * int * data = (int*) malloc(elements * sizeof(int));
     * 
     * if (rank == 0) {
     *   double beggining = MPI_Wtime();
     * 
     *   for (int i = 1; i < numranks; i++) {
     *      MPI_Send(data, elements, MPI_INT, i, tag, MPI_COMM_WORLD);
     *      MPI_Recv(data, elements, MPI_INT, i, tag, MPI_COMM_WORLD);
     *   }
     *   double end = MPI_Wtime();
     *   double avr = (begging + end) / numranks;
     * }
     * 
     * else {
     *   MPI_Recv(data, elements, MPI_INT, 0, tag, MPI_COMM_WORLD);
     *   MPI_Send(data, elements, MPI_INT, 0, tag, MPI_COMM_WORLD);
     * }
     * 
     **/
}