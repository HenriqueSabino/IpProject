#include <allegro.h>
#include <string.h>
#include "../headers/enemy.h"
#include "../headers/vector.h"

Enemy *bat_ref;

void init_enemy(Enemy *bat, Vector pos)
{
    bat->animation_frame = 0;
    bat->facing_right = 0;

    bat->rb.acceleration = create_vector(0, 0);
    bat->rb.gravity_scale = 0.1f;
    bat->rb.pos = pos;
    bat->rb.velocity = create_vector(0, 0);

    bat->rb.cb.width = 52;
    bat->rb.cb.height = 34;
    bat->rb.cb.offset = create_vector(6, 8);
    bat->rb.cb.min = create_vector(bat->rb.pos.x + bat->rb.cb.offset.x, bat->rb.pos.y + bat->rb.cb.offset.y);
    bat->rb.cb.max = create_vector(bat->rb.cb.min.x + bat->rb.cb.width, bat->rb.cb.min.y + bat->rb.cb.height);
    bat->rb.cb.solid = 0;
    strcpy(bat->rb.cb.tag, "bat");

    bat_ref = bat;
}