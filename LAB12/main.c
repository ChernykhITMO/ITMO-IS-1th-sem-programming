#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int tmp1= atoi(argv[1]);
    int tmp2 = atoi(argv[2]);
    int sum = tmp1 + tmp2;
    FILE *file = freopen("res.txt", "w", stdout);
    printf("%d", sum);
    fclose(file);
    return 0;
}
