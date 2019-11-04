#ifndef ENEMY_H
#define ENEMY_H

#include "rigidbody.h"

#define BAT "..\\assets\\Characters\\Bat.bmp"

typedef struct enemy
{
    RigidBody rb;
    int animation_frame, facing_right;
}Enemy;

void init_enemy(Enemy* enemy);
void atk();



#endif // !"ENEMY_H"