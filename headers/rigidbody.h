#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "vector.h"
#include "collisionbox.h"

typedef struct rigidbody
{
    Vector pos, velocity, acceleration;
    float gravity_scale;
    CollisionBox cb;
} RigidBody;

void update(RigidBody *rb);
void update_all(RigidBody *rbs[], int amount);
void update_limit_pos(RigidBody *rb, Vector min, Vector max);
void apply_force(RigidBody *rb, float x, float y);

#endif // !RIGIDBODY_H