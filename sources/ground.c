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

    if (animation_frame == 0 || animation_frame == 8 || animation_frame == 9)
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
    else if (animation_frame == 6)
    {
        ground->rb.cb.width = 104;
        ground->rb.cb.height = 100;
        ground->rb.cb.offset = create_vector(12, 28);
    }
    else if (animation_frame == 7)
    {
        ground->rb.cb.width = 104;
        ground->rb.cb.height = 100;
        ground->rb.cb.offset = create_vector(12, 28);
    }
    else if (animation_frame == 11)
    {
        ground->rb.cb.width = 128;
        ground->rb.cb.height = 100;
        ground->rb.cb.offset = create_vector(0, 0);
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

    if (animation_frame == 0 || animation_frame == 1 || animation_frame == 2 || animation_frame == 3)
        platform->rb.pos = pos;
    else
        platform->rb.pos = sum(pos, create_vector(0, 28));

    if (animation_frame == 0 || animation_frame == 4)
    {
        platform->rb.cb.width = 128;
        platform->rb.cb.height = 1;
        platform->rb.cb.offset = create_vector(0, 28);
    }
    else if (animation_frame == 1 || animation_frame == 5)
    {
        platform->rb.cb.width = 116;
        platform->rb.cb.height = 1;
        platform->rb.cb.offset = create_vector(12, 28);
    }
    else if (animation_frame == 2 || animation_frame == 6)
    {
        platform->rb.cb.width = 116;
        platform->rb.cb.height = 1;
        platform->rb.cb.offset = create_vector(0, 28);
    }
    else if (animation_frame == 3 || animation_frame == 7)
    {
        platform->rb.cb.width = 104;
        platform->rb.cb.height = 1;
        platform->rb.cb.offset = create_vector(12, 28);
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

    lava->rb.cb.width = 128;
    lava->rb.cb.height = 80;
    lava->rb.cb.offset = create_vector(0, 48);

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

void init_bridge(Ground *bridge, Vector pos, int animation_frame)
{
    bridge->animation_frame = animation_frame;

    bridge->rb.gravity_scale = 0;
    bridge->rb.velocity = create_vector(0, 0);
    bridge->rb.acceleration = create_vector(0, 0);
    bridge->rb.pos = pos;

    if (animation_frame >= 0 && animation_frame <= 2)
    {
        bridge->rb.cb.width = 128;
        bridge->rb.cb.height = 116;
        bridge->rb.cb.offset = create_vector(0, 28);
    }
    else
    {
        bridge->rb.cb.width = 32;
        bridge->rb.cb.height = 128;
        bridge->rb.cb.offset = create_vector(0, 0);
    }

    bridge->rb.cb.min = create_vector(bridge->rb.pos.x, bridge->rb.pos.y);
    bridge->rb.cb.max = create_vector(bridge->rb.cb.min.x + bridge->rb.cb.width, bridge->rb.cb.min.y + bridge->rb.cb.height);
    strcpy(bridge->rb.cb.tag, "bridge");
    bridge->rb.cb.solid = 1;
    bridge->rb.cb.enabled = 1;
    bridge->rb.collidingWith = createList();
    bridge->rb.onCollisionEnter = NULL;
    bridge->rb.onCollisionExit = NULL;
    bridge->rb.onCollisionStay = NULL;
}
