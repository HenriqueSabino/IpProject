#include <allegro.h>
#include <string.h>
#include <stdio.h>
#include "../headers/enemy.h"
#include "../headers/player.h"
#include "../headers/collisionbox.h"
#include "../headers/vector.h"
#include "../headers/list.h"
#include "../headers/constants.h"

Enemy *enemies_ref;
int enemies_ref_count;

void onCollisionEnter_bat(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "sword") == 0 || strcmp(other->cb.tag, "arrow") == 0)
    {
        for (int i = 0; i < enemies_ref_count; i++)
        {
            if (&enemies_ref[i].rb == self)
            {

                enemies_ref[i].taking_damage = 1;

                if (strcmp(other->cb.tag, "sword") == 0)
                {
                    enemies_ref[i].life -= 2;
                }
                else if (strcmp(other->cb.tag, "arrow") == 0)
                {
                    enemies_ref[i].life--;
                }

                if (enemies_ref[i].life > 0)
                {
                    continue;
                }
                else
                {
                    self->velocity = create_vector(0, -15);
                    self->acceleration = create_vector(0, 0);
                    enemies_ref[i].alive = 0;
                }
            }
        }
    }
}

void init_bat(Enemy *bat, Vector pos)
{
    bat->animation_frame = 0;
    bat->facing_right = 0;
    bat->player_pos = create_vector(200, -32);
    bat->enemy_pos_ini = pos;
    bat->life = 6;
    bat->attack = 1;
    bat->alive = 1;
    bat->taking_damage = 0;

    bat->rb.acceleration = create_vector(0, 0);
    bat->rb.gravity_scale = 0;
    bat->rb.pos = pos;
    bat->rb.velocity = create_vector(0, 0);

    bat->rb.cb.width = 52;
    bat->rb.cb.height = 34;
    bat->rb.cb.offset = create_vector(6, 8);
    bat->rb.cb.min = create_vector(bat->rb.pos.x + bat->rb.cb.offset.x, bat->rb.pos.y + bat->rb.cb.offset.y);
    bat->rb.cb.max = create_vector(bat->rb.cb.min.x + bat->rb.cb.width, bat->rb.cb.min.y + bat->rb.cb.height);
    bat->rb.cb.solid = 0;
    bat->rb.cb.enabled = 1;
    bat->rb.collidingWith = createList();
    bat->rb.onCollisionEnter = onCollisionEnter_bat;
    bat->rb.onCollisionExit = NULL;
    bat->rb.onCollisionStay = NULL;
    strcpy(bat->rb.cb.tag, "bat");
}

void onCollisionEnter_fox(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "ground") == 0 || strcmp(other->cb.tag, "bridge") == 0)
    {
        if (self->cb.max.y < other->cb.min.y || self->cb.min.y > other->cb.max.y)
        {
            self->velocity.y = 0;
            self->acceleration = create_vector(0, 0);

            for (int i = 0; i < enemies_ref_count; i++)
            {
                if (&enemies_ref[i].rb == self)
                {
                    enemies_ref[i].taking_damage = 0;
                }
            }
        }
    }

    if (strcmp(other->cb.tag, "platform") == 0)
    {
        if (self->cb.max.y < other->cb.min.y)
        {
            self->velocity.y = 0;
            self->acceleration = create_vector(0, 0);

            for (int i = 0; i < enemies_ref_count; i++)
            {
                if (&enemies_ref[i].rb == self)
                {
                    enemies_ref[i].taking_damage = 0;
                }
            }
        }
    }

    if (strcmp(other->cb.tag, "sword") == 0 || strcmp(other->cb.tag, "arrow") == 0)
    {
        for (int i = 0; i < enemies_ref_count; i++)
        {
            if (&enemies_ref[i].rb == self)
            {
                enemies_ref[i].taking_damage = 1;

                if (strcmp(other->cb.tag, "sword") == 0)
                    enemies_ref[i].life -= 2;
                else if (strcmp(other->cb.tag, "arrow") == 0)
                    enemies_ref[i].life--;

                if (enemies_ref[i].life > 0)
                {
                    if (strcmp(other->cb.tag, "sword") == 0)
                    {
                        if (other->pos.x > self->pos.x)
                        {
                            self->velocity = create_vector(-10, -5);
                        }
                        else
                        {
                            self->velocity = create_vector(10, -5);
                        }
                    }
                    else if (strcmp(other->cb.tag, "arrow") == 0)
                    {
                        if (other->velocity.x < 0)
                        {
                            self->velocity = create_vector(-5, -5);
                        }
                        else
                        {
                            self->velocity = create_vector(5, -5);
                        }
                    }
                }
                else
                {
                    self->velocity = create_vector(0, -15);
                    self->acceleration = create_vector(0, 0);
                }
            }
        }
    }
}

