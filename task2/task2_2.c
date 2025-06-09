#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int* arr, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 100000;
    int* global_data = NULL;
    int* local_data = NULL;
    int local_size;

    double start_time, end_time;

    // Процесс 0 генерирует данные
    if (rank == 0) {
        global_data = (int*)malloc(N * sizeof(int));
        srand(time(NULL));
        for (int i = 0; i < N; i++) {
            global_data[i] = rand() % 100000;
        }
        start_time = MPI_Wtime();
    }

    // Распределяем данные между процессами
    local_size = N / size;
    local_data = (int*)malloc(local_size * sizeof(int));

    MPI_Scatter(global_data, local_size, MPI_INT,
               local_data, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Каждый процесс сортирует свою часть
    bubble_sort(local_data, local_size);

    // Собираем отсортированные части
    MPI_Gather(local_data, local_size, MPI_INT,
              global_data, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Процесс 0 выполняет финальную сортировку
    if (rank == 0) {
        bubble_sort(global_data, N);
        end_time = MPI_Wtime();

        printf("Sorted array (first 10 elements): ");
        for (int i = 0; i < 10; i++) {
            printf("%d ", global_data[i]);
        }
        printf("\nTotal time: %.4f seconds\n", end_time - start_time);

        free(global_data);
    }

    free(local_data);
    MPI_Finalize();
    return 0;
}