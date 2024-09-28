// Лабораторная работа 8.Вариант 2.
#include <stdio.h>
#include <string.h>

int main() {
    // 2
    int n;
    scanf("%d", &n);
    char str1[10];
    scanf("%s", str1);
    char str2[10];
    scanf("%s", str2);
    char result[20];
    strcpy(result, str1);
    strncat(result, str2, n);
    printf("Number 1: ");
    printf("%s \n", result);


    // 4
    int comparison = strncmp(str1, str2, n);
    printf("Number 2: ");
    if (comparison == 0) {
        printf("Strings are equal");
    } else if (comparison < 0) {
        printf("before\n");
    } else {
        printf("after\n");
    }

    // 6
    strncpy(str1, str2, n);
    printf("Number 3: ");
    printf("%s\n", str1);

    // 8
    printf("Number 4: ");
    char target;
    scanf(" %c", &target);
    char *res = strchr(str1, target);
    if (res != NULL) {
        int index = res - str1;
        printf("%d\n", index);
    } else {
        printf("No\n");
    }

    // 10


    char *result2 = strpbrk(str1, str2);
    printf("Number 5: ");

    if (result2 != NULL) {
        printf("%s", result2);
    } else {
        printf("No\n");
    }

    return 0;

}