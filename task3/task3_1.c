#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

int main() {
    double *a = malloc(SIZE * sizeof(double));
    double *b = malloc(SIZE * sizeof(double));
    double *res_add = malloc(SIZE * sizeof(double));
    double *res_sub = malloc(SIZE * sizeof(double));
    double *res_mul = malloc(SIZE * sizeof(double));
    double *res_div = malloc(SIZE * sizeof(double));

    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        a[i] = rand() % 100 + 1;
        b[i] = rand() % 100 + 1;
    }

    clock_t start = clock();

    for (int i = 0; i < SIZE; i++) {
        res_add[i] = a[i] + b[i];
        res_sub[i] = a[i] - b[i];
        res_mul[i] = a[i] * b[i];
        res_div[i] = a[i] / b[i];
    }

    clock_t end = clock();
    printf("Serial time: %.4f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(a); free(b); free(res_add); free(res_sub); free(res_mul); free(res_div);
    return 0;
}