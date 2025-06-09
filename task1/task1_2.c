#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    // Проверка наличия аргумента командной строки
    if (argc != 2) {
        printf("Usage: %s <size>\n", argv[0]);
        return 1;
    }

    // Чтение размера массива из аргумента командной строки
    int size = atoi(argv[1]);

    // Выделение памяти под массив
    int *array = malloc(size * sizeof(int));
    if (array == NULL) {
        printf("Failed to allocate memory for the array.\n");
        return 1;
    }

    // Инициализация генератора случайных чисел
    srand(time(NULL));
    // Заполнение массива случайными числами
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }

    // Замер времени начала вычислений
    clock_t start = clock();
    long long sum = 0;
    // Вычисление суммы элементов массива
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    // Замер времени окончания вычислений
    clock_t end = clock();

    // Вывод результатов
    printf("Sequential sum: %lld\n", sum);
    printf("Time: %.2f ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);

    // Освобождение выделенной памяти
    free(array);
    return 0;
}
