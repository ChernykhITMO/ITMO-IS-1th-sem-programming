#include <stdio.h>
int main() {
    int a;
    int b;
    scanf("%o", &a);
    printf("%d\n", a);
    printf("%o %o\n",a, a >> 3);
    printf("%o %o\n", a, ~a);
    scanf("%o", &b);
    printf("%o\n", b | a);
    return 0;
}