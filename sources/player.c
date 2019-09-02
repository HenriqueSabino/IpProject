#include <allegro.h>
#include "../headers/player.h"
#include "../headers/vector.h"

void update_player(Player *player)
{
    update_limit_pos(&(player->rb), create_vector(0, 0), create_vector(SCREEN_W, SCREEN_H));
}

void init_player(Player *player)
{
    player->rb.acceleration = create_vector(0, 0);
    player->rb.gravity_scale = 0.1f;
    player->rb.pos = create_vector(0, 0);
    player->rb.velocity = create_vector(0, 0);
    player->rb.cb.width = 100;
    player->rb.cb.height = 100;
    player->rb.cb.min = create_vector(player->rb.pos.x, player->rb.pos.y);
    player->rb.cb.max = create_vector(player->rb.pos.x + player->rb.cb.width, player->rb.pos.y + player->rb.cb.height);
    player->rb.cb.solid = 1;
    player->rb.cb.tag = "player";
}

void set_velocity_axis(Player *player, char *axis, float s)
{
    if (*axis == *"horizontal")
    {
        player->rb.velocity.x = s;
    }
    else if (*axis == *"vertical")
    {
        player->rb.velocity.y = s;
    }
}