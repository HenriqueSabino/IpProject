#include <allegro.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../headers/constants.h"
#include "../headers/player.h"
#include "../headers/enemy.h"
#include "../headers/keyboard.h"
#include "../headers/list.h"
#include "../headers/ground.h"
#include "../headers/scenegeneration.h"
#include "../headers/menu.h"

volatile int close_game = FALSE;
void close_program()
{
    close_game = TRUE;
}
END_OF_FUNCTION(close_program)

volatile int counter = 0;
volatile long game_timer = 0;
void increment()
{
    counter++;
    game_timer++;
}
END_OF_FUNCTION(increment)

void draw_player(BITMAP *bmp, BITMAP *sprite, Player *player, Vector camera);

void draw_bat(BITMAP *bmp, BITMAP *sprite, Enemy *bat, Vector camera);

void draw_fox(BITMAP *bmp, BITMAP *sprite, Enemy *fox, Vector camera);

void draw_ground(BITMAP *bmp, BITMAP *sprite, Ground *ground, Vector camera);

void draw_lifebar(BITMAP *bmp, BITMAP *sprite, Player player);

int main()
{
    char *map;
    int map_size = readMap(&map, "../sources/map.txt");

    allegro_init();
    install_keyboard();
    install_timer();
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 64 * 16, 64 * 9, 0, 0);

    LOCK_VARIABLE(close_game);
    LOCK_FUNCTION(close_program);
    set_close_button_callback(close_program);

    LOCK_VARIABLE(game_timer);
    LOCK_VARIABLE(counter);
    LOCK_FUNCTION(increment);

    install_int_ex(increment, MSEC_TO_TIMER(1.0 / FPS * 1000));

    Vector camera;

    Player player;

    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP *player_sprite = load_bitmap(PLAYER_SPRITE_SHEET, NULL);
    if (player_sprite == NULL)
        allegro_message("error");

    BITMAP *bat_sprite = load_bitmap(BAT, NULL);
    if (bat_sprite == NULL)
        allegro_message("error");

    BITMAP *fox_sprite = load_bitmap(FOX, NULL);
    if (fox_sprite == NULL)
        allegro_message("error");

    BITMAP *ground_sprite = load_bitmap(OVER_WORLD_GROUND, NULL);
    if (ground_sprite == NULL)
        allegro_message("error");

    BITMAP *lifebar_sprite = load_bitmap("../assets/Canvas/LifeBar.bmp", NULL);
    if (lifebar_sprite == NULL)
        allegro_message("error");

    int row = 0, col = 0, not_objs = 0, ground_count = 0, enemy_count = 0;

    for (int i = 0; i < map_size; i++)
    {
        if (map[i] == 'G')
        {
            ground_count++;
        }
        else if (map[i] == 'B' || map[i] == 'F')
        {
            enemy_count++;
        }
    }

    Ground grounds[ground_count];
    ground_count = 0;

    Enemy enemies[enemy_count];
    enemy_count = 0;

    for (int i = 0; i < map_size; i++)
    {
        if (map[i] == 'P')
        {
            init_player(&player, create_vector(col * 128, row * 128));
            init_timer_invulnerability();
            camera = sum(player.rb.pos, create_vector(-100, -200));
            col++;
        }
        else if (map[i] == 'B')
        {
            init_bat(&enemies[enemy_count], create_vector(col * 128, row * 128));
            enemy_count++;
            col++;
        }
        else if (map[i] == 'F')
        {
            init_fox(&enemies[enemy_count], create_vector(col * 128, row * 128));
            enemy_count++;
            col++;
        }
        else if (map[i] == 'G')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 0);
            ground_count++;
            col++;
        }
        else if (map[i] == '*')
        {
            not_objs++;
            col++;
        }
        else if (map[i] == '\n')
        {
            row++;
            not_objs++;
            col = 0;
        }
    }

    RigidBody *rbs[map_size - not_objs];
    rbs[0] = &player.rb;
    for (int i = 0; i < ground_count; i++)
    {
        rbs[i + 1] = &grounds[i].rb;
    }

    for (int i = 0; i < enemy_count; i++)
    {
        rbs[i + ground_count + 1] = &enemies[i].rb;
    }

    while (!close_game)
    {

        if (player.life <= 0 || player.rb.pos.y >= 1000)
        {
            close_program();
            break;
        }

        keyboard_input();
        //USER INPUT
        if (key_down(KEY_ESC))
        {
            close_program();
        }
        if ((key_down(KEY_W) || key_down(KEY_SPACE)))
        {
            if (player.can_jump)
            {
                set_velocity_axis(&player, "vertical", -20);
            }
        }
        if (key_holding(KEY_A) || key_holding(KEY_D))
        {
            if (key_holding(KEY_A))
            {
                set_velocity_axis(&player, "horizontal", -5);
                player.facing_right = 0;
            }
            else
            {
                set_velocity_axis(&player, "horizontal", 5);
                player.facing_right = 1;
            }
        }
        else
        {
            set_velocity_axis(&player, "horizontal", 0);
        }

        if (key_down(KEY_F))
        {
            player.attacking = 1;
        }

        //UPDATE

        while (counter > 0)
        {
            update_all(rbs, map_size - not_objs);

            //linear interpolation between camera and player's position
            Vector offset_camera = create_vector(-100, -200);
            camera = lerp(camera, sum(player.rb.pos, offset_camera), 0.9f);

            for (int i = 0; i < enemy_count; i++)
            {
                if (strcmp(enemies[i].rb.cb.tag, "bat") == 0 || strcmp(enemies[i].rb.cb.tag, "fox") == 0)
                {
                    atk(&enemies[i], player.rb);

                    if (enemies[i].animation_frame >= 0 && enemies[i].animation_frame <= 3)
                    {
                        if (game_timer % 4 == 0)
                        {
                            enemies[i].animation_frame++;
                            enemies[i].animation_frame %= 4;
                        }
                    }
                }
            }
            
            if (player.animation_frame >= 0 && player.animation_frame <= 7)
            {
                if (game_timer % 4 == 0)
                {
                    player.animation_frame++;
                    player.animation_frame %= 8;
                }
            }

            if (player.animation_frame >= 12 && player.animation_frame <= 17)
            {
                if (game_timer % 2 == 0)
                {
                    player.animation_frame++;
                    if (12 + player.animation_frame % 6 != 12)
                    {
                        player.animation_frame = 12 + player.animation_frame % 6;
                    }
                    else
                    {
                        player.animation_frame = 8;
                        player.attacking = 0;
                    }                    
                }            
            }

            counter--;
        }

        //DRAWING
        draw_lifebar(buffer, lifebar_sprite, player);

        for (int i = 0; i < ground_count; i++)
        {
            draw_ground(buffer, ground_sprite, &grounds[i], camera);
        }

        draw_player(buffer, player_sprite, &player, camera);

        for (int i = 0; i < enemy_count; i++)
        {
            if (strcmp(enemies[i].rb.cb.tag, "bat") == 0)
            {
                draw_bat(buffer, bat_sprite, &enemies[i], camera);
            }
            else if (strcmp(enemies[i].rb.cb.tag, "fox") == 0)
            {
                draw_fox(buffer, fox_sprite, &enemies[i], camera);
            }
        }

        draw_sprite(screen, buffer, 0, 0);
        clear(buffer);
    }

    free(map);
    destroy_bitmap(buffer);
    destroy_bitmap(player_sprite);
    destroy_bitmap(bat_sprite);
    destroy_bitmap(fox_sprite);
    destroy_bitmap(ground_sprite);

    for (int i = 0; i < map_size - not_objs; i++)
    {
        destroy_list(rbs[i]->collidingWith);
    }

    return 0;
}
END_OF_MAIN();

