#ifndef GROUND_H
#define GROUND_H

#include "rigidbody.h"

#define OVER_WORLD_GROUND "..\\assets\\Platforms\\OverworldGround.bmp"
#define OVER_WORLD_PLATFORM "..\\assets\\Platforms\\OverworldGround3.bmp"
#define CAVE_GROUND "..\\assets\\Platforms\\CaveGround.bmp"
#define HELL_GROUND "..\\assets\\Platforms\\HellGround.bmp"
#define CAVE_GROUND_PLATFORM "..\\assets\\Platforms\\CaveGround2.bmp"
#define LAVA "..\\assets\\Platforms\\LavaGround.bmp"
#define BRIDGE "..\\assets\\Platforms\\BridgePieces.bmp"

typedef struct ground
{
     RigidBody rb;
     int animation_frame;
} Ground;

void init_ground(Ground *ground, Vector pos, int animation_frame);
void init_platform(Ground *platform, Vector pos, int animation_frame);
void init_lava(Ground *lava, Vector pos, int animation_frame);
void init_bridge(Ground *bridge, Vector pos, int animation_frame);

#endif // "GROUND_H"