#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int vector[4] = {10, 20, 30, 40};  // défini seulement sur le processus 0
    int value;  // chaque processus va recevoir un seul élément
    int gathered[4];  // buffer pour rassembler les valeurs sur le process 0

    if (size != 4) {
        if (rank == 0) {
            printf("⚠️ Ce programme doit être lancé avec exactement 4 processus !\n");
        }
        MPI_Finalize();
        return 0;
    }

    // 1️⃣ Distribution du vecteur : chaque processus reçoit un élément
    MPI_Scatter(vector, 1, MPI_INT, &value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Processus %d a reçu la valeur %d\n", rank, value);

    // (Chaque processus pourrait modifier sa valeur ici si on voulait)

    // 2️⃣ Rassemblement : tous les processus envoient leur valeur au processus 0
    MPI_Gather(&value, 1, MPI_INT, gathered, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Processus 0 a rassemblé les valeurs : ");
        for (int i = 0; i < 4; i++) {
            printf("%d ", gathered[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