void onCollisionStay_fox(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "ground") == 0 || strcmp(other->cb.tag, "bridge") == 0)
    {
        if (self->cb.max.y < other->cb.min.y || self->cb.min.y > other->cb.max.y)
        {
            self->velocity.y = 0;
            self->acceleration = create_vector(0, 0);

            for (int i = 0; i < enemies_ref_count; i++)
            {
                if (&enemies_ref[i].rb == self)
                {
                    enemies_ref[i].taking_damage = 0;
                }
            }
        }
    }

    if (strcmp(other->cb.tag, "platform") == 0)
    {
        if (self->cb.max.y < other->cb.min.y)
        {
            self->velocity.y = 0;
            self->acceleration = create_vector(0, 0);

            for (int i = 0; i < enemies_ref_count; i++)
            {
                if (&enemies_ref[i].rb == self)
                {
                    enemies_ref[i].taking_damage = 0;
                }
            }
        }
    }
}

void init_fox(Enemy *fox, Vector pos)
{
    fox->animation_frame = 0;
    fox->facing_right = 1;
    fox->player_pos = create_vector(0, 0);
    fox->enemy_pos_ini = create_vector(0, 0);
    fox->attack = 1;
    fox->life = 10;
    fox->alive = 1;

    fox->rb.acceleration = create_vector(0, 0);
    fox->rb.gravity_scale = 0.1f;
    fox->rb.pos = pos;
    fox->rb.velocity = create_vector(-5, 0);
    fox->taking_damage = 0;

    fox->rb.cb.width = 90;
    fox->rb.cb.height = 45;
    fox->rb.cb.offset = create_vector(0, 51);
    fox->rb.cb.min = create_vector(fox->rb.pos.x + fox->rb.cb.offset.x, fox->rb.pos.y + fox->rb.cb.offset.y);
    fox->rb.cb.max = create_vector(fox->rb.cb.min.x + fox->rb.cb.width, fox->rb.cb.min.y + fox->rb.cb.height);
    fox->rb.cb.solid = 1;
    fox->rb.cb.enabled = 1;
    fox->rb.collidingWith = createList();
    fox->rb.onCollisionEnter = onCollisionEnter_fox;
    fox->rb.onCollisionExit = NULL;
    fox->rb.onCollisionStay = onCollisionStay_fox;
    strcpy(fox->rb.cb.tag, "fox");
}

void init_harpy(Enemy *harpy, Vector pos)
{
    harpy->animation_frame = 0;
    harpy->facing_right = 0;
    harpy->player_pos = create_vector(200, -32);
    harpy->enemy_pos_ini = pos;
    harpy->life = 12;
    harpy->attack = 1;
    harpy->alive = 1;
    harpy->taking_damage = 0;

    harpy->rb.acceleration = create_vector(0, 0);
    harpy->rb.gravity_scale = 0;
    harpy->rb.pos = pos;
    harpy->rb.velocity = create_vector(0, 0);

    harpy->rb.cb.width = 50;
    harpy->rb.cb.height = 30;
    harpy->rb.cb.offset = create_vector(11, 22);
    harpy->rb.cb.min = create_vector(harpy->rb.pos.x + harpy->rb.cb.offset.x, harpy->rb.pos.y + harpy->rb.cb.offset.y);
    harpy->rb.cb.max = create_vector(harpy->rb.cb.min.x + harpy->rb.cb.width, harpy->rb.cb.min.y + harpy->rb.cb.height);
    harpy->rb.cb.solid = 0;
    harpy->rb.cb.enabled = 1;
    harpy->rb.collidingWith = createList();
    harpy->rb.onCollisionEnter = onCollisionEnter_bat;
    harpy->rb.onCollisionExit = NULL;
    harpy->rb.onCollisionStay = NULL;
    strcpy(harpy->rb.cb.tag, "harpy");
}

