#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//Somme de chaque elements de deux tableaux 1D, parallelized with OPENMP

int main() {
    int N = 1000000;
    int *tab1 = (int*)malloc(N * sizeof(int));
    int *tab2 = (int*)malloc(N * sizeof(int));
    int *tab3 = (int*)malloc(N * sizeof(int));
    int i;
    double start, end;

    for (i = 0; i < N; i++) {
        tab1[i] = i;
        tab2[i] = i;
    }

    //start = omp_get_wtime();
    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        tab3[i] = tab1[i] + tab2[i];
    }
    //end = omp_get_wtime();

    free(tab1);
    free(tab2);
    free(tab3);
    return 0;
}