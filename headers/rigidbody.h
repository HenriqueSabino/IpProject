#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "vector.h"
#include "collisionbox.h"
#include "list.h"

typedef struct rigidbody
{
    Vector pos, velocity, acceleration;
    float gravity_scale;
    CollisionBox cb;
    List *collidingWith;
    void (*onCollisionEnter)(struct rigidbody *self, struct rigidbody *other);
    void (*onCollisionStay)(struct rigidbody *self, struct rigidbody *other);
    void (*onCollisionExit)(struct rigidbody *self, struct rigidbody *other);
} RigidBody;

void update(RigidBody *rb);
void update_all(RigidBody *rbs[], int amount);
void update_limit_pos(RigidBody *rb, Vector min, Vector max);
void apply_force(RigidBody *rb, float x, float y);

#endif // !RIGIDBODY_H