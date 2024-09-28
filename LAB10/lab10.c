#include <stdio.h>
#include <math.h>
#include <string.h>

struct coordinates {
    float x;
    float y;
};

float distance(struct coordinates point1, struct coordinates point2) {
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}


void distanceArray(struct coordinates points[], int n, float distances[][n - 1]) {
    for (int i = 0; i < n; i++){
        int len = 0;
        for (int j = 0; j < n; j++){
            if (i != j){
                distances[i][len++] = distance(points[i], points[j]);
            }
        }
    }
}

void removeSpace(char str[], int index, int count) {
    if (str[index] == '\0') {
        str[count] = '\0';
        return;
    }

    char currentChar = str[index];
    char prevChar = (index > 0) ? str[index - 1] : '\0';

    if (currentChar == ' ' && prevChar == ' ')
        removeSpace(str, index + 1, count);
    else {
        str[count] = currentChar;
        removeSpace(str, index + 1, count + 1);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    struct coordinates points[n];
    for(int i = 0; i < n; i++)
        scanf("%f %f", &points[i].x, &points[i].y);

    float distances[n][n - 1];
    distanceArray(points, n, distances);

    printf("Distances: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            printf("%.4f ", distances[i][j]);
        }
        printf("\n");
    }

    char str[100];
    fgets(str, sizeof(str), stdin);
    fgets(str, sizeof(str), stdin);
    removeSpace(str, 0, 0);

    printf("%s\n", str);

    return 0;
}
