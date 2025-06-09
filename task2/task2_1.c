#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция пузырьковой сортировки
void bubbleSort(int* array, int size) {
    // Проходим по всему массиву size-1 раз
    for (int i = 0; i < size - 1; i++) {
        // В каждом проходе сравниваем соседние элементы и меняем их местами, если нужно
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main() {
    // Открываем файл input.txt для чтения
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        // Если файл не открылся, выводим ошибку и завершаем программу
        perror("Failed to open input.txt");
        return 1;
    }

    int size;
    // Считываем первое число из файла — размер массива
    if (fscanf(file, "%d", &size) != 1) {
        fprintf(stderr, "Failed to read array size from input.txt\n");
        fclose(file);
        return 1;
    }
    fclose(file);

    // Выделяем память под массив целых чисел
    int* array = (int*)malloc(size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Заполняем массив случайными числами от 0 до 99
    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }

    // Замер времени начала сортировки
    clock_t start = clock();

    // Выполняем пузырьковую сортировку
    bubbleSort(array, size);

    // Замер времени окончания сортировки
    clock_t end = clock();

    // Выводим сообщение и время сортировки в миллисекундах
    printf("Sequential bubble sort completed.\n");
    printf("Time: %.2f ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);

    // Освобождаем память
    free(array);
    return 0;
}
