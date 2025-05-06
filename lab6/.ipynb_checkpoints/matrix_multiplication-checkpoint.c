#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_blas.h>

void generate_random_matrix(double *matrix, int n) {
    for (int i = 0; i < n * n; i++) {
        matrix[i] = (double)rand() / RAND_MAX;
    }
}

void naive_multiplication(double *A, double *B, double *C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i * n + j] = 0.0;
            for (int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

void better_multiplication(double *A, double *B, double *C, int n) {
    for (int i = 0; i < n * n; i++) {
        C[i] = 0.0;
    }
    
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

void blas_multiplication(double *A, double *B, double *C, int n) {
    gsl_matrix_view A_view = gsl_matrix_view_array(A, n, n);
    gsl_matrix_view B_view = gsl_matrix_view_array(B, n, n);
    gsl_matrix_view C_view = gsl_matrix_view_array(C, n, n);
    
    // C = alpha*A*B + beta*C, gdzie alpha=1.0, beta=0.0
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &A_view.matrix, &B_view.matrix, 0.0, &C_view.matrix);
}

double measure_time(void (*func)(double*, double*, double*, int), double *A, double *B, double *C, int n) {
    clock_t start, end;
    start = clock();
    func(A, B, C, n);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));
    
    int sizes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    printf("Rozmiar,Naiwna,Ulepszona,BLAS\n");
    
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        
        double *A = (double*)malloc(n * n * sizeof(double));
        double *B = (double*)malloc(n * n * sizeof(double));
        double *C = (double*)malloc(n * n * sizeof(double));
        
        generate_random_matrix(A, n);
        generate_random_matrix(B, n);
        
        //Pomiary
        double time_naive = measure_time(naive_multiplication, A, B, C, n);
        
        double time_better = measure_time(better_multiplication, A, B, C, n);
        
        double time_blas = measure_time(blas_multiplication, A, B, C, n);
        
        printf("%d,%f,%f,%f\n", n, time_naive, time_better, time_blas);
        
        // Zwolnienie pamięci
        free(A);
        free(B);
        free(C);
    }
    
    return 0;
}