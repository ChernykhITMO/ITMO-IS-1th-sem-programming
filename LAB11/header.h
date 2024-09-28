#ifndef GEOMETRY_H
#define GEOMETRY_H
struct Parallelogram{
    double x1, y1;
    double x2, y2;
    double x3, y3;
};

double area(struct Parallelogram parallelogram);
double length(struct Parallelogram parallelogram);
struct Parallelogram create();
#endif