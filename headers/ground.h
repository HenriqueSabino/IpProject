#ifndef GROUND_H
#define GROUND_H

#include "rigidbody.h"


#define OVER_WORLD_GROUND "..\\assets\\Platforms\\OverworldGround.bmp"

typedef struct ground
{
     RigidBody rb;    
     int frame_position;
} Ground;


void init_ground(Ground *ground);
//void set_velocity_axis(Player *player, char *axis, float s);
#endif // "GROUND_H"