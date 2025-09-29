#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int matrix[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    int row[4];  // buffer to receive the row

    if (size < 2) {
        if (rank == 0) {
            printf("This program needs at least 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        // Send the second row (index 1) to process 1
        MPI_Send(matrix[1], 4, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent row: %d %d %d %d\n",
               matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3]);
    } else if (rank == 1) {
        // Receive the row from process 0
        MPI_Recv(row, 4, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received row: %d %d %d %d\n",
               row[0], row[1], row[2], row[3]);
    }

    MPI_Finalize();
    return 0;
}
