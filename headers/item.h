#ifndef ITEM_H
#define ITEM_H

#include "rigidbody.h"

#define ITEM_PATH "..\\assets\\Canvas\\LifePotion.bmp"


typedef struct item
{
     RigidBody rb;
     int animation_frame;
} Item;

void init_potion(Item *potion, Vector pos, int animation_frame);
void onCollisionEnter_potion(RigidBody *self, RigidBody *other);
void onCollisionStay_potion(RigidBody *self, RigidBody *other);

#endif // "ITEM_H"