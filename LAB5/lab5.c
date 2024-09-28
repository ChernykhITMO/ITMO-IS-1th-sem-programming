// Лабораторная работа 5. Массивы. Вариант 7.
#include <stdio.h>
int main() {
    int arr[7] = {90, 76, 54, 23, 56, 12, 48};
    for (int i = 0; i < 7; i++)
        printf("%d ", arr[i]);
    printf("\n");

    int arr1[2][2] = {{2, 5},
                      {2, 2}};
    int arr2[2][2] = {{1, 2},
                      {0, 1}};
    int mas[2][2];

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            mas[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                mas[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", mas[i][j]);
        }
    }
}