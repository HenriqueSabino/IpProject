#include <allegro.h>
#include <string.h>
#include <stdio.h>
#include "../headers/boss.h"
#include "../headers/player.h"
#include "../headers/rigidbody.h"
#include "../headers/collisionbox.h"
#include "../headers/vector.h"
#include "../headers/list.h"
#include "../headers/constants.h"

Boss *jb_ref;

int check_damage = 0;

void atk_jumper_boss(Boss *jumper_boss, Player *player, int behavior)
{
    jumper_boss->behavior = behavior;

    Vector player_pos = mult(sum(player->rb.cb.min, player->rb.cb.max), 0.5f);
    Vector jumper_boss_pos = mult(sum(jumper_boss->rb.cb.min, jumper_boss->rb.cb.max), 0.5f);

    if (player->rb.cb.min.x > jumper_boss->rb.pos.x)
    {
        jumper_boss->facing_right = 1;
        jumper_boss->rb.cb.offset = create_vector(40, 36);
    }
    else
    {
        jumper_boss->facing_right = 0;
        jumper_boss->rb.cb.offset = create_vector(14, 36);
    }

    if (jumper_boss->taking_damage == 1)
    {
        if (player_pos.x > jumper_boss_pos.x)
        {
            jumper_boss->rb.acceleration = create_vector(0, 0);
            jumper_boss->rb.velocity = create_vector(-5, -5);
            jumper_boss->taking_damage = -1;
        }
        else
        {
            jumper_boss->rb.acceleration = create_vector(0, 0);
            jumper_boss->rb.velocity = create_vector(5, -5);
            jumper_boss->taking_damage = -1;
        }
    }

    if (jumper_boss->behavior == 1)
    {
        if (jumper_boss->rb.velocity.y == 0)
        {
            if (dist(create_vector(jumper_boss_pos.x, 0), create_vector(player_pos.x, 0)) <= 100)
            {
                jumper_boss->rb.acceleration = create_vector(0, 0);
            }
            else if (!jumper_boss->taking_damage)
            {
                if (dist(jumper_boss_pos, sum(player_pos, jumper_boss->player_pos)) <= 10)
                {
                    jumper_boss->rb.velocity.x *= -1;
                }
                jumper_boss->rb.velocity = mult(normalized(diff(create_vector(player_pos.x, 0), create_vector(jumper_boss_pos.x, 0))), 5);
            }
        }
    }
    else if (jumper_boss->behavior == 2)
    {
        if (dist(jumper_boss->rb.pos, player_pos) <= 400)
        {
            if (jumper_boss->sleepy)
            {
                jumper_boss->animation_frame = 2;
            }
            jumper_boss->alert = 1;
            jumper_boss->sleepy = 0;
        }

        if (dist(player_pos, jumper_boss->rb.pos) <= 200)
        {
            jumper_boss->alert = 0;
            jumper_boss->angry = 1;
            jumper_boss->behavior = 1;
            jumper_boss->animation_frame = 4;
        }
    }
    else if (jumper_boss->behavior == 3)
    {
        if (jumper_boss->rb.velocity.y == 0)
            jumper_boss->rb.velocity = create_vector(0, -30);
    }

    if (check_damage == 1)
    {
        if (player->can_jump && !player->invulnerability)
        {
            player->life -= 5;
            player->taking_damage = 1;
            if (player->life > 0)
            {
                if (player_pos.x > jumper_boss_pos.x)
                {
                    player->rb.velocity = create_vector(10, -10);
                }
                else
                {
                    player->rb.velocity = create_vector(-10, -10);
                }
            }
            else
            {
                player->rb.velocity = create_vector(0, -15);
                player->rb.acceleration = create_vector(0, 0);
            }
        }
        if (jumper_boss->rb.pos.x > player_pos.x)
            jumper_boss->rb.velocity = mult(normalized(diff(create_vector(player_pos.x, 0), create_vector(jumper_boss_pos.x, 0))), 5);
        else
            jumper_boss->rb.velocity = mult(normalized(diff(create_vector(player_pos.x, 0), create_vector(jumper_boss_pos.x, 0))), -5);

        check_damage = 0;
    }
}

