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