void init_ghost(Enemy *ghost, Vector pos)
{
    ghost->animation_frame = 0;
    ghost->facing_right = 0;
    ghost->player_pos = create_vector(200, -32);
    ghost->enemy_pos_ini = create_vector(0, 0);
    ghost->life = 666;
    ghost->attack = 1;
    ghost->alive = 1;
    ghost->taking_damage = 0;

    ghost->rb.acceleration = create_vector(0, 0);
    ghost->rb.gravity_scale = 0;
    ghost->rb.pos = pos;
    ghost->rb.velocity = create_vector(0, 0);

    ghost->rb.cb.width = 40;
    ghost->rb.cb.height = 40;
    ghost->rb.cb.offset = create_vector(7, 7);
    ghost->rb.cb.min = create_vector(ghost->rb.pos.x + ghost->rb.cb.offset.x, ghost->rb.pos.y + ghost->rb.cb.offset.y);
    ghost->rb.cb.max = create_vector(ghost->rb.cb.min.x + ghost->rb.cb.width, ghost->rb.cb.min.y + ghost->rb.cb.height);
    ghost->rb.cb.solid = 0;
    ghost->rb.cb.enabled = 1;
    ghost->rb.collidingWith = createList();
    ghost->rb.onCollisionEnter = NULL;
    ghost->rb.onCollisionExit = NULL;
    ghost->rb.onCollisionStay = NULL;
    strcpy(ghost->rb.cb.tag, "ghost");
}

void onCollision_spike(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "ground") == 0 || strcmp(other->cb.tag, "platform") == 0 || strcmp(other->cb.tag, "bridge") == 0)
    {
        if (self->cb.max.y < other->cb.min.y || self->cb.min.y > other->cb.max.y)
        {
            self->velocity.y = 0;
            self->acceleration = create_vector(0, 0);
            self->gravity_scale = 0;
            self->cb.enabled = 0;
            self->cb.solid = 0;
        }
    }
}

void init_spike(Enemy *spike, Vector pos)
{
    spike->animation_frame = 4;
    spike->facing_right = 0;
    spike->player_pos = create_vector(0, 0);
    spike->enemy_pos_ini = create_vector(0, 0);
    spike->life = 1;
    spike->attack = 1;
    spike->alive = 1;
    spike->taking_damage = 0;

    spike->rb.acceleration = create_vector(0, 0);
    spike->rb.gravity_scale = 0.1f;
    spike->rb.pos = pos;
    spike->rb.velocity = create_vector(0, 0);

    spike->rb.cb.width = 120;
    spike->rb.cb.height = 8;
    spike->rb.cb.offset = create_vector(4, 118);
    spike->rb.cb.min = create_vector(spike->rb.pos.x + spike->rb.cb.offset.x, spike->rb.pos.y + spike->rb.cb.offset.y);
    spike->rb.cb.max = create_vector(spike->rb.cb.min.x + spike->rb.cb.width, spike->rb.cb.min.y + spike->rb.cb.height);
    spike->rb.cb.solid = 1;
    spike->rb.cb.enabled = 1;
    spike->rb.collidingWith = createList();
    spike->rb.onCollisionEnter = onCollision_spike;
    spike->rb.onCollisionExit = NULL;
    spike->rb.onCollisionStay = onCollision_spike;
    strcpy(spike->rb.cb.tag, "spike");
}

