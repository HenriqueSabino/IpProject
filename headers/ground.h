#ifndef GROUND_H
#define GROUND_H

#include "rigidbody.h"

#define OVER_WORLD_GROUND "..\\assets\\Platforms\\OverworldGround.bmp"

typedef struct ground
{
     RigidBody rb;
     int animation_frame;
} Ground;

void init_ground(Ground *ground, Vector pos, int animation_frame);
//void set_velocity_axis(Player *player, char *axis, float s);
#endif // "GROUND_H"