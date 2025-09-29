#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int recv_val; // valeur reçue
    int send_val = 1000 + rank; // valeur à envoyer au prochain processus

    int prev = (rank - 1 + size) % size; // rang du processus précédent
    int next = (rank + 1) % size;        // rang du processus suivant

    // Envoyer et recevoir dans l'anneau
    MPI_Sendrecv(
        &send_val, 1, MPI_INT, next, 0,
        &recv_val, 1, MPI_INT, prev, 0,
        MPI_COMM_WORLD, MPI_STATUS_IGNORE
    );

    printf("Process %d received %d from process %d\n", rank, recv_val, prev);

    MPI_Finalize();
    return 0;
}