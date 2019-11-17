#ifndef ENEMY_H
#define ENEMY_H

#include "rigidbody.h"
#include "vector.h"
#include "player.h"

#define BAT "..\\assets\\Characters\\Bat.bmp"
#define FOX "..\\assets\\Characters\\Fox.bmp"
#define HARPY "..\\assets\\Characters\\Harpy.bmp"
#define GHOST "..\\assets\\Characters\\Ghost.bmp"
#define SPIKE "..\\assets\\Platforms\\Spikes.bmp"

typedef struct enemy
{
    RigidBody rb;
    Vector player_pos;
    int animation_frame, facing_right, attack, taking_damage, life, alive;
} Enemy;

void init_bat(Enemy *enemy, Vector pos);
void init_fox(Enemy *enemy, Vector pos);
void init_harpy(Enemy *enemy, Vector pos);
void init_ghost(Enemy *enemy, Vector pos);
void init_spike(Enemy *enemy, Vector pos);
void atk(Enemy *enemy, RigidBody pos);
void atk_ghost(Enemy *enemy, Player *player);
void set_enemies_ref(Enemy *enemies, int count);

#endif // !"ENEMY_H"