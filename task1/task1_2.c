#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv); // Инициализация MPI

    int rank, comm_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);      // Получение ранга процесса
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size); // Получение количества процессов

    int global_size;
    if (rank == 0) {
        // Чтение размера массива из файла только в процессе 0
        FILE *file = fopen("input.txt", "r");
        fscanf(file, "%d", &global_size);
        fclose(file);
    }

    // Распространение размера массива всем процессам
    MPI_Bcast(&global_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_size = global_size / comm_size;  // Размер подмассива для каждого процесса
    int *local_array = malloc(local_size * sizeof(int)); // Память под локальный массив

    if (rank == 0) {
        int *global_array = malloc(global_size * sizeof(int));
        srand(time(NULL));
        for (int i = 0; i < global_size; i++) {
            global_array[i] = rand() % 100; // Инициализация глобального массива случайными числами
        }

        // Распределение частей массива между процессами
        MPI_Scatter(global_array, local_size, MPI_INT,
                    local_array, local_size, MPI_INT, 0, MPI_COMM_WORLD);
        free(global_array);
    } else {
        // Остальные процессы получают свои части
        MPI_Scatter(NULL, local_size, MPI_INT,
                    local_array, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    }

    // Измерение времени
    double start = MPI_Wtime();

    // Подсчёт локальной суммы
    long local_sum = 0;
    for (int i = 0; i < local_size; i++) {
        local_sum += local_array[i];
    }

    // Сбор всех локальных сумм в глобальную
    long global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();

    if (rank == 0) {
        // Вывод результата
        printf("Parallel sum: %ld\n", global_sum);
        printf("Time: %.2f ms\n", (end - start) * 1000);
    }

    free(local_array);
    MPI_Finalize(); // Завершение MPI
    return 0;
}
