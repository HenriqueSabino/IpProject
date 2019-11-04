#include <allegro.h>
#include <string.h>
#include "../headers/ground.h"
#include "../headers/vector.h"

void init_ground(Ground *ground)
{
    ground->rb.gravity_scale = 0;
    ground->rb.velocity = create_vector(0, 0);
    ground-> rb.acceleration = create_vector(0, 0);
    ground-> rb.pos = create_vector(60, SCREEN_H / 2);
    ground-> rb.cb.width = 500 ;
    ground-> rb.cb.height = 20;
    ground-> rb.cb.offset = create_vector(0, 0);
    ground-> rb.cb.min = create_vector(60, SCREEN_H / 2);
    ground-> rb.cb.max = create_vector(ground->rb.cb.min.x + ground->rb.cb.width, ground->rb.cb.min.y + ground->rb.cb.height);
    strcpy(ground->rb.cb.tag, "ground");
    ground-> rb.cb.solid = 0;
    ground-> rb.collidingWith = createList();
    ground-> rb.onCollisionEnter = NULL;
    ground-> rb.onCollisionExit = NULL;
    ground-> rb.onCollisionStay = NULL;
    
}
