#include <allegro.h>
#include <string.h>
#include "../headers/ground.h"
#include "../headers/vector.h"

void init_ground(Ground *ground, Vector pos, int animation_frame)
{
    ground->animation_frame = animation_frame;

    ground->rb.gravity_scale = 0;
    ground->rb.velocity = create_vector(0, 0);
    ground-> rb.acceleration = create_vector(0, 0);
    ground->rb.pos = pos;
    ground-> rb.cb.width = 128;
    ground-> rb.cb.height = 128;
    ground-> rb.cb.offset = create_vector(0, 0);
    ground-> rb.cb.min = create_vector(ground->rb.pos.x, ground->rb.pos.y);
    ground-> rb.cb.max = create_vector(ground->rb.cb.min.x + ground->rb.cb.width, ground->rb.cb.min.y + ground->rb.cb.height);
    strcpy(ground->rb.cb.tag, "ground");
    ground-> rb.cb.solid = 1;
    ground-> rb.collidingWith = createList();
    ground-> rb.onCollisionEnter = NULL;
    ground-> rb.onCollisionExit = NULL;
    ground-> rb.onCollisionStay = NULL;
}
