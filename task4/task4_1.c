#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 400
#define COLS 250

int main() {
    int i, j;
    double **A, **B;
    double **add_result, **sub_result, **mul_result, **div_result;

    // Выделение памяти
    A = malloc(ROWS * sizeof(double*));
    B = malloc(ROWS * sizeof(double*));
    add_result = malloc(ROWS * sizeof(double*));
    sub_result = malloc(ROWS * sizeof(double*));
    mul_result = malloc(ROWS * sizeof(double*));
    div_result = malloc(ROWS * sizeof(double*));

    for (i = 0; i < ROWS; i++) {
        A[i] = malloc(COLS * sizeof(double));
        B[i] = malloc(COLS * sizeof(double));
        add_result[i] = malloc(COLS * sizeof(double));
        sub_result[i] = malloc(COLS * sizeof(double));
        mul_result[i] = malloc(COLS * sizeof(double));
        div_result[i] = malloc(COLS * sizeof(double));
    }

    // Инициализация случайными значениями
    srand(time(NULL));
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            A[i][j] = rand() % 100 + 1;
            B[i][j] = rand() % 100 + 1;
        }
    }

    // Засекаем время
    clock_t start = clock();

    // Арифметические операции
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            add_result[i][j] = A[i][j] + B[i][j];
            sub_result[i][j] = A[i][j] - B[i][j];
            mul_result[i][j] = A[i][j] * B[i][j];
            div_result[i][j] = A[i][j] / B[i][j];
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Serial matrix operation time: %.4f seconds\n", time_spent);

    // Освобождение памяти
    for (i = 0; i < ROWS; i++) {
        free(A[i]); free(B[i]);
        free(add_result[i]); free(sub_result[i]);
        free(mul_result[i]); free(div_result[i]);
    }
    free(A); free(B);
    free(add_result); free(sub_result);
    free(mul_result); free(div_result);

    return 0;
}