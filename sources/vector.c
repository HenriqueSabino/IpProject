#include <math.h>
#include "../headers/vector.h"

Vector create_vector(float x, float y)
{
    Vector temp = {.x = x, .y = y};
    return temp;
}

Vector sum(Vector a, Vector b)
{
    return create_vector(a.x + b.x, a.y + b.y);
}

Vector diff(Vector a, Vector b)
{
    return create_vector(a.x - b.x, a.y - b.y);
}

Vector mult(Vector a, float x)
{
    return create_vector(x * a.x, x * a.y);
}

float getMag(Vector a)
{
    return sqrtf(a.x * a.x + a.y * a.y);
}

Vector normalized(Vector a)
{
    return mult(a, 1 / getMag(a));
}

void setMag(Vector *a, float x)
{
    *a = mult(normalized(*a), x);
}

float dot(Vector a, Vector b)
{
    return a.x * b.x + a.y * b.y;
}

float dist(Vector a, Vector b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}