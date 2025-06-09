#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int SIZE;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Обработка аргумента командной строки
    if (argc < 2) {
        if (rank == 0)
            fprintf(stderr, "Usage: %s <array_size>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    SIZE = atoi(argv[1]);
    if (SIZE % size != 0) {
        if (rank == 0)
"array_ops_parallel.c" 83L, 2812B
