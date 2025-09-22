#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000

int main() {
    double *a = (double*)malloc(N * sizeof(double));
    double *b = (double*)malloc(N * sizeof(double));
    double dot = 0.0;
    int i;
    double start, end;

    for (i = 0; i < N; i++) {
        a[i] = 1.0;
        b[i] = 2.0;
    }

    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:dot)
    for (i = 0; i < N; i++) {
        dot += a[i] * b[i];
    }
    end = omp_get_wtime();

    printf("Dot product = %f\n", dot);
    printf("Time with %d threads: %f seconds\n", omp_get_max_threads(), end - start);

    free(a);
    free(b);
    return 0;
}
