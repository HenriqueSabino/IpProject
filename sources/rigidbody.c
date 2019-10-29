#include "../headers/rigidbody.h"
#include "../headers/constants.h"
#include <stdio.h>

void update(RigidBody *rb)
{
    rb->acceleration.y = rb->gravity_scale * GRAVITY;
    rb->velocity.x += rb->acceleration.x;
    rb->velocity.y += rb->acceleration.y;
    rb->pos.x += rb->velocity.x;
    rb->pos.y += rb->velocity.y;

    rb->cb.min.x = rb->pos.x + rb->cb.offset.x;
    rb->cb.min.y = rb->pos.y + rb->cb.offset.y;
    rb->cb.max.x = rb->cb.min.x + rb->cb.width;
    rb->cb.max.y = rb->cb.min.y + rb->cb.height;
}

void update_all(RigidBody *rbs[], int amount)
{
    CollisionBox prev_cb[amount];
    for (int i = 0; i < amount; i++)
    {
        prev_cb[i] = rbs[i]->cb;
        update(rbs[i]);
    }
    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < amount; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (collided(rbs[i]->cb, rbs[j]->cb) && rbs[i]->cb.solid)
            {
                if (prev_cb[i].min.x >= rbs[j]->cb.max.x)
                {
                    rbs[i]->pos.x = (prev_cb[i].min.x) - (prev_cb[i].min.x - rbs[j]->cb.max.x) - prev_cb[i].offset.x;

                    rbs[i]->cb.min.x = rbs[i]->pos.x + rbs[i]->cb.offset.x;
                    rbs[i]->cb.min.y = rbs[i]->pos.y + rbs[i]->cb.offset.y;
                    rbs[i]->cb.max.x = rbs[i]->cb.min.x + rbs[i]->cb.width;
                    rbs[i]->cb.max.y = rbs[i]->cb.min.y + rbs[i]->cb.height;
                }
                else if (prev_cb[i].max.x <= rbs[j]->cb.min.x)
                {

                    rbs[i]->pos.x = prev_cb[i].min.x + rbs[j]->cb.min.x - prev_cb[i].max.x - prev_cb[i].offset.x;

                    rbs[i]->cb.min.x = rbs[i]->pos.x + rbs[i]->cb.offset.x;
                    rbs[i]->cb.min.y = rbs[i]->pos.y + rbs[i]->cb.offset.y;
                    rbs[i]->cb.max.x = rbs[i]->cb.min.x + rbs[i]->cb.width;
                    rbs[i]->cb.max.y = rbs[i]->cb.min.y + rbs[i]->cb.height;
                }
                else if (prev_cb[i].min.y >= rbs[j]->cb.max.y)
                {
                    if (*rbs[i]->cb.tag == *"player" && *rbs[j]->cb.tag == *"ground")
                    {
                        rbs[i]->velocity.y = 0;
                        (rbs[i]->onCollisionEnter)(*rbs[j]);
                    }
                    else if (*rbs[i]->cb.tag == *"ground" && *rbs[j]->cb.tag == *"player")
                    {
                        rbs[j]->velocity.y = 0;
                        (rbs[j]->onCollisionEnter)(*rbs[i]);
                    }
                    rbs[i]->pos.y = prev_cb[i].min.y - (prev_cb[i].min.y - rbs[j]->cb.max.y) - prev_cb[i].offset.y;

                    rbs[i]->cb.min.x = rbs[i]->pos.x + rbs[i]->cb.offset.x;
                    rbs[i]->cb.min.y = rbs[i]->pos.y + rbs[i]->cb.offset.y;
                    rbs[i]->cb.max.x = rbs[i]->cb.min.x + rbs[i]->cb.width;
                    rbs[i]->cb.max.y = rbs[i]->cb.min.y + rbs[i]->cb.height;
                }
                else if (prev_cb[i].max.y <= rbs[j]->cb.min.y)
                {
                    if (*rbs[i]->cb.tag == *"player" && *rbs[j]->cb.tag == *"ground")
                    {
                        rbs[i]->velocity.y = 0;
                        (rbs[i]->onCollisionEnter)(*rbs[j]);
                    }
                    else if (*rbs[i]->cb.tag == *"ground" && *rbs[j]->cb.tag == *"player")
                    {
                        rbs[j]->velocity.y = 0;
                        (rbs[j]->onCollisionEnter)(*rbs[i]);
                    }
                    rbs[i]->pos.y = prev_cb[i].min.y + rbs[j]->cb.min.y - prev_cb[i].max.y - prev_cb[i].offset.y;

                    rbs[i]->cb.min.x = rbs[i]->pos.x + rbs[i]->cb.offset.x;
                    rbs[i]->cb.min.y = rbs[i]->pos.y + rbs[i]->cb.offset.y;
                    rbs[i]->cb.max.x = rbs[i]->cb.min.x + rbs[i]->cb.width;
                    rbs[i]->cb.max.y = rbs[i]->cb.min.y + rbs[i]->cb.height;
                }
            }
        }
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

void apply_force(RigidBody *rb, float x, float y)
{
    //force = mass * acceleration
    //mass = 1, for now, so force = acceleration
    rb->acceleration.x += x;
    rb->acceleration.y += y;
}