void onCollisionEnter_jumperboss(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "sword") == 0 || strcmp(other->cb.tag, "arrow") == 0)
    {
        for (int i = 0; i < enemies_ref_count; i++)
        {
            if (&enemies_ref[i].rb == self)
            {
                enemies_ref[i].taking_damage = 1;

                if (strcmp(other->cb.tag, "sword") == 0)
                    enemies_ref[i].life -= 2;
                else if (strcmp(other->cb.tag, "arrow") == 0)
                    enemies_ref[i].life--;

                if (enemies_ref[i].life > 0)
                {
                    if (strcmp(other->cb.tag, "sword") == 0)
                    {
                        if (other->pos.x > self->pos.x)
                        {
                            self->velocity = create_vector(-10, -5);
                        }
                        else
                        {
                            self->velocity = create_vector(10, -5);
                        }
                    }
                    else if (strcmp(other->cb.tag, "arrow") == 0)
                    {
                        if (other->velocity.x < 0)
                        {
                            self->velocity = create_vector(-5, -5);
                        }
                        else
                        {
                            self->velocity = create_vector(5, -5);
                        }
                    }
                }
                else
                {
                    self->acceleration = create_vector(0, 0);
                    self->gravity_scale = 0;
                }
            }
        }
    }

    if (strcmp(other->cb.tag, "ground") == 0 || strcmp(other->cb.tag, "bridge") == 0)
    {
        if (self->cb.max.y < other->cb.min.y || self->cb.min.y > other->cb.max.y)
        {
            self->velocity.y = 0;
            self->acceleration = create_vector(0, 0);

            for (int i = 0; i < enemies_ref_count; i++)
            {
                if (&enemies_ref[i].rb == self)
                {
                    enemies_ref[i].taking_damage = 0;
                }
            }
        }
    }

    if (strcmp(other->cb.tag, "platform") == 0)
    {
        if (self->cb.max.y < other->cb.min.y)
        {
            self->velocity.y = 0;
            self->acceleration = create_vector(0, 0);

            for (int i = 0; i < enemies_ref_count; i++)
            {
                if (&enemies_ref[i].rb == self)
                {
                    enemies_ref[i].taking_damage = 0;
                }
            }
        }
    }
}

void onCollisionStay_jumperboss(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "ground") == 0 || strcmp(other->cb.tag, "bridge") == 0)
    {
        if (self->cb.max.y < other->cb.min.y || self->cb.min.y > other->cb.max.y)
        {
            self->velocity.y = 0;
            self->acceleration = create_vector(0, 0);

            for (int i = 0; i < enemies_ref_count; i++)
            {
                if (&enemies_ref[i].rb == self)
                {
                    enemies_ref[i].taking_damage = 0;
                }
            }
        }
    }

    if (strcmp(other->cb.tag, "platform") == 0)
    {
        if (self->cb.max.y < other->cb.min.y)
        {
            self->velocity.y = 0;
            self->acceleration = create_vector(0, 0);

            for (int i = 0; i < enemies_ref_count; i++)
            {
                if (&enemies_ref[i].rb == self)
                {
                    enemies_ref[i].taking_damage = 0;
                }
            }
        }
    }
}

void init_jumperboss(Enemy *jumperboss, Vector pos)
{
    jumperboss->animation_frame = 0;
    jumperboss->facing_right = 0;
    jumperboss->player_pos = create_vector(0, 0);
    jumperboss->life = 20;
    jumperboss->attack = 0;
    jumperboss->alive = 1;
    jumperboss->taking_damage = 0;

    jumperboss->rb.acceleration = create_vector(0, 0);
    jumperboss->rb.gravity_scale = 0.1f;
    jumperboss->rb.pos = pos;
    jumperboss->rb.velocity = create_vector(0, 0);

    jumperboss->rb.cb.width = 68;
    jumperboss->rb.cb.height = 88;
    jumperboss->rb.cb.offset = create_vector(40, 36);
    jumperboss->rb.cb.min = create_vector(jumperboss->rb.pos.x + jumperboss->rb.cb.offset.x, jumperboss->rb.pos.y + jumperboss->rb.cb.offset.y);
    jumperboss->rb.cb.max = create_vector(jumperboss->rb.cb.min.x + jumperboss->rb.cb.width, jumperboss->rb.cb.min.y + jumperboss->rb.cb.height);
    jumperboss->rb.cb.solid = 1;
    jumperboss->rb.cb.enabled = 1;
    jumperboss->rb.collidingWith = createList();
    jumperboss->rb.onCollisionEnter = onCollisionEnter_jumperboss;
    jumperboss->rb.onCollisionExit = NULL;
    jumperboss->rb.onCollisionStay = onCollisionStay_jumperboss;
    strcpy(jumperboss->rb.cb.tag, "jumperboss");
}

