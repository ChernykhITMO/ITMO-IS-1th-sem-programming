// Лабораторная работа 6.Вариант 2.
#include <stdio.h>
#include <stdlib.h>
int main(){
    float arr[4];
    float *pointer1 = arr;

    for(int i = 0; i < 4; i++){
        scanf("%f", &arr[i]);
    }

    for(int i = 0; i < 4; i++){
        printf("%.1f ", *(pointer1+i));
    }
    printf("\n");

    float * pointer2 = NULL;

    pointer2 = (float *)malloc(4 * sizeof(float));

    for(int i = 0; i < 4; i++){
        scanf("%f", &pointer2[i]);
    }

    for(int i = 0; i < 4; i++)
        printf("%.1f ", pointer2[i]);

    free(pointer2);

    return 0;
}

