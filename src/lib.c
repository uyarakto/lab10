#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

#define MAX_ELEMENTS 1000 // Максимальна кількість елементів у масиві

int* findDuplicates(int* array, int size, int* resultSize) {
    int* result = (int*)malloc(MAX_ELEMENTS * sizeof(int)); // Результуючий масив
    if (result == NULL) {
        *resultSize = 0;
        return NULL;
    }

    // Хеш-таблиця для відстеження кількості зустрічей кожного елемента
    int counts[MAX_ELEMENTS] = {0};

    // Обхід масиву та збільшення лічильника для кожного елемента
    for (int i = 0; i < size; ++i) {
        counts[array[i]]++;
    }

    int index = 0;
    // Створення результуючого масиву
    for (int i = 0; i < MAX_ELEMENTS; ++i) {
        if (counts[i] > 0) {
            result[index++] = i;         // Значення
            result[index++] = counts[i]; // Кількість повторень
        }
    }

    *resultSize = index; // Встановлення розміру результату

    return result;
}