void draw_player(BITMAP *bmp, BITMAP *sprite, Player *player, Vector camera)
{

    BITMAP *player_sprite = create_bitmap(128, 128);
    clear_to_color(player_sprite, makecol(255, 0, 255));

    if (abs(player->rb.velocity.x) > 0 && player->animation_frame > 7)
    {
        player->animation_frame = 0;
    }
    else if (player->rb.velocity.x == 0 && player->attacking == 0)
    {
        player->animation_frame = 8;
    }
    else if (player->rb.velocity.x == 0 && player->attacking != 0)
    {
        if (player->animation_frame < 12)
        {
            player->animation_frame = 12;
        }

        if (player->animation_frame < 17)
        {
            player->attacking = 1;
        }
    }

    if (!player->can_jump || player->rb.velocity.y != 0)
    {
        player->animation_frame = 10;
    }

    int r_img_pos = player->animation_frame % PLAYER_SPRITE_COLS;
    int c_img_pos = player->animation_frame / PLAYER_SPRITE_COLS;

    r_img_pos *= PLAYER_TILE_SIZE;
    c_img_pos *= PLAYER_TILE_SIZE;

    //draw the a part of the sprite sheet to the screen and scales it
    masked_stretch_blit(sprite, player_sprite, r_img_pos, c_img_pos, 50, 50, 0, 0, 128, 128);

    set_trans_blender(255, 255, 255, 64);

    if (player->facing_right)
    {
        if (player->invulnerability == 1)
        {
            if(game_timer % 2 == 0)
            {
                draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - camera.x, player->rb.pos.y - camera.y, DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - camera.x, player->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
            }
        }
        else
        {
            draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - camera.x, player->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
        }
    }
    else
    {
        if (player->invulnerability == 1)
        {
            if(game_timer % 4 == 0)
            {
                draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - camera.x, player->rb.pos.y - camera.y, DRAW_SPRITE_TRANS, DRAW_SPRITE_H_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - camera.x, player->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
            }
        }
        else
        {
            draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - camera.x, player->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
        }
    }

    destroy_bitmap(player_sprite);
}

