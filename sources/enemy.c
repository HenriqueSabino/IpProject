#include <allegro.h>
#include <string.h>
#include <stdio.h>
#include "../headers/enemy.h"
#include "../headers/collisionbox.h"
#include "../headers/vector.h"
#include "../headers/list.h"

Enemy *enemies_ref;
int enemies_ref_count;

void onCollisionEnter_bat(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "sword") == 0)
    {
        for (int i = 0; i < enemies_ref_count; i++)
        {
                if (&enemies_ref[i].rb == self)
                {
                    enemies_ref[i].taking_damage = 1;    
                }
        }
        
        if (other->pos.x > self->pos.x)
        {
            self->velocity.x = -10;
            self->velocity.y = 0;
        }
        else
        {
            self->velocity.x = 10;
            self->velocity.y = 0;
        }
        
    }

    // faz urro
    if (strcmp(other->cb.tag, "sword") == 0)
    {
        for (int i = 0; i < enemies_ref_count; i++)
        {
            if (&enemies_ref[i].rb == self)
            {
                    enemies_ref[i].life--;
                    if(enemies_ref[i].life <= 0)
                    {
                        enemies_ref[i].alive = 0;
                    }
                    printf("\n%d\n", enemies_ref[i].life);                      
            }
        }
    }
}

void init_bat(Enemy *bat, Vector pos)
{
    bat->animation_frame = 0;
    bat->facing_right = 0;
    bat->player_pos = create_vector(200, -32);
    bat->life = 3;
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
    if (strcmp(other->cb.tag, "ground") == 0)
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
    if (strcmp(other->cb.tag, "sword") == 0)
    {
        for (int i = 0; i < enemies_ref_count; i++)
        {
                if (&enemies_ref[i].rb == self)
                {
                    enemies_ref[i].taking_damage = 1;    
                }
        }
        for(int i = 0; i < enemies_ref_count; i++)
        {
            if(&enemies_ref[i].rb == self)
            {
                if(enemies_ref[i].life > 0)
                {
                    if (other->pos.x > self->pos.x)
                    {
                        self->velocity.x = -10;
                        self->velocity.y = -5;
                    }
                    else
                    {
                        self->velocity.x = 10;
                        self->velocity.y = -5;
                    }
                }
            }
        }
        
    }

    // faz urro
    if (strcmp(other->cb.tag, "sword") == 0)
    {
        for (int i = 0; i < enemies_ref_count; i++)
        {
            if (&enemies_ref[i].rb == self)
            {
                    enemies_ref[i].life--;  
                    printf("\n%d\n", enemies_ref[i].life);                     
            }
        }
    }
}

void onCollisionStay_fox(RigidBody *self, RigidBody *other)
{
    if (strcmp(other->cb.tag, "ground") == 0)
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
}

void init_fox(Enemy *fox, Vector pos)
{
    fox->animation_frame = 0;
    fox->facing_right = 1;
    fox->player_pos = create_vector(0, 0);
    fox->attack = 1;
    fox->life = 5;
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

    if (strcmp(enemy->rb.cb.tag, "bat") == 0 && enemy->attack)
    {
        if(dist(create_vector(enemy_pos.x, 0), create_vector(player_pos.x, 0)) >= 200)
        {
            enemy->taking_damage = 0;
        }

        if (dist(create_vector(enemy_pos.x, 0), create_vector(player_pos.x, 0)) <= 100)
        {
            enemy->rb.acceleration = create_vector(0, 0);
        }
        else if (dist(enemy->rb.pos, player_pos) <= 400 && !enemy->taking_damage)
        {
            if (dist(enemy_pos, sum(player_pos, enemy->player_pos)) <= 10)
            {
                enemy->player_pos.x *= -1;
                enemy->rb.acceleration = mult(normalized(diff(player_pos, enemy_pos)), 8);
            }
            enemy->rb.velocity = mult(normalized(diff(sum(player_pos, enemy->player_pos), enemy_pos)), 5);
        }
    }
    else if (strcmp(enemy->rb.cb.tag, "fox") == 0 && enemy->taking_damage == 0 && enemy->rb.velocity.y == 0 && enemy->attack)
    {
        if (dist(create_vector(enemy_pos.x, 0), create_vector(player_pos.x, 0)) <= 100)
        {
            enemy->rb.acceleration = create_vector(0, 0);
        }
        else if (dist(enemy->rb.pos, player_pos) <= 400)
        {
            if (player_pos.x > enemy_pos.x)
            {
                enemy->rb.velocity.x = 5;
                enemy->rb.acceleration.y = 0;
            }
            else
            {
                enemy->rb.velocity.x = -5;
                enemy->rb.acceleration.y = 0;
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