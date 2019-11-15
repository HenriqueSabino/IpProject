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

volatile int menu_on = TRUE;
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

void draw_harpy(BITMAP *bmp, BITMAP *sprite, Enemy *harpy, Vector camera);

void draw_ghost(BITMAP *bmp, BITMAP *sprite, Enemy *harpy, Vector camera);

void draw_ground(BITMAP *bmp, BITMAP *sprite, Ground *ground, Vector camera);

void draw_lifebar(BITMAP *bmp, BITMAP *sprite, Player player);

void draw_arrow(BITMAP *bmp, BITMAP *sprite);

int main()
{
    char *map;
    int map_size = readMap(&map, "../sources/map.txt");

    allegro_init();
    install_keyboard();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    install_timer();
    set_color_depth(desktop_color_depth());

    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    LOCK_VARIABLE(close_game);
    LOCK_FUNCTION(close_program);
    set_close_button_callback(close_program);

    LOCK_VARIABLE(game_timer);
    LOCK_VARIABLE(counter);
    LOCK_VARIABLE(menu_on);
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

    BITMAP *harpy_sprite = load_bitmap(HARPY, NULL);
    if (harpy_sprite == NULL)
        allegro_message("error");

    BITMAP *ghost_sprite = load_bitmap(GHOST, NULL);
    if (ghost_sprite == NULL)
        allegro_message("error");

    BITMAP *ground_sprite = load_bitmap(OVER_WORLD_GROUND, NULL);
    if (ground_sprite == NULL)
        allegro_message("error");

    BITMAP *lifebar_sprite = load_bitmap("../assets/Canvas/LifeBar.bmp", NULL);
    if (lifebar_sprite == NULL)
        allegro_message("error");

    BITMAP *arrow_sprite = load_bitmap(ARROW_PATH, NULL);
    if (arrow_sprite == NULL)
        allegro_message("error");

    int row = 0, col = 0, not_objs = 0, ground_count = 0, enemy_count = 0;

    for (int i = 0; i < map_size; i++)
    {
        if (map[i] == '0' || map[i] == '1' || map[i] == '2' || map[i] == '3' || map[i] == '4' ||
            map[i] == '5' || map[i] == '6' || map[i] == '7' || map[i] == '8' || map[i] == '9' ||
            map[i] == 'a' || map[i] == 'b' || map[i] == 'c')
        {
            ground_count++;
        }
        else if (map[i] == 'B' || map[i] == 'F'|| map[i] == 'H' || map[i] == 'G')
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
        else if (map[i] == 'H')
        {
            init_harpy(&enemies[enemy_count], create_vector(col * 128, row * 128));
            enemy_count++;
            col++;
        }
        else if (map[i] == 'G')
        {
            init_ghost(&enemies[enemy_count], create_vector(col * 128, row * 128));
            enemy_count++;
            col++;
        }
        else if (map[i] == '0')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 0);
            ground_count++;
            col++;
        }
        else if (map[i] == '1')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 1);
            ground_count++;
            col++;
        }
        else if (map[i] == '2')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 2);
            ground_count++;
            col++;
        }
        else if (map[i] == '3')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 3);
            ground_count++;
            col++;
        }
        else if (map[i] == '4')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 4);
            ground_count++;
            col++;
        }
        else if (map[i] == '5')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 5);
            ground_count++;
            col++;
        }
        else if (map[i] == '6')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 6);
            ground_count++;
            col++;
        }
        else if (map[i] == '7')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 7);
            ground_count++;
            col++;
        }
        else if (map[i] == '8')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 8);
            ground_count++;
            col++;
        }
        else if (map[i] == '9')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 9);
            ground_count++;
            col++;
        }
        else if (map[i] == 'a')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 10);
            ground_count++;
            col++;
        }
        else if (map[i] == 'b')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 11);
            ground_count++;
            col++;
        }
        else if (map[i] == 'c')
        {
            init_ground(&grounds[ground_count], create_vector(col * 128, row * 128), 12);
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

    int rbs_size = map_size - not_objs + 1;
    RigidBody *rbs[rbs_size];
    rbs[0] = &player.rb;
    for (int i = 0; i < ground_count; i++)
    {
        rbs[i + 1] = &grounds[i].rb;
    }

    for (int i = 0; i < enemy_count; i++)
    {
        rbs[i + ground_count + 1] = &enemies[i].rb;
    }

    set_enemies_ref(enemies, enemy_count);

    rbs[rbs_size - 1] = &player.sword_rb;

#pragma region menu
    //VARIABLES
    int chx = 355, chy = 420, som = 0;
    int py[2] = {420, 485};

    //BITMAPS
    BITMAP *menu = load_bitmap(LOGO_PATH, NULL);
    BITMAP *arrow = load_bitmap(ARROW_PATH, NULL);
    BITMAP *buff = create_bitmap(64 * 16, 64 * 9);

    //SAMPLES
    SAMPLE *select = load_sample(SELECT_SOUND);
    SAMPLE *intro = load_sample(INTRO_SOUND);
    SAMPLE *enter = load_sample(ENTER_SOUND);

    //INTRODUCTION SAMPLE
    play_sample(intro, 255, 128, 1000, 1);

    int animation_frame = 0;

    while (menu_on)
    {
        keyboard_input();

        //INPUT
        if (key_down(KEY_RIGHT) || key_down(KEY_LEFT))
        {
            som = 1;
        }

        if (key_down(KEY_DOWN))
        {
            chy = (chy == py[0]) ? py[1] : py[0];
            som = 1;
        }

        if (key_down(KEY_UP))
        {

            chy = (chy == py[0]) ? py[1] : py[0];
            som = 1;
        }

        if (key_down(KEY_ENTER))
        {
            if (chy == py[0])
            {
                stop_sample(intro);
                play_sample(enter, 255, 128, 1000, 0);
                menu_on = FALSE;
            }
            else
            {
                // OUTPUT FUNCTION
                return 0;
            }
        }

        if (key_down(KEY_ESC))
        {
            // OUTPUT FUNCTION
            return 0;
        }

        while (counter > 0)
        {
            if (animation_frame >= 0 && animation_frame <= 15)
            {
                if (game_timer % 2 == 0)
                {
                    animation_frame++;
                    animation_frame %= 16;
                }
            }

            int r_img_pos = animation_frame % ARROW_SPRITE_COLS;
            int c_img_pos = animation_frame / ARROW_SPRITE_COLS;

            r_img_pos *= ARROW_TILE_SIZE;
            c_img_pos *= ARROW_TILE_SIZE;

            //draw the a part of the sprite sheet to the screen and scales it
            masked_blit(arrow_sprite, buff, r_img_pos, c_img_pos, chx, chy, 32, 32);

            if (som == 1)
            {
                play_sample(select, 255, 128, 1000, 0);
                som = 0;
            }

            draw_sprite(screen, buff, 0, 0);
            clear(buff);
            draw_sprite(buff, menu, 0, 0);

            counter--;
        }
    }

    destroy_bitmap(buff);
    destroy_bitmap(menu);
    destroy_bitmap(arrow);
    destroy_sample(select);
    destroy_sample(intro);

#pragma endregion

    clear_to_color(buffer, 0x40AEBF);

    while (!close_game)
    {
        if(player.rb.pos.y >= 600)
        {
            player.life = 0;
        }

        if (player.life <= 0)
        {
            player.rb.cb.enabled = 0;
            player.sword_rb.cb.enabled = 0;
            if(player.rb.pos.y >= 1200)
            {
                close_program();
                break;
            }
        }

        keyboard_input();
        //USER INPUT
        if (key_down(KEY_ESC))
        {
            close_program();
        }
        if (key_down(KEY_W) || key_down(KEY_SPACE))
        {
            if (player.can_jump)
            {
                set_velocity_axis(&player, "vertical", -20);
            }
        }
        if ((key_holding(KEY_A) || key_holding(KEY_D)) && player.attacking == 0)
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
            if (!player.taking_damage)
                player.attacking = 1;
        }

        //UPDATE

        while (counter > 0)
        {
            update_all(rbs, rbs_size);

            //linear interpolation between camera and player's position
            Vector offset_camera = create_vector(-100, -200);

            if(player.life > 0)
            {
                camera = lerp(camera, sum(player.rb.pos, offset_camera), 0.9f);

                if (camera.x <= 0)
                {
                    camera.x = 0;
                }
                else if (camera.x + SCREEN_W >= grounds[ground_count - 1].rb.cb.max.x)
                {
                    camera.x = grounds[ground_count - 1].rb.cb.max.x - SCREEN_W;
                }

                if (camera.y + SCREEN_H >= grounds[ground_count - 1].rb.cb.max.y)
                {
                    camera.y = grounds[ground_count - 1].rb.cb.max.y - SCREEN_H;
                }
            }

            for (int i = 0; i < enemy_count; i++)
            {
                if (enemies[i].alive)
                {
                    if(strcmp(enemies[i].rb.cb.tag, "ghost") != 0)
                    {
                        atk(&enemies[i], player.rb);
                    }
                    else
                    {
                        atk_ghost(&enemies[i], &player);
                    }
                }

                if (!enemies[i].taking_damage && enemies[i].alive)
                {
                    if(strcmp(enemies[i].rb.cb.tag, "fox") == 0 || strcmp(enemies[i].rb.cb.tag, "fox") == 0)
                    {
                        if (enemies[i].animation_frame >= 0 && enemies[i].animation_frame <= 3)
                        {
                            if (game_timer % 4 == 0)
                            {
                                enemies[i].animation_frame++;
                                enemies[i].animation_frame %= 4;
                            }
                        }
                    }
                    else if(strcmp(enemies[i].rb.cb.tag, "harpy") == 0)
                    {
                        if (enemies[i].animation_frame >= 0 && enemies[i].animation_frame <= 4)
                        {
                            if (game_timer % 4 == 0)
                            {
                                enemies[i].animation_frame++;
                                enemies[i].animation_frame %= 5;
                            }
                        }
                    }
                    else if(strcmp(enemies[i].rb.cb.tag, "ghost") == 0)
                    {
                        if(enemies[i].attack == 1)
                        {
                            if (enemies[i].animation_frame >= 0 && enemies[i].animation_frame <= 3)
                            {
                                if (game_timer % 4 == 0)
                                {
                                    enemies[i].animation_frame++;
                                    enemies[i].animation_frame %= 4;
                                }
                            }
                        }
                        else
                        {
                            enemies[i].animation_frame = 0;
                        }
                    }
                }
                else
                {
                    if (strcmp(enemies[i].rb.cb.tag, "bat") == 0)
                        enemies[i].animation_frame = 3;
                    else
                        enemies[i].animation_frame = 0;
                }
            }

            // Kill enemy
            for (int i = 0; i < enemy_count; i++)
            {
                if (enemies[i].life <= 0)
                {
                    enemies[i].alive = 0;
                    enemies[i].attack = 0;
                    enemies[i].rb.gravity_scale = 0.2f;
                    enemies[i].rb.cb.enabled = 0;
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
                        player.sword_rb.cb.enabled = 0;
                    }
                }
            }
            counter--;
        }

        //DRAWING

        for (int i = 0; i < ground_count; i++)
        {
            draw_ground(buffer, ground_sprite, &grounds[i], camera);
        }

        draw_player(buffer, player_sprite, &player, camera);

        for (int i = 0; i < enemy_count; i++)
        {
            if (strcmp(enemies[i].rb.cb.tag, "bat") == 0 && enemies[i].rb.pos.y <= 1000)
            {
                draw_bat(buffer, bat_sprite, &enemies[i], camera);
                if (enemies[i].alive == 0 && enemies[i].rb.pos.y >= 1000)
                    enemies[i].rb.pos.y = 1001;
            }
            else if (strcmp(enemies[i].rb.cb.tag, "fox") == 0 && enemies[i].rb.pos.y <= 1000)
            {
                draw_fox(buffer, fox_sprite, &enemies[i], camera);
                if (enemies[i].alive == 0 && enemies[i].rb.pos.y >= 1000)
                    enemies[i].rb.pos.y = 1001;
            }
            else if (strcmp(enemies[i].rb.cb.tag, "harpy") == 0 && enemies[i].rb.pos.y <= 1000)
            {
                draw_harpy(buffer, harpy_sprite, &enemies[i], camera);
                if (enemies[i].alive == 0 && enemies[i].rb.pos.y >= 1000)
                    enemies[i].rb.pos.y = 1001;
            }
            else if (strcmp(enemies[i].rb.cb.tag, "ghost") == 0 && enemies[i].rb.pos.y <= 1000)
            {
                draw_ghost(buffer, ghost_sprite, &enemies[i], camera);
                if (enemies[i].alive == 0 && enemies[i].rb.pos.y >= 1000)
                    enemies[i].rb.pos.y = 1001;
            }
        }

        draw_lifebar(buffer, lifebar_sprite, player);

        draw_sprite(screen, buffer, 0, 0);
        clear_to_color(buffer, 0x40AEBF);
    }

    free(map);
    destroy_bitmap(buffer);
    destroy_bitmap(lifebar_sprite);
    destroy_bitmap(player_sprite);
    destroy_bitmap(harpy_sprite);
    destroy_bitmap(ghost_sprite);
    destroy_bitmap(bat_sprite);
    destroy_bitmap(fox_sprite);
    destroy_bitmap(ground_sprite);

    for (int i = 0; i < rbs_size; i++)
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
            if (player->animation_frame >= 16)
                player->sword_rb.cb.enabled = 1;
        }
    }

    if ((!player->can_jump || player->rb.velocity.y != 0) && player->attacking == 0)
    {
        player->animation_frame = 10;
    }
    else if ((!player->can_jump || player->rb.velocity.y != 0) && player->attacking != 0)
    {
        if (player->animation_frame < 12)
        {
            player->animation_frame = 12;
        }

        if (player->animation_frame < 17)
        {
            player->attacking = 1;
            if (player->animation_frame >= 16)
                player->sword_rb.cb.enabled = 1;
        }
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
        if (player->invulnerability == 1 && player->life > 0)
        {
            if (game_timer % 2 == 0)
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
        if (player->invulnerability == 1 && player->life > 0)
        {
            if (game_timer % 4 == 0)
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

    set_trans_blender(255, 255, 255, 64);

    if (bat->facing_right)
    {
        if (bat->taking_damage == 0 || bat->alive == 0)
        {
            draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - camera.x, bat->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
        }
        else
        {
            if (game_timer % 2 == 0)
            {
                draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - camera.x, bat->rb.pos.y - camera.y, DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - camera.x, bat->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
            }
        }
    }
    else
    {
        if (bat->taking_damage == 0 || bat->alive == 0)
        {
            draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - camera.x, bat->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
        }
        else
        {
            if (game_timer % 2 == 0)
            {
                draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - camera.x, bat->rb.pos.y - camera.y, DRAW_SPRITE_TRANS, DRAW_SPRITE_H_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - camera.x, bat->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
            }
        }
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

    set_trans_blender(255, 255, 255, 64);

    if (fox->facing_right)
    {
        if (fox->taking_damage == 0 || fox->alive == 0)
        {
            draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - camera.x, fox->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
        }
        else
        {
            if (game_timer % 2 == 0)
            {
                draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - camera.x, fox->rb.pos.y - camera.y, DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - camera.x, fox->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
            }
        }
    }
    else
    {
        if (fox->taking_damage == 0 || fox->alive == 0)
        {
            draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - camera.x, fox->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
        }
        else
        {
            if (game_timer % 2 == 0)
            {
                draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - camera.x, fox->rb.pos.y - camera.y, DRAW_SPRITE_TRANS, DRAW_SPRITE_H_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - camera.x, fox->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
            }
        }
    }

    destroy_bitmap(fox_sprite);
}

void draw_harpy(BITMAP *bmp, BITMAP *sprite, Enemy *harpy, Vector camera)
{
    BITMAP *harpy_sprite = create_bitmap(64, 64);
    clear_to_color(harpy_sprite, makecol(255, 0, 255));

    int r_img_pos = harpy->animation_frame % BAT_SPRITE_COLS;
    int c_img_pos = harpy->animation_frame / BAT_SPRITE_COLS;

    r_img_pos *= BAT_TILE_SIZE;
    c_img_pos *= BAT_TILE_SIZE;

    //draw the a part of the sprite sheet to the screen and scales it
    masked_stretch_blit(sprite, harpy_sprite, r_img_pos, c_img_pos, 32, 32, 0, 0, 64, 64);

    set_trans_blender(255, 255, 255, 64);

    if (harpy->facing_right)
    {
        if (harpy->taking_damage == 0 || harpy->alive == 0)
        {
            draw_sprite_ex(bmp, harpy_sprite, harpy->rb.pos.x - camera.x, harpy->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
        }
        else
        {
            if (game_timer % 2 == 0)
            {
                draw_sprite_ex(bmp, harpy_sprite, harpy->rb.pos.x - camera.x, harpy->rb.pos.y - camera.y, DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, harpy_sprite, harpy->rb.pos.x - camera.x, harpy->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
            }
        }
    }
    else
    {
        if (harpy->taking_damage == 0 || harpy->alive == 0)
        {
            draw_sprite_ex(bmp, harpy_sprite, harpy->rb.pos.x - camera.x, harpy->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
        }
        else
        {
            if (game_timer % 2 == 0)
            {
                draw_sprite_ex(bmp, harpy_sprite, harpy->rb.pos.x - camera.x, harpy->rb.pos.y - camera.y, DRAW_SPRITE_TRANS, DRAW_SPRITE_H_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, harpy_sprite, harpy->rb.pos.x - camera.x, harpy->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
            }
        }
    }

    destroy_bitmap(harpy_sprite);
}

void draw_ghost(BITMAP *bmp, BITMAP *sprite, Enemy *ghost, Vector camera)
{
    BITMAP *ghost_sprite = create_bitmap(64, 64);
    clear_to_color(ghost_sprite, makecol(255, 0, 255));

    int r_img_pos = ghost->animation_frame % BAT_SPRITE_COLS;
    int c_img_pos = ghost->animation_frame / BAT_SPRITE_COLS;

    r_img_pos *= BAT_TILE_SIZE;
    c_img_pos *= BAT_TILE_SIZE;

    //draw the a part of the sprite sheet to the screen and scales it
    masked_stretch_blit(sprite, ghost_sprite, r_img_pos, c_img_pos, 32, 32, 0, 0, 64, 64);

    set_trans_blender(255, 255, 255, 64);

    if (ghost->facing_right)
    {
        if (ghost->attack == 1)
        {
            draw_sprite_ex(bmp, ghost_sprite, ghost->rb.pos.x - camera.x, ghost->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
        }
        else
        {
            draw_sprite_ex(bmp, ghost_sprite, ghost->rb.pos.x - camera.x, ghost->rb.pos.y - camera.y, DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
        }
    }
    else
    {
        if (ghost->attack == 1)
        {
            draw_sprite_ex(bmp, ghost_sprite, ghost->rb.pos.x - camera.x, ghost->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
        }
        else
        {
            draw_sprite_ex(bmp, ghost_sprite, ghost->rb.pos.x - camera.x, ghost->rb.pos.y - camera.y, DRAW_SPRITE_TRANS, DRAW_SPRITE_H_FLIP);
        }
    }

    destroy_bitmap(ghost_sprite);
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