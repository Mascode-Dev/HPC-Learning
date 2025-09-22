#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//Somme de chaque elements d'un tableau 1D, parallelized with OPENMP

// Crée et initialise un tableau de taille N avec des 1.0
double* tableau_init(int N) {
    double* a = (double*)malloc(N * sizeof(double));
    if (a == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }

    for (int i = 0; i < N; i++) {
        a[i] = 1.0;
    }
    return a;
}

double** matrix_init(int N){
    double** a = (double**)malloc(N * sizeof(double*));
    if (a == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }

    for (int i = 0; i < N; i++) {
        a[i] = (double*)malloc(N * sizeof(double));
        if (a[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            // Libérer la mémoire déjà allouée avant de retourner
            for (int j = 0; j < i; j++) {
                free(a[j]);
            }
            free(a);
            return NULL;
        }
        for (int j = 0; j < N; j++) {
            a[i][j] = 1.0;
        }
    }
    return a;
}

// Somme parallèle d'un tableau
double parallel_sum(double* a, int N) {
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += a[i];
    }

    printf("Sum: %f\n", sum);
    return sum;
}

double parallel_matrix_sum(double** a, int N) {
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += a[i][j];
        }
    }

    printf("Matrix Sum: %f\n", sum);
    return sum;
}

int main() {
    int N = 10;

    // Initialisation du tableau
    double* a = tableau_init(N);
    if (a == NULL) return 1; // stop si allocation échoue
    parallel_sum(a, N);
    free(a); // Libération mémoire

    // Calcul de la somme
    double** b = matrix_init(N);
    if (a == NULL) return 1; // stop si allocation échoue
    parallel_matrix_sum(b, N);

    for (int i = 0; i < N; i++) {
        free(b[i]);
    }
    free(b); // Libération mémoire
    
    return 0;
}