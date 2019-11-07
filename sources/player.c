#include <allegro.h>
#include <string.h>
#include <stdio.h>
#include "../headers/player.h"
#include "../headers/vector.h"

Player *player_ref;



void set_velocity_axis(Player *player, char *axis, float s)
{
    if (strcmp(axis, "horizontal") == 0)
    {
        player->rb.velocity.x = s;
    }
    else if (strcmp(axis, "vertical") == 0)
    {
        player->rb.velocity.y = s;
    }
}

void onCollisionEnter(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "ground") == 0)
    {
        if (self->cb.max.y < other->cb.min.y || self->cb.min.y > other->cb.max.y)
        {
            if (self->cb.max.y < other->cb.min.y)
            {
                player_ref->can_jump = 1;
            }
            self->velocity.y = 0;
        }
    }
    if (strcmp(other->cb.tag, "bat") == 0)
    {
        player_ref->life--;

        if(player_ref->facing_right == 1)
        {
            player_ref->rb.acceleration.x = -10;
            player_ref->rb.acceleration.y = -2;
        }
        else
        {
            player_ref->rb.acceleration.x = 10;
            player_ref->rb.acceleration.y = -2;
        }

    }
}

void onCollisionStay(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "ground") == 0)
    {
        if (self->cb.max.y < other->cb.min.y || self->cb.min.y > other->cb.max.y)
        {
            self->velocity.y = 0;
            player_ref->can_jump = 1;
        }
    }
}

void onCollisionExit(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "ground") == 0)
    {
        player_ref->can_jump = 0;
    }
    else if (strcmp(other->cb.tag, "bat") == 0)
    {
        player_ref->rb.acceleration = create_vector(0, 0);
    }
}

void init_player(Player *player, Vector pos)
{
    player->animation_frame = 8;
    player->facing_right = 1;
    player->life = 100;

    player->rb.acceleration = create_vector(0, 0);
    player->rb.gravity_scale = 0.1f;
    player->rb.pos = pos;
    player->rb.velocity = create_vector(0, 0);

    player->rb.cb.width = 54;
    player->rb.cb.height = 65;
    player->rb.cb.offset = create_vector(37, 39);
    player->rb.cb.min = create_vector(player->rb.pos.x + player->rb.cb.offset.x, player->rb.pos.y + player->rb.cb.offset.y);
    player->rb.cb.max = create_vector(player->rb.cb.min.x + player->rb.cb.width, player->rb.cb.min.y + player->rb.cb.height);
    player->rb.cb.solid = 1;
    strcpy(player->rb.cb.tag, "player");

    player->rb.onCollisionEnter = onCollisionEnter;
    player->rb.onCollisionExit = onCollisionExit;
    player->rb.onCollisionStay = onCollisionStay;
    player->rb.collidingWith = createList();
    player->can_jump = 0;

    player_ref = player;
}