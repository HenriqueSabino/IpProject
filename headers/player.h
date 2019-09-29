#ifndef PLAYER_H
#define PLAYER_H

#include "rigidbody.h"

#define PLAYER_SPRITE_SHEET "..\\assets\\PlayerSpriteSheet.bmp"

typedef struct player
{
    RigidBody rb;
    int animation_frame, facing_right;
} Player;

void init_player(Player *player);
void set_velocity_axis(Player *player, char *axis, float s);

#endif // !"PLAYER_H"