void atk(Enemy *enemy, RigidBody player)
{
    Vector player_pos = mult(sum(player.cb.min, player.cb.max), 0.5f);
    Vector enemy_pos = mult(sum(enemy->rb.cb.min, enemy->rb.cb.max), 0.5f);

    if (player_pos.x >= enemy_pos.x)
    {
        enemy->facing_right = 0;
    }
    else
    {
        enemy->facing_right = 1;
    }

    if ((strcmp(enemy->rb.cb.tag, "bat") == 0 || strcmp(enemy->rb.cb.tag, "harpy") == 0) && enemy->attack)
    {
        if (enemy->taking_damage == 1)
        {
            if (player_pos.x > enemy_pos.x)
            {
                enemy->rb.velocity = create_vector(-10, 0);
                enemy->rb.acceleration = create_vector(0, 0);
            }
            else
            {
                enemy->rb.velocity = create_vector(10, 0);
                enemy->rb.acceleration = create_vector(0, 0);
            }

            if (dist(create_vector(enemy->rb.pos.x, 0), create_vector(enemy->enemy_pos_ini.x, 0)) >= 100)
            {
                enemy->taking_damage = 0;
            }
        }

        if (dist(create_vector(enemy_pos.x, 0), create_vector(player_pos.x, 0)) <= 100 && !enemy->taking_damage)
        {
            enemy->rb.acceleration = create_vector(0, 0);
        }
        else if (dist(enemy->rb.pos, player_pos) <= SCREEN_WIDTH && !enemy->taking_damage)
        {
            if (dist(enemy_pos, sum(player_pos, enemy->player_pos)) <= 10)
            {
                enemy->player_pos.x *= -1;
                enemy->rb.acceleration = mult(normalized(diff(player_pos, enemy_pos)), 8);
            }
            enemy->rb.velocity = mult(normalized(diff(sum(player_pos, enemy->player_pos), enemy_pos)), 5);
        }

        if (enemy->taking_damage == 0)
            enemy->enemy_pos_ini = enemy->rb.pos;
    }
    else if (strcmp(enemy->rb.cb.tag, "fox") == 0 && enemy->taking_damage == 0 && enemy->rb.velocity.y == 0 && enemy->attack)
    {
        if (dist(enemy->rb.pos, player_pos) <= SCREEN_WIDTH)
        {
            if (dist(create_vector(enemy_pos.x, 0), create_vector(player_pos.x, 0)) <= 100)
            {
                enemy->rb.acceleration = create_vector(0, 0);
            }
            else if (dist(enemy->rb.pos, player_pos) <= SCREEN_WIDTH && !enemy->taking_damage)
            {
                if (dist(enemy_pos, sum(player_pos, enemy->player_pos)) <= 10)
                {
                    enemy->player_pos.x *= -1;
                    enemy->rb.acceleration = mult(normalized(diff(create_vector(player_pos.x, 0), create_vector(enemy_pos.x, 0))), 8);
                }
                enemy->rb.velocity = mult(normalized(diff(create_vector(player_pos.x, 0), create_vector(enemy_pos.x, 0))), 5);
            }

            enemy->rb.acceleration.y = 0;
            enemy->rb.velocity.y = 0;
        }
        else
        {
            enemy->rb.velocity = create_vector(0, 0);
        }
    }
    else if (strcmp(enemy->rb.cb.tag, "spike") == 0 && enemy->rb.cb.solid == 0)
    {
        if (enemy->animation_frame == 0)
        {
            enemy->rb.cb.width = 120;
            enemy->rb.cb.height = 76;
            enemy->rb.cb.offset = create_vector(4, 48);
            enemy->rb.cb.enabled = 1;
        }
        else if (enemy->animation_frame == 1 || enemy->animation_frame == 7)
        {
            enemy->rb.cb.width = 120;
            enemy->rb.cb.height = 56;
            enemy->rb.cb.offset = create_vector(4, 68);
            enemy->rb.cb.enabled = 1;
        }
        else if (enemy->animation_frame == 2 || enemy->animation_frame == 6)
        {
            enemy->rb.cb.width = 120;
            enemy->rb.cb.height = 44;
            enemy->rb.cb.offset = create_vector(4, 80);
            enemy->rb.cb.enabled = 1;
        }
        else if (enemy->animation_frame == 3 || enemy->animation_frame == 5)
        {
            enemy->rb.cb.width = 120;
            enemy->rb.cb.height = 28;
            enemy->rb.cb.offset = create_vector(4, 96);
            enemy->rb.cb.enabled = 1;
        }
        else
        {
            enemy->rb.cb.width = 120;
            enemy->rb.cb.height = 8;
            enemy->rb.cb.offset = create_vector(4, 118);
            enemy->rb.cb.enabled = 0;
        }
    }
}

