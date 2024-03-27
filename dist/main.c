#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main() {
    int array[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);

    int* result;
    int resultSize;

    // Визначаємо кількість повторюваних елементів та створюємо результуючий масив
    result = findDuplicates(array, size, &resultSize);

    printf("Результуючий масив:\n");
    for (int i = 0; i < resultSize; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Звільнимо пам'ять, яку виділили для результату
    free(result);

    return 0;
}
