#include <allegro.h>
#include <string.h>
#include "../headers/enemy.h"
#include "../headers/vector.h"
#include "../headers/list.h"


void init_enemy(Enemy *bat, Vector pos)
{
    bat->animation_frame = 0;
    bat->facing_right = 0;
    bat->player_pos = create_vector(128, -32);

    bat->rb.acceleration = create_vector(0, 0);
    bat->rb.gravity_scale = 0;
    bat->rb.pos = pos;
    bat->rb.velocity = create_vector(0, 0);

    bat->rb.cb.width = 52;
    bat->rb.cb.height = 34;
    bat->rb.cb.offset = create_vector(6, 8);
    bat->rb.cb.min = create_vector(bat->rb.pos.x + bat->rb.cb.offset.x, bat->rb.pos.y + bat->rb.cb.offset.y);
    bat->rb.cb.max = create_vector(bat->rb.cb.min.x + bat->rb.cb.width, bat->rb.cb.min.y + bat->rb.cb.height);
    bat->rb.cb.solid = 0;
    bat->rb.collidingWith = createList();
    strcpy(bat->rb.cb.tag, "bat");
}

void atk(Enemy *enemy, RigidBody player)
{
    Vector player_pos = mult(sum(player.cb.min, player.cb.max), 0.5f);
    Vector enemy_pos = mult(sum(enemy->rb.cb.min, enemy->rb.cb.max), 0.5f);
    if (dist(enemy_pos, player_pos) <= 100){
        enemy->rb.acceleration = create_vector(0, 0);
    }
    else if(dist(enemy->rb.pos, player_pos) <= 400)
    {
        if (dist(enemy_pos, sum(player_pos, enemy->player_pos)) <= 10){
            enemy->player_pos.x *= -1;
            enemy->rb.acceleration = mult(normalized(diff(player_pos, enemy_pos)), 15);
        }
        enemy->rb.velocity = mult(normalized(diff(sum(player_pos, enemy->player_pos), enemy_pos)), 5);
    }
}