void onCollisionEnter_jumper_boss(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "ground") == 0)
    {
        if (self->cb.max.y < other->cb.min.y || self->cb.min.y > other->cb.max.y)
        {
            if (jb_ref->behavior == 3)
            {
                check_damage = 1;
            }
            jb_ref->behavior = 1;
            jb_ref->rb.velocity.y = 0;
            jb_ref->rb.acceleration = create_vector(0, 0);
            jb_ref->taking_damage = 0;
        }
    }

    else if (strcmp(other->cb.tag, "platform") == 0)
    {
        if (self->cb.max.y < other->cb.min.y)
        {
            if (jb_ref->behavior == 3)
            {
                check_damage = 1;
            }
            jb_ref->behavior = 1;
            jb_ref->rb.velocity.y = 0;
            jb_ref->rb.acceleration = create_vector(0, 0);
            jb_ref->taking_damage = 0;
        }
    }

    if (strcmp(other->cb.tag, "sword") == 0 || strcmp(other->cb.tag, "arrow") == 0)
    {
        if (!jb_ref->stomp_on && !jb_ref->fire_on)
        {
            jb_ref->taking_damage = 1;

            if (strcmp(other->cb.tag, "sword") == 0)
                jb_ref->life -= 2;
            else if (strcmp(other->cb.tag, "arrow") == 0)
                jb_ref->life--;

            if (jb_ref->life > 0)
            {
                return;
            }
            else
            {
                jb_ref->animation_frame = 10;
                self->velocity = create_vector(0, -2);
                self->acceleration = create_vector(0, 0);
            }
        }
    }
}

void onCollisionStay_jumper_boss(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "ground") == 0)
    {
        if (self->cb.max.y < other->cb.min.y || self->cb.min.y > other->cb.max.y)
        {
            jb_ref->rb.velocity.y = 0;
            jb_ref->rb.acceleration = create_vector(0, 0);
            jb_ref->taking_damage = 0;
        }
    }

    else if (strcmp(other->cb.tag, "platform") == 0)
    {
        if (self->cb.max.y < other->cb.min.y)
        {
            self->velocity.y = 0;
            self->acceleration = create_vector(0, 0);
            jb_ref->taking_damage = 0;
        }
    }
}

void init_jumper_boss(Boss *jumper_boss, Vector pos)
{
    jumper_boss->animation_frame = 0;
    jumper_boss->facing_right = 0;
    jumper_boss->player_pos = create_vector(0, 0);
    jumper_boss->boss_pos_ini = create_vector(0, 0);
    jumper_boss->life = 80;
    jumper_boss->alive = 1;
    jumper_boss->taking_damage = 0;
    jumper_boss->sleepy = 1;
    jumper_boss->angry = 0;
    jumper_boss->alert = 0;
    jumper_boss->behavior = 0;
    jumper_boss->stomp_on = 0;
    jumper_boss->fire_on = 0;

    jumper_boss->rb.acceleration = create_vector(0, 0);
    jumper_boss->rb.gravity_scale = 0.1f;
    jumper_boss->rb.pos = pos;
    jumper_boss->rb.velocity = create_vector(0, 0);

    jumper_boss->rb.cb.width = 68;
    jumper_boss->rb.cb.height = 88;
    jumper_boss->rb.cb.offset = create_vector(22, 36);
    jumper_boss->rb.cb.min = create_vector(jumper_boss->rb.pos.x + jumper_boss->rb.cb.offset.x, jumper_boss->rb.pos.y + jumper_boss->rb.cb.offset.y);
    jumper_boss->rb.cb.max = create_vector(jumper_boss->rb.cb.min.x + jumper_boss->rb.cb.width, jumper_boss->rb.cb.min.y + jumper_boss->rb.cb.height);
    jumper_boss->rb.cb.solid = 1;
    jumper_boss->rb.cb.enabled = 1;
    jumper_boss->rb.collidingWith = createList();
    jumper_boss->rb.onCollisionEnter = onCollisionEnter_jumper_boss;
    jumper_boss->rb.onCollisionExit = NULL;
    jumper_boss->rb.onCollisionStay = onCollisionStay_jumper_boss;
    strcpy(jumper_boss->rb.cb.tag, "jumper_boss");

    jb_ref = jumper_boss;
}

void onCollisionEnter_FB(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "player") == 0)
    {
        self->cb.enabled = 0;
    }
}

void init_fireball(Fireball *fireball, Vector pos)
{
    fireball->animation_frame = 0;

    fireball->rb.gravity_scale = 0;
    fireball->rb.velocity = create_vector(0, 0);
    fireball->rb.acceleration = create_vector(0, 0);
    fireball->rb.pos = pos;

    fireball->rb.cb.width = 64;
    fireball->rb.cb.height = 18;
    fireball->rb.cb.offset = create_vector(0, 22);

    fireball->rb.cb.min = create_vector(fireball->rb.pos.x, fireball->rb.pos.y);
    fireball->rb.cb.max = create_vector(fireball->rb.cb.min.x + fireball->rb.cb.width, fireball->rb.cb.min.y + fireball->rb.cb.height);
    strcpy(fireball->rb.cb.tag, "fireball");
    fireball->rb.cb.solid = 0;
    fireball->rb.cb.enabled = 0;
    fireball->rb.collidingWith = createList();
    fireball->rb.onCollisionEnter = onCollisionEnter_FB;
    fireball->rb.onCollisionExit = NULL;
    fireball->rb.onCollisionStay = NULL;
}