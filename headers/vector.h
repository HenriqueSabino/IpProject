#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector
{
    float x;
    float y;
} Vector;

Vector create_vector(float x, float y);
Vector sum(Vector a, Vector b);
Vector diff(Vector a, Vector b);
Vector mult(Vector a, float x);
Vector normalized(Vector a);
void setMag(Vector *a, float x);
float getMag(Vector a);
float dot(Vector a, Vector b);
float dist(Vector a, Vector b);

#endif // !VECTOR_H