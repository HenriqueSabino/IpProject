#include <allegro.h>
#include <string.h>
#include "../headers/ground.h"
#include "../headers/vector.h"

void init_ground(Ground *ground, Vector pos, int animation_frame)
{
    ground->animation_frame = animation_frame;

    ground->rb.gravity_scale = 0;
    ground->rb.velocity = create_vector(0, 0);
    ground->rb.acceleration = create_vector(0, 0);
    ground->rb.pos = pos;

    if (animation_frame == 0 || animation_frame == 1 || animation_frame == 2 || animation_frame == 7)
    {
        ground->rb.cb.width = 128;
        ground->rb.cb.height = 100;
        ground->rb.cb.offset = create_vector(0, 28);
    }
    else if (animation_frame == 3)
    {
        ground->rb.cb.width = 116;
        ground->rb.cb.height = 128;
        ground->rb.cb.offset = create_vector(0, 0);
    }
    else if (animation_frame == 4)
    {
        ground->rb.cb.width = 116;
        ground->rb.cb.height = 128;
        ground->rb.cb.offset = create_vector(12, 0);
    }
    else
    {
        ground->rb.cb.width = 128;
        ground->rb.cb.height = 128;
        ground->rb.cb.offset = create_vector(0, 0);
    }

    ground->rb.cb.min = create_vector(ground->rb.pos.x, ground->rb.pos.y);
    ground->rb.cb.max = create_vector(ground->rb.cb.min.x + ground->rb.cb.width, ground->rb.cb.min.y + ground->rb.cb.height);
    strcpy(ground->rb.cb.tag, "ground");
    ground->rb.cb.solid = 1;
    ground->rb.cb.enabled = 1;
    ground->rb.collidingWith = createList();
    ground->rb.onCollisionEnter = NULL;
    ground->rb.onCollisionExit = NULL;
    ground->rb.onCollisionStay = NULL;
}
