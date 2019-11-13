#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/rigidbody.h"
#include "../headers/constants.h"
#include "../headers/collisionbox.h"
#include "../headers/list.h"

void update(RigidBody *rb)
{
    rb->velocity = sum(rb->velocity, create_vector(rb->acceleration.x, rb->acceleration.y + GRAVITY * rb->gravity_scale));
    rb->pos = sum(rb->pos, rb->velocity);

    rb->cb.min = sum(rb->pos, rb->cb.offset);
    rb->cb.max.x = rb->cb.min.x + rb->cb.width;
    rb->cb.max.y = rb->cb.min.y + rb->cb.height;
}

void update_all(RigidBody *rbs[], int amount)
{
    CollisionBox rbs_before_update[amount];
    CollisionBox rbs_after_update[amount];
    for (int i = 0; i < amount; i++)
    {
        rbs_before_update[i] = rbs[i]->cb;
        update(rbs[i]);
        rbs_after_update[i] = rbs[i]->cb;
    }
    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < amount; j++)
        {
            if (i == j || strcmp(rbs[i]->cb.tag, "ground") == 0)
            {
                continue;
            }

            DataNode other_cb;
            other_cb.value = &rbs[j]->cb;

            if (collided(rbs[i]->cb, rbs[j]->cb))
            {
                if (rbs[i]->cb.solid && rbs[j]->cb.solid && rbs[i]->cb.enabled && rbs[j]->cb.enabled && strcmp(rbs[j]->cb.tag, "fox") != 0)
                {
                    if (rbs_before_update[i].min.y >= rbs[j]->cb.max.y)
                    {
                        rbs[i]->pos.y = rbs_before_update[i].min.y - (rbs_before_update[i].min.y - rbs[j]->cb.max.y) - rbs_before_update[i].offset.y + 1;
                    }
                    else if (rbs_before_update[i].max.y <= rbs[j]->cb.min.y)
                    {
                        rbs[i]->pos.y = rbs_before_update[i].min.y + rbs[j]->cb.min.y - rbs_before_update[i].max.y - rbs_before_update[i].offset.y - 1;
                    }
                    else if (rbs_before_update[i].min.x >= rbs[j]->cb.max.x)
                    {
                        rbs[i]->pos.x = (rbs_before_update[i].min.x) - (rbs_before_update[i].min.x - rbs[j]->cb.max.x) - rbs_before_update[i].offset.x + 1;
                    }
                    else if (rbs_before_update[i].max.x <= rbs[j]->cb.min.x)
                    {
                        rbs[i]->pos.x = rbs_before_update[i].min.x + rbs[j]->cb.min.x - rbs_before_update[i].max.x - rbs_before_update[i].offset.x - 1;
                    }

                    rbs[i]->cb.min = sum(rbs[i]->pos, rbs[i]->cb.offset);
                    rbs[i]->cb.max = sum(rbs[i]->cb.min, create_vector(rbs[i]->cb.width, rbs[i]->cb.height));
                }
            }
            else
            {
                int index = indexof(rbs[i]->collidingWith, other_cb);
                if (index != -1)
                {
                    remove_at(rbs[i]->collidingWith, index);
                    if (rbs[i]->onCollisionExit != NULL)
                    {
                        (rbs[i]->onCollisionExit)(rbs[i], rbs[j]);
                    }
                }
            }
        }
    }
    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < amount; j++)
        {
            if (i == j || strcmp(rbs[i]->cb.tag, "ground") == 0)
            {
                continue;
            }
            DataNode other_cb;
            other_cb.value = &rbs[j]->cb;

            if (collided(rbs_after_update[i], rbs_after_update[j]))
            {
                if (indexof(rbs[i]->collidingWith, other_cb) != -1)
                {
                    if (rbs[i]->onCollisionStay != NULL)
                    {
                        (rbs[i]->onCollisionStay)(rbs[i], rbs[j]);
                    }
                }
                else
                {
                    push(rbs[i]->collidingWith, other_cb);
                    if (rbs[i]->onCollisionEnter != NULL)
                    {
                        (rbs[i]->onCollisionEnter)(rbs[i], rbs[j]);
                    }
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