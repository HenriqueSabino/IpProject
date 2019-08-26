#include "../headers/rigidbody.h"
#include "../headers/constants.h"

void update(RigidBody *rb)
{
    rb->acceleration.y = rb->gravity_scale * GRAVITY;
    rb->velocity.x += rb->acceleration.x;
    rb->velocity.y += rb->acceleration.y;
    rb->pos.x += rb->velocity.x;
    rb->pos.y += rb->velocity.y;
}

void update_all(RigidBody rbs[], int amount)
{
    for (int i = 0; i < amount; i++)
    {
        update(&rbs[i]);
    }
}

void update_limit_pos(RigidBody *rb, Vector min, Vector max)
{
    update(rb);
    if (rb->pos.x <= min.x)
    {
        rb->pos.x = min.x;
        rb->velocity.x = 0;
    }
    else if (rb->pos.x >= max.x)
    {
        rb->pos.x = max.x;
        rb->velocity.x = 0;
    }
    if (rb->pos.y <= min.y)
    {
        rb->pos.y = min.y;
        rb->velocity.y = 0;
    }
    else if (rb->pos.y >= max.y)
    {
        rb->pos.y = max.y;
        rb->velocity.y = 0;
    }
}