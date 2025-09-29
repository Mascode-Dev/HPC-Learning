#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, nb_procs, value, sum, i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_procs);

    if(rank==0)
        value = 0;
    else
        value = rank;

    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank==0)
        printf("Sum of ranks: %d\n", sum);
    
    MPI_Finalize();
    return 0;
}