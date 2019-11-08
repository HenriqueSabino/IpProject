#ifndef ENEMY_H
#define ENEMY_H

#include "rigidbody.h"
#include "vector.h"

#define BAT "..\\assets\\Characters\\Bat.bmp"

typedef struct enemy
{
    RigidBody rb;
    Vector player_pos;
    int animation_frame, facing_right, live, atack;
} Enemy;

void init_bat(Enemy *enemy, Vector pos);
void atk(Enemy *enemy, RigidBody pos);

#endif // !"ENEMY_H"