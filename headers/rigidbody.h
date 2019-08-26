#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "vector.h"

typedef struct rigidbody
{
    Vector pos, velocity, acceleration;
    float gravity_scale;
} RigidBody;

void update(RigidBody *rb);
void update_all(RigidBody rbs[], int amount);
void update_limit_pos(RigidBody *rb, Vector min, Vector max);

#endif // !RIGIDBODY_H