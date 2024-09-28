// Лабораторная работа 4. Логические операции. Вариант 18
#include <stdio.h>
int main() {
    int a;
    scanf("%d", &a);
    printf("%d", (a >= - 77) && (a <= 1));
    int b;
    scanf("%o", &b);
    printf("%o", (b >> 18) % 2);
    return 0;
}
