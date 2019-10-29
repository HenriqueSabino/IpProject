#include <allegro.h>
#include <string.h>
#include <stdio.h>
#include "../headers/player.h"
#include "../headers/vector.h"

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

void onCollisionEnter(RigidBody other)
{
    if (strcmp(other.cb.tag, "ground") == 0)
    {
        //printf("Collided with ground.");
    }
}

void init_player(Player *player)
{
    player->animation_frame = 8;
    player->facing_right = 1;

    player->rb.acceleration = create_vector(0, 0);
    player->rb.gravity_scale = 0.1f;
    player->rb.pos = create_vector(0, 0);
    player->rb.velocity = create_vector(0, 0);

    player->rb.cb.width = 42;
    player->rb.cb.height = 50;
    player->rb.cb.offset = create_vector(29, 31);
    player->rb.cb.min = create_vector(player->rb.pos.x + player->rb.cb.offset.x, player->rb.pos.y + player->rb.cb.offset.y);
    player->rb.cb.max = create_vector(player->rb.cb.min.x + player->rb.cb.width, player->rb.cb.min.y + player->rb.cb.height);
    player->rb.cb.solid = 1;
    strcpy(player->rb.cb.tag, "player");

    player->rb.onCollisionEnter = onCollisionEnter;
}