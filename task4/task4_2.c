#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Функция сравнения для qsort
int cmpfunc(const void *a, const void *b) {
    double arg1 = *(const double*)a;
    double arg2 = *(const double*)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

int main(int argc, char** argv) {
    int rank, size;
    double *data = NULL, *local_data;
    int chunk, array_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Получаем размер массива из аргументов командной строки
    if (argc < 2) {
        if (rank == 0)
            fprintf(stderr, "Usage: %s <array_size>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    array_size = atoi(argv[1]);
    if (array_size % size != 0) {
        if (rank == 0)
            fprintf(stderr, "Array size must be divisible by number of processes.\n");
        MPI_Finalize();
        return 1;
    }

    chunk = array_size / size;
    local_data = malloc(chunk * sizeof(double));

    if (rank == 0) {
        data = malloc(array_size * sizeof(double));
        srand(42);
        for (int i = 0; i < array_size; i++) {
            data[i] = rand() % 100000;
        }
    }


    MPI_Scatter(data, chunk, MPI_DOUBLE, local_data, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double t1 = MPI_Wtime();

    // Локальная быстрая сортировка
    qsort(local_data, chunk, sizeof(double), cmpfunc);

    // Сбор отсортированных блоков обратно
    MPI_Gather(local_data, chunk, MPI_DOUBLE, data, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Финальная быстрая сортировка всего массива
        qsort(data, array_size, sizeof(double), cmpfunc);
        double t2 = MPI_Wtime();
        printf("Parallel qsort completed on %d processes.\n", size);
        printf("Time elapsed: %.4f seconds for array size %d\n", t2 - t1, array_size);
        free(data);
    }

    free(local_data);
    MPI_Finalize();
    return 0;
}