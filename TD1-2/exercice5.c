#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;

    // Initialisation de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Récupérer le rang du processus
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Récupérer le nombre total de processus

    // Vérification pair/impair
    if (rank % 2 == 0) {
        printf("Process %d is even (out of %d processes)\n", rank, size);
    } else {
        printf("Process %d is odd (out of %d processes)\n", rank, size);
    }

    MPI_Finalize();
    return 0;
}