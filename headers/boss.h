#ifndef BOSS_H
#define BOSS_H

#include "rigidbody.h"
#include "vector.h"
#include "player.h"

#define JUMPER_BOSS "..\\assets\\Characters\\JumperBoss.bmp"

typedef struct boss
{
    RigidBody rb;
    Vector player_pos;
    Vector boss_pos_ini;
    int animation_frame, facing_right, taking_damage, life, alive, sleepy, angry, alert;
} Boss;

void init_jumper_boss(Boss *jumper_boss, Vector pos);
void atk_jumper_boss(Boss *jumper_boss, Player *player, int behavior);

#endif // !"BOSS_H"