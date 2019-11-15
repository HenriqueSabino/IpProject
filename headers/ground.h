#ifndef GROUND_H
#define GROUND_H

#include "rigidbody.h"

#define OVER_WORLD_GROUND "..\\assets\\Platforms\\OverworldGround.bmp"
#define OVER_WORLD_PLATFORM "..\\assets\\Platforms\\OverworldGround3.bmp"

typedef struct ground
{
     RigidBody rb;
     int animation_frame;
} Ground;

void init_ground(Ground *ground, Vector pos, int animation_frame);
void init_platform(Ground *ground, Vector pos, int animation_frame);

#endif // "GROUND_H"