// Лабораторная работа 7.Вариант 16.
#include <stdio.h>
#include <math.h>
int main() {
    enum printed_publication{Boock, magazine, newspaper};
    enum printed_publication c = newspaper;
    printf("%d \n", c);
    struct Circle{
        float x, y;
    };
    struct Circle circle;
    circle.x = -1.0;
    circle.y = 2.0;
    float radius = 4.0;
    float lenght = 2.0 * M_PI * radius;
    printf("%.4f \n", lenght);

    // Пункт 3

    typedef union {
        struct {
            int NumLock: 1;
            int CapsLock : 1;
            int ScrollLock : 1;
        }; int value;
    } structura;
    int k;
    scanf("%x",&k);
    structura main;
    main.value = k;
    printf("NumLock: %s \n", main.NumLock ? "ON" : "OFF");
    printf("CapsLock: %s \n", main.CapsLock ? "ON" : "OFF");
    printf("ScrollLock: %s \n", main.ScrollLock ? "ON" : "OFF");
}
