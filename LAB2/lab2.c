#include <stdio.h>
#include <math.h>

int main() {
    float a;
    scanf("%f", &a);
    float z1 = sinf((M_PI / 2) + 3 * a) / (1 - sinf(3 * a - M_PI));
    float z2 = 1 / tanf(5 / 4 * M_PI + 3 / 2 * a);
    printf("%f %f", z1, z2);
    return 0;
}
