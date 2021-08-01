#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

extern void matToImage(char *filename, int *mat, int *dims);

int main(int argc, char **argv)
{
    const int MAX_ITERATOR = 510;
    int *mat;
    int cols = 18000;
    int rows = 12000;
    int rank, numranks;
    int numoutside = 0;
    int iter;

    double area, i_c, r_c, i_z, r_z;
    double r_start, r_end, i_start, i_end;

    //vars for window size 3:2 ratio
    r_start = -2;
    r_end = 1;
    i_start = -1;
    i_end = 1;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numranks);

    if (rows % numranks != 0) {
        if (rank == 0){printf("Number of ranks must evenly divide number of rows\n");}

        MPI_Finalize();

        return 1;
    }

    mat = (int *)malloc(cols * rows * sizeof(int));
    int numrows = rows / numranks;
    int mystart = rank * numrows;
    int myend = mystart + numrows - 1;

    printf("RANK: %d, mystart: %d, myend: %d\n", rank, mystart, myend);

    double starttime = MPI_Wtime();
    #pragma omp parallel private(r_c,i_c,i_z,r_z,iter)
    {
        int tid=omp_get_thread_num();
        double starttime=omp_get_wtime();

        #pragma omp for reduction(+:numoutside) nowait
        for (int i = mystart; i <= myend; i++) {
            for (int j = 0; j < cols; j++) {
                i_c = i_start + i / (rows * 1.0) * (i_end - i_start);
                r_c = r_start + j / (cols * 1.0) * (r_end - r_start);
                i_z = i_c;
                r_z = r_c;
                iter = 0;

                while (iter < MAX_ITERATOR) {
                    iter = iter + 1;
                    double r_t = r_z * r_z - i_z * i_z;
                    double i_t = 2.0 * r_z * i_z;
                    i_z = i_t + i_c;
                    r_z = r_t + r_c;

                    if (r_z * r_z + i_z * i_z > 4){
                        numoutside = numoutside + 1;
                        break;
                    }
                }
                mat[i * cols + j] = iter;
            }
        }

        double endtime=omp_get_wtime();

        printf("Thread: %d Time: %f\n",tid,endtime-starttime);
    }

    double endtime = MPI_Wtime();

    MPI_Allreduce(MPI_IN_PLACE, &numoutside, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    area = (r_end - r_start) * (i_end - i_start) * (1.0 * cols * rows - numoutside) / (1.0 * cols * rows);

    MPI_Gather(&mat[mystart * cols], numrows * cols, MPI_INT, mat, numrows * cols, MPI_INT, 0, MPI_COMM_WORLD);
    double finaltime = MPI_Wtime();

    printf("Rank %d, Time: %.5f\n", rank, endtime - starttime);
    
    if (rank == 0) {
        printf("Final Time: %.5f\n", finaltime - starttime);
        printf("Area of Mandelbrot set = %f\n", area);

        int dims[2] = {rows, cols};
        matToImage("Mandelbrot.jpg", mat, dims);
    }

    free(mat);

    MPI_Finalize();
}