void draw_bat(BITMAP *bmp, BITMAP *sprite, Enemy *bat, Vector camera)
{
    BITMAP *bat_sprite = create_bitmap(64, 64);
    clear_to_color(bat_sprite, makecol(255, 0, 255));

    int r_img_pos = bat->animation_frame % BAT_SPRITE_COLS;
    int c_img_pos = bat->animation_frame / BAT_SPRITE_COLS;

    r_img_pos *= BAT_TILE_SIZE;
    c_img_pos *= BAT_TILE_SIZE;

    //draw the a part of the sprite sheet to the screen and scales it
    masked_stretch_blit(sprite, bat_sprite, r_img_pos, c_img_pos, 32, 32, 0, 0, 64, 64);

    if (bat->facing_right)
    {
        draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - camera.x, bat->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
    }
    else
    {
        draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - camera.x, bat->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
    }
    destroy_bitmap(bat_sprite);
}

void draw_fox(BITMAP *bmp, BITMAP *sprite, Enemy *fox, Vector camera)
{
    BITMAP *fox_sprite = create_bitmap(96, 96);
    clear_to_color(fox_sprite, makecol(255, 0, 255));

    //rect(bmp, fox->rb.cb.min.x - camera.x, fox->rb.cb.min.y - camera.y, fox->rb.cb.max.x - camera.x, fox->rb.cb.max.y - camera.y, makecol(255,0,0));

    int r_img_pos = fox->animation_frame % FOX_SPRITE_COLS;
    int c_img_pos = fox->animation_frame / FOX_SPRITE_COLS;

    r_img_pos *= FOX_TILE_SIZE;
    c_img_pos *= FOX_TILE_SIZE;

    //draw the a part of the sprite sheet to the screen and scales it
    masked_stretch_blit(sprite, fox_sprite, r_img_pos, c_img_pos, 32, 32, 0, 0, 96, 96);

    if (fox->facing_right)
    {
        draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - camera.x, fox->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
    }
    else
    {
        draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - camera.x, fox->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
    }
    destroy_bitmap(fox_sprite);
}

void draw_ground(BITMAP *bmp, BITMAP *sprite, Ground *ground, Vector camera)
{
    BITMAP *ground_sprite = create_bitmap(128, 128);
    clear_to_color(ground_sprite, makecol(255, 0, 255));

    int r_img_pos = ground->animation_frame % GROUND_SPRITE_COLS;
    int c_img_pos = ground->animation_frame / GROUND_SPRITE_COLS;

    r_img_pos *= GROUND_TILE_SIZE;
    c_img_pos *= GROUND_TILE_SIZE;

    //draw the a part of the sprite sheet to the screen and scales it
    masked_stretch_blit(sprite, ground_sprite, r_img_pos, c_img_pos, 32, 32, 0, 0, 128, 128);

    draw_sprite_ex(bmp, ground_sprite, ground->rb.pos.x - camera.x, ground->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);

    destroy_bitmap(ground_sprite);
}

void draw_lifebar(BITMAP *bmp, BITMAP *sprite, Player player)
{
    char player_life[4];
    itoa(player.life, player_life, 10);
    strcat(player_life, "%");
    rectfill(bmp, 74, 34, 74 + floor(57 * player.life / 100.0f), 49, makecol(255, 0, 0));
    draw_sprite(bmp, sprite, 10, 10);
    textout_ex(bmp, font, player_life, 64 + 25, 38, makecol(255, 255, 0), -1);
}