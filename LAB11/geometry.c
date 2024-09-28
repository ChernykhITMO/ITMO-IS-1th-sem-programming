#include <stdio.h>
#include <math.h>
#include "header.h"

double area(struct Parallelogram parallelogram) {
    double vector1X = parallelogram.x2 - parallelogram.x1;
    double vector1Y = parallelogram.y2 - parallelogram.y1;
    double vector2X = parallelogram.x3 - parallelogram.x1;
    double vector2Y = parallelogram.y3 - parallelogram.y1;
    return fabs(vector1X * vector2Y - vector1Y * vector2X);
}

double length(struct Parallelogram parallelogram) {
    double side1 = sqrt(pow(parallelogram.x2 - parallelogram.x1, 2) + pow(parallelogram.y2 - parallelogram.y1, 2));
    double side2 = sqrt(pow(parallelogram.x3 - parallelogram.x2, 2) + pow(parallelogram.y3 - parallelogram.y2, 2));
    double side3 = sqrt(pow(parallelogram.x1 - parallelogram.x3, 2) + pow(parallelogram.y1 - parallelogram.y3, 2));
    return side1 + side2 + side3;
}

struct Parallelogram create() {
    struct Parallelogram parallelogram;
    scanf("%lf %lf", &parallelogram.x1, &parallelogram.y1);
    scanf("%lf %lf", &parallelogram.x2, &parallelogram.y2);
    scanf("%lf %lf", &parallelogram.x3, &parallelogram.y3);
    return parallelogram;
}