void atk_ghost(Enemy *enemy, Player *player)
{
    Vector player_pos = mult(sum(player->rb.cb.min, player->rb.cb.max), 0.5f);
    Vector enemy_pos = mult(sum(enemy->rb.cb.min, enemy->rb.cb.max), 0.5f);

    if (player_pos.x >= enemy_pos.x)
    {
        enemy->facing_right = 0;
    }
    else
    {
        enemy->facing_right = 1;
    }

    if (enemy->facing_right == player->facing_right)
    {
        enemy->attack = 0;
    }
    else
    {
        enemy->attack = 1;
    }

    if (enemy->attack == 1)
    {
        if (dist(enemy->rb.pos, player_pos) <= SCREEN_WIDTH)
        {
            enemy->rb.velocity = mult(normalized(diff(player_pos, enemy_pos)), 2.5f);
        }
    }
    else
    {
        enemy->rb.velocity = create_vector(0, 0);
        enemy->rb.acceleration = create_vector(0, 0);
    }
}

void atk_jumperboss(Enemy *enemy, Player *player, int behavior)
{
    int attack_behavior = behavior;

    Vector player_pos = mult(sum(player->rb.cb.min, player->rb.cb.max), 0.5f);
    Vector enemy_pos = mult(sum(enemy->rb.cb.min, enemy->rb.cb.max), 0.5f);

    if (player->rb.cb.min.x > enemy_pos.x)
    {
        enemy->facing_right = 0;
        enemy->rb.cb.offset = create_vector(40, 36);
    }
    else
    {
        enemy->facing_right = 1;
        enemy->rb.cb.offset = create_vector(14, 36);
    }

    if (attack_behavior == 1)
    {
        if (enemy->taking_damage == 0 && enemy->rb.velocity.y == 0 && enemy->attack)
        {
            if (dist(create_vector(enemy_pos.x, 0), create_vector(player_pos.x, 0)) <= 100)
            {
                enemy->rb.acceleration = create_vector(0, 0);
            }
            else if (dist(enemy->rb.pos, player_pos) <= SCREEN_WIDTH && !enemy->taking_damage)
            {
                if (dist(enemy_pos, sum(player_pos, enemy->player_pos)) <= 10)
                {
                    enemy->player_pos.x *= -1;
                    enemy->rb.acceleration = mult(normalized(diff(create_vector(player_pos.x, 0), create_vector(enemy_pos.x, 0))), 8);
                }
                enemy->rb.velocity = mult(normalized(diff(create_vector(player_pos.x, 0), create_vector(enemy_pos.x, 0))), 5);
            }

            enemy->rb.acceleration.y = 0;
            enemy->rb.velocity.y = 0;
        }
    }
}

void set_enemies_ref(Enemy *enemies, int count)
{
    enemies_ref = enemies;
    enemies_ref_count = count;
}
