#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H

#include "vector.h"

typedef struct collision_box
{
    Vector min, max, offset;
    char tag[50];
    int solid, width, height, enabled;
} CollisionBox;

int collided(CollisionBox a, CollisionBox b);

#endif // !COLLISIONBOX_H