#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H

#include "vector.h"

typedef struct collision_box
{
    Vector min, max;
    char *tag;
    int solid, width, height;
} CollisionBox;

int collided(CollisionBox a, CollisionBox b);

#endif // !COLLISIONBOX_H