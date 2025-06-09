
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int* array, int size) {
    for (int i = 0; i < size - 1; i++) {
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
    FILE* file;
    errno_t err = fopen_s(&file, "C:\\Users\\MyComp\\Desktop\\TextFile1.txt", "r");
    if (err != 0) {
        printf("Failed to open file\n");
        return 1;
    }

    int size;
    if (fscanf_s(file, "%d", &size) != 1) {
        printf("Failed to read from file\n");
        fclose(file);
        return 1;
    }
    fclose(file);

    int* array = (int*)malloc(size * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }

    clock_t start = clock();
    bubbleSort(array, size);
    clock_t end = clock();

    printf("Sequential bubble sort completed.\n");
    printf("Time: %.2f ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);

    free(array);
    return 0;
}
