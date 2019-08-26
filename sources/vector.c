#include "../headers/vector.h"

Vector create_vector(float x, float y)
{
    Vector temp = {.x = x, .y = y};
    return temp;
}