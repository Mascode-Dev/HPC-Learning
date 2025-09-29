#include <stdio.h>
#include <mpi.h>

#define N 4

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if (rank == 0) {
            printf("⚠️ Ce programme nécessite exactement 2 processus !\n");
        }
        MPI_Finalize();
        return 0;
    }

    int matrix[N][N] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12},
        {13,14, 15, 16}
    };

    // Partie supérieure et inférieure à échanger
    int upper[6]; // pour les éléments i<j
    int lower[6]; // pour les éléments i>j

    if (rank == 0) {
        // Extraire la partie supérieure
        int k = 0;
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                upper[k++] = matrix[i][j];
            }
        }

        // Envoyer la partie supérieure à process 1
        MPI_Send(upper, 6, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // Recevoir la partie inférieure depuis process 1
        MPI_Recv(lower, 6, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Mettre à jour la matrice avec les valeurs reçues
        int k2 = 0;
        for (int i = 1; i < N; i++) {
            for (int j = 0; j < i; j++) {
                matrix[i][j] = lower[k2++];
            }
        }

        printf("Processus 0 : matrice après mise à jour (partie inférieure remplacée)\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%3d ", matrix[i][j]);
            }
            printf("\n");
        }

    } else if (rank == 1) {
        // Recevoir la partie supérieure
        MPI_Recv(upper, 6, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Processus 1 : a reçu la partie supérieure : ");
        for (int i = 0; i < 6; i++) printf("%d ", upper[i]);
        printf("\n");

        // Simuler une matrice locale et extraire la partie inférieure
        int local_matrix[N][N] = {
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9, 10, 11, 12},
            {13,14, 15, 16}
        };

        int k = 0;
        for (int i = 1; i < N; i++) {
            for (int j = 0; j < i; j++) {
                lower[k++] = local_matrix[i][j];
            }
        }

        // Envoyer la partie inférieure à process 0
        MPI_Send(lower, 6, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
