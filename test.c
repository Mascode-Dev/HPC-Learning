#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    printf("Je suis le processus %d\n", world_rank);

    MPI_Finalize();  // ← Add this line

    return 0;
}
