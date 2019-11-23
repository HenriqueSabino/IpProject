#ifndef ITEM_H
#define ITEM_H

#include "rigidbody.h"

#define ITEM_PATH "..\\assets\\Canvas\\LifePotion.bmp"
#define ARROW_ATTACK "..\\assets\\Canvas\\Arrow_attack.bmp"

typedef struct item
{
     RigidBody rb;
     int animation_frame;
} Item;

void init_potion(Item *potion, Vector pos, int animation_frame);
void init_arrow_attack(Item *arrow_attack, Vector pos);
void onCollisionEnter_potion(RigidBody *self, RigidBody *other);
void onCollisionStay_potion(RigidBody *self, RigidBody *other);
void onCollisionEnter_arrow(RigidBody *self, RigidBody *other);

#endif // "ITEM_H"