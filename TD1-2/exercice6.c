#include <stdio.h>
#include <mpi.h>

double f(double x) {
    return 4 / (1 + x*x); // f(x) = 4 / (1 + x^2)
}

int main() {
    int N = 10000;
    double a = 0.0, b = 1.0;

    double integral = 0.0;
    double h = (b - a) / N; // largeur des sous-intervalles

    #pragma omp parallel for reduction(+:integral)
    for (int i = 0; i < N; i++) {
        double x_mid = a + i*h + h/2; // point milieu
        integral += f(x_mid);
    }
    
    integral *= h;

    printf("Integral: %f\n", integral);
    return 0;
}
