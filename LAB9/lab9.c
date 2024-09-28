// Лабораторная работа 9.Вариант 13.
#include <stdio.h>
int main() {
    char *num[] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    int tmp;
    scanf("%d", &tmp);
    printf("%s", num[tmp]);
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        int prime = 0;
        for (int j = 2; j * j <= i; ++j) {
            if (i % j == 0) {
                prime = 1;
                break;
            }
        }
        if (prime == 0) {
            printf("%d ", i);
        }
    }
    return 0;

}

