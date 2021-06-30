#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int rank, numranks;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numranks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int N;          // size of our vectors
    if(rank==0) {
        N=1000;     // Only Rank 0 knows the size of the vectors
    }

    /*
     * Tell everyone how large the vectors are.
     * 1st. Since N is an int, we need to send  &N (this is our data)
     * 2nd. The data contains one single item (1)
     * 3rd. The single item is of type int (MPI_INT)
     * 4th. Rank 0 performs the Broadcasting, everyone else receives.
     *      No if statements! Everyone must call this Bcast.
     *      Rank 0 SENDs the data and everyone else RECEIVEs the data
     *      and places the data in the variable N.
     * 5th. Our communicator.
     */
    MPI_Bcast( &N, 1, MPI_INT, 0, MPI_COMM_WORLD); 

    int *a;           // Our first Vector
    int *b;           // Our second Vector
    /*
     * Everyone knows about the variables a and b (declared above)
     * but only Rank 0 allocates space for them, and then
     * initializes them in the "for" loop.
     */
    if( rank == 0 ){
        a = (int *) malloc( N*sizeof(int) );
        b = (int *) malloc( N*sizeof(int) );
        for(int i=0; i<N; i++){
            a[i] = b[i] = 2;
        }
    }

    //N for each rank
    /*
     * How large each chunk will be?
     */
    int myN=  TODO_1              


    /*
     * Allocates counts and displacements for all ranks
     */
    int *sendcounts=  TODO_2
    int *disp=        TODO_3

    /*
     * Compute Counts
     */
    for(int i=0; i<numranks; i++){
        sendcounts[i]=myN;
    }
    //last rank gets all the leftover
    sendcounts[numranks-1]+=N-myN*numranks;

    /*
     * Every Rank will run this. 
     * Print number of elements that each rank gets
     */
    printf("Rank %d: Number of Elements: %d\n",rank,sendcounts[rank]);

    /*
     * Compute displacements
     */
    disp[0]=   TODO_4



    /*
     * All nodes will receive a partial vector data to perform 
     * the dot product.  We need to allocate this space for every node/Rank
     * We need to do this for vector 'a' and vector 'b'.
     */
    int *mya = (int*) malloc(sendcounts[rank]*sizeof(int));
    int *myb = (int*) malloc(sendcounts[rank]*sizeof(int));

    /*
     * Scatterv both vectors
     * Everyone runs these two Scatterv()
     * Rank 0 performs the Scattering of the data (gets vectors 'a' and 'b'
     *        splits them up based on the sendcounts and send the chunks to
     *        everyother rank.  Everyother rank will receive the scattered data
     *        into the mya and myb buffers.
     *
     */
    MPI_Scatterv(a,_,_,_,_,_,_,0,MPI_COMM_WORLD);      TODO_5    (fill in the blanks)
    MPI_Scatterv(b,_,_,_,_,_,_,0,MPI_COMM_WORLD);      TODO_6    (fill in the blanks)

    /*
     * Do dot product
     * PLEASE NOTE HERE.  The computation of this partial dot product is the same.
     * However, each rank is now working on smaller vectors, 
     * not (a dot b)  but rather (mya dot myb)
     * THIS IS WHERE PARALLELISM IMPROVES PERFORMANCE (same problem but smaller dataset)
     */
    int result=0;
    for(int i=0;i<sendcounts[rank];i++){
        result+=mya[i]*myb[i];
    }



    /*
     * Now that every node computed a partial dot product, and this partial dot product
     * is stored in the variable 'result' we need to send all these partial results
     * to rank 0 who can collect them all and compute the final result by summ them up.
     * We can use MPI_Reduce or MPI_Allreduce to send the final result to everyone.
     */

    TODO_7   use MPI_Reduce or MPI_Allreduce, lets use MPI_Allreduce so that the 
             next printf statement will work for every rank.



    printf("Rank: %d, Result: %d\n",rank,result);

    MPI_Finalize();
}