// Лабораторная работа 11.Вариант 14. Задания Параллелограмм, 2, 3.

#include <stdio.h>
#include "header.h"

int main() {
    struct Parallelogram parallelogram = create();
    double area_result = area(parallelogram);
    double length_result = length(parallelogram);

    printf("Area: %.lf\n", area_result);
    printf("Lenght: %.4lf\n", length_result);

    return 0;
}