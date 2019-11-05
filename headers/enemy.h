#ifndef ENEMY_H
#define ENEMY_H

#include "rigidbody.h"
#include "vector.h"

#define BAT "..\\assets\\Characters\\Bat.bmp"

typedef struct enemy
{
    RigidBody rb;
    int animation_frame, facing_right;
}Enemy;

void init_enemy(Enemy* enemy, Vector pos);



#endif // !"ENEMY_H"