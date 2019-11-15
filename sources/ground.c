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

    if (animation_frame == 0 || animation_frame == 7 || animation_frame == 9 || animation_frame == 10)
    {
        ground->rb.cb.width = 128;
        ground->rb.cb.height = 100;
        ground->rb.cb.offset = create_vector(0, 28);
    }
    else if (animation_frame == 1)
    {
        ground->rb.cb.width = 116;
        ground->rb.cb.height = 100;
        ground->rb.cb.offset = create_vector(12, 28);
    }
    else if (animation_frame == 2)
    {
        ground->rb.cb.width = 116;
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

void init_platform(Ground *platform, Vector pos, int animation_frame)
{
    platform->animation_frame = animation_frame;

    platform->rb.gravity_scale = 0;
    platform->rb.velocity = create_vector(0, 0);
    platform->rb.acceleration = create_vector(0, 0);
    platform->rb.pos = pos;

    if (animation_frame == 0)
    {
        platform->rb.cb.width = 128;
        platform->rb.cb.height = 1;
        platform->rb.cb.offset = create_vector(0, 28);
    }
    else if (animation_frame == 1)
    {
        platform->rb.cb.width = 116;
        platform->rb.cb.height = 1;
        platform->rb.cb.offset = create_vector(12, 28);
    }
    else if (animation_frame == 2)
    {
        platform->rb.cb.width = 116;
        platform->rb.cb.height = 1;
        platform->rb.cb.offset = create_vector(0, 28);
    }

    platform->rb.cb.min = create_vector(platform->rb.pos.x, platform->rb.pos.y);
    platform->rb.cb.max = create_vector(platform->rb.cb.min.x + platform->rb.cb.width, platform->rb.cb.min.y + platform->rb.cb.height);
    strcpy(platform->rb.cb.tag, "platform");
    platform->rb.cb.solid = 1;
    platform->rb.cb.enabled = 1;
    platform->rb.collidingWith = createList();
    platform->rb.onCollisionEnter = NULL;
    platform->rb.onCollisionExit = NULL;
    platform->rb.onCollisionStay = NULL;
}

void init_lava(Ground *lava, Vector pos, int animation_frame)
{
    lava->animation_frame = animation_frame;

    lava->rb.gravity_scale = 0;
    lava->rb.velocity = create_vector(0, 0);
    lava->rb.acceleration = create_vector(0, 0);
    lava->rb.pos = pos;

    if (animation_frame == 4)
    {
        lava->rb.cb.width = 128;
        lava->rb.cb.height = 128;
        lava->rb.cb.offset = create_vector(0, 0);
    }
    else
    {
        lava->rb.cb.width = 128;
        lava->rb.cb.height = 120;
        lava->rb.cb.offset = create_vector(0, 8);
    }
    

    lava->rb.cb.min = create_vector(lava->rb.pos.x, lava->rb.pos.y);
    lava->rb.cb.max = create_vector(lava->rb.cb.min.x + lava->rb.cb.width, lava->rb.cb.min.y + lava->rb.cb.height);
    strcpy(lava->rb.cb.tag, "lava");
    lava->rb.cb.solid = 1;
    lava->rb.cb.enabled = 1;
    lava->rb.collidingWith = createList();
    lava->rb.onCollisionEnter = NULL;
    lava->rb.onCollisionExit = NULL;
    lava->rb.onCollisionStay = NULL;
}
