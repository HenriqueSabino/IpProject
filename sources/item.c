#include <allegro.h>
#include <string.h>
#include "../headers/item.h"
#include "../headers/vector.h"

void init_potion(Item *potion, Vector pos, int animation_frame)
{
    potion->animation_frame = animation_frame;

    potion->rb.gravity_scale = 0.1f;
    potion->rb.velocity = create_vector(0, 0);
    potion->rb.acceleration = create_vector(0, 0);
    potion->rb.pos = pos;

    potion->rb.cb.width = 32;
    potion->rb.cb.height = 32;
    potion->rb.cb.offset = create_vector(0, 12);

    potion->rb.cb.min = create_vector(potion->rb.pos.x, potion->rb.pos.y);
    potion->rb.cb.max = create_vector(potion->rb.cb.min.x + potion->rb.cb.width, potion->rb.cb.min.y + potion->rb.cb.height);
    strcpy(potion->rb.cb.tag, "potion");
    potion->rb.cb.solid = 1;
    potion->rb.cb.enabled = 1;
    potion->rb.collidingWith = createList();
    potion->rb.onCollisionEnter = onCollisionEnter_potion;
    potion->rb.onCollisionExit = NULL;
    potion->rb.onCollisionStay = onCollisionStay_potion;
}

void onCollisionEnter_potion(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "ground") == 0 || strcmp(other->cb.tag, "bridge") == 0 || strcmp(other->cb.tag, "platform") == 0)
    {
        if (self->cb.max.y < other->cb.min.y || self->cb.min.y > other->cb.max.y)
        {
            self->velocity.y = 0;
            self->acceleration = create_vector(0, 0);
        }
    }
}
void onCollisionStay_potion(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "ground") == 0 || strcmp(other->cb.tag, "bridge") == 0 || strcmp(other->cb.tag, "platform") == 0)
    {
        if (self->cb.max.y < other->cb.min.y || self->cb.min.y > other->cb.max.y)
        {
            self->velocity.y = 0;
            self->acceleration = create_vector(0, 0);
        }
    }
}

void init_arrow_attack(Item *arrow_attack, Vector pos)
{
    arrow_attack->animation_frame = 0;

    arrow_attack->rb.gravity_scale = 0;
    arrow_attack->rb.velocity = create_vector(0, 0);
    arrow_attack->rb.acceleration = create_vector(0, 0);
    arrow_attack->rb.pos = pos;

    arrow_attack->rb.cb.width = 5;
    arrow_attack->rb.cb.height = 8;
    arrow_attack->rb.cb.offset = create_vector(7, 21);

    arrow_attack->rb.cb.min = create_vector(arrow_attack->rb.pos.x, arrow_attack->rb.pos.y);
    arrow_attack->rb.cb.max = create_vector(arrow_attack->rb.cb.min.x + arrow_attack->rb.cb.width, arrow_attack->rb.cb.min.y + arrow_attack->rb.cb.height);
    strcpy(arrow_attack->rb.cb.tag, "arrow");
    arrow_attack->rb.cb.solid = 0;
    arrow_attack->rb.cb.enabled = 0;
    arrow_attack->rb.collidingWith = createList();
    arrow_attack->rb.onCollisionEnter = onCollisionEnter_arrow;
    arrow_attack->rb.onCollisionExit = NULL;
    arrow_attack->rb.onCollisionStay = NULL;
}

void onCollisionEnter_arrow(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "bat") == 0 || strcmp(other->cb.tag, "fox") == 0 || strcmp(other->cb.tag, "harpy") == 0 || strcmp(other->cb.tag, "jumper_boss") == 0)
    {
        self->cb.enabled = 0;
    }
}