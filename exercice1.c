#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Print for ranks 1 < p < n-1
	if (rank > 1 && rank < size - 1) {
		printf("Process %d: %s\n", rank, (rank % 2 == 0) ? "even" : "odd");
	}

	MPI_Finalize();
	return 0;
}