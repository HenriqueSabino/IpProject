#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector
{
    float x;
    float y;
} Vector;

Vector create_vector(float x, float y);

#endif // !VECTOR_H