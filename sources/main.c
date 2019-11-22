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
#include "../headers/item.h"

#pragma region functions
volatile int close_game = 0;
void close_program()
{
    close_game = 1;
}
END_OF_FUNCTION(close_program)

int menu_on = 1;
int death_on = 0;
volatile int counter = 0;
volatile int player_animation_counter = 0;
volatile long game_timer = 0;

void increment()
{
    counter++;
    game_timer++;
    player_animation_counter++;
}
END_OF_FUNCTION(increment)

void draw_player(BITMAP *bmp, BITMAP *sprite, Player *player, Vector camera);

void draw_bat(BITMAP *bmp, BITMAP *sprite, Enemy *bat, Vector camera);

void draw_fox(BITMAP *bmp, BITMAP *sprite, Enemy *fox, Vector camera);

void draw_harpy(BITMAP *bmp, BITMAP *sprite, Enemy *harpy, Vector camera);

void draw_ghost(BITMAP *bmp, BITMAP *sprite, Enemy *ghost, Vector camera);

void draw_spike(BITMAP *bmp, BITMAP *sprite, Enemy *spike, Vector camera);

void draw_ground(BITMAP *bmp, BITMAP *sprite, Ground *ground, Vector camera);

void draw_platform(BITMAP *bmp, BITMAP *sprite, Ground *platform, Vector camera);

void draw_lava(BITMAP *bmp, BITMAP *sprite, Ground *lava, Vector camera);

void draw_bridge(BITMAP *bmp, BITMAP *sprite, Ground *bridge, Vector camera);

void draw_object(BITMAP *bmp, BITMAP *sprite, Object *scenario, Vector camera);

void draw_lifebar(BITMAP *bmp, BITMAP *sprite, Player player);

void draw_arrow(BITMAP *bmp, BITMAP *sprite);

void draw_potion(BITMAP *bmp, BITMAP *sprite, Item *potion, Vector camera);

#pragma endregion

int main()
{
#pragma region allegro initialization
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
    LOCK_VARIABLE(death_on);
    LOCK_FUNCTION(increment);

    install_int_ex(increment, MSEC_TO_TIMER(1.0 / FPS * 1000));

    int playing_first_level = 0;

    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);

#pragma endregion

#pragma region loading sprites
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

    BITMAP *spike_sprite = load_bitmap(SPIKE, NULL);
    if (spike_sprite == NULL)
        allegro_message("error");

    BITMAP *ground_sprite = load_bitmap(OVER_WORLD_GROUND, NULL);
    if (ground_sprite == NULL)
        allegro_message("error");

    BITMAP *platform_sprite = load_bitmap(OVER_WORLD_PLATFORM, NULL);
    if (platform_sprite == NULL)
        allegro_message("error");

    BITMAP *lava_sprite = load_bitmap(LAVA, NULL);
    if (lava_sprite == NULL)
        allegro_message("error");

    BITMAP *bridge_sprite = load_bitmap(BRIDGE, NULL);
    if (bridge_sprite == NULL)
        allegro_message("error");

    BITMAP *scenario_sprite = load_bitmap(SCENARIO, NULL);
    if (scenario_sprite == NULL)
        allegro_message("error");

    BITMAP *lifebar_sprite = load_bitmap("../assets/Canvas/LifeBar.bmp", NULL);
    if (lifebar_sprite == NULL)
        allegro_message("error");

    BITMAP *montain_sprite = load_bitmap("../assets/Scenario/Montain.bmp", NULL);
    if (montain_sprite == NULL)
        allegro_message("error");

    BITMAP *ground_background_sprite = load_bitmap("../assets/Scenario/Ground_Background.bmp", NULL);
    if (ground_background_sprite == NULL)
        allegro_message("error");

    BITMAP *arrow_sprite = load_bitmap(ARROW_PATH, NULL);
    if (arrow_sprite == NULL)
        allegro_message("error");

    BITMAP *potion_sprite = load_bitmap(ITEM_PATH, NULL);
    if (potion_sprite == NULL)
        allegro_message("error");

#pragma endregion

    while (!close_game)
    {
#pragma region menu
        //VARIABLES
        int chx = 355, chy = 420, som = FALSE;
        int py[2] = {420, 485};

        //BITMAPS
        BITMAP *menu = load_bitmap(LOGO_PATH, NULL);
        BITMAP *arrow = load_bitmap(ARROW_PATH, NULL);

        //SAMPLES
        SAMPLE *select = load_sample(SELECT_SOUND);
        SAMPLE *intro = load_sample(INTRO_SOUND);
        SAMPLE *enter = load_sample(ENTER_SOUND);

        //INTRODUCTION SAMPLE
        play_sample(intro, 255, 128, 1000, 1);

        int animation_frame = 0;

        while (menu_on && !close_game)
        {
            keyboard_input();

            //INPUT
            if (key_down(KEY_RIGHT) || key_down(KEY_LEFT))
            {
                som = TRUE;
            }

            if (key_down(KEY_DOWN))
            {
                chy = (chy == py[0]) ? py[1] : py[0];
                som = TRUE;
            }

            if (key_down(KEY_UP))
            {

                chy = (chy == py[0]) ? py[1] : py[0];
                som = TRUE;
            }

            if (key_down(KEY_ENTER))
            {
                if (chy == py[0])
                {
                    stop_sample(intro);
                    menu_on = 0;
                    playing_first_level = 1;
                }
                else
                {
                    close_program();
                }
            }

            if (key_down(KEY_ESC))
            {
                close_program();
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
                masked_blit(arrow_sprite, buffer, r_img_pos, c_img_pos, chx, chy, 32, 32);

                if (som)
                {
                    play_sample(select, 255, 128, 1000, 0);
                    som = FALSE;
                }

                draw_sprite(screen, buffer, 0, 0);
                clear(buffer);
                draw_sprite(buffer, menu, 0, 0);

                counter--;
            }
        }

        destroy_bitmap(menu);
        destroy_sample(intro);

#pragma endregion

        clear_to_color(buffer, 0x40AEBF);
#pragma region first level
#pragma region generating first level

        char *map;
        int map_size = readMap(&map, "../sources/level_1.txt");

        char *scenario_map;
        int scenario_map_size = readMap(&scenario_map, "../sources/level_1_scenario.txt");

        Vector camera;

        Player player;

        int row = 0, col = 0, not_objs = 0, ground_count = 0, enemy_count = 0, object_count = 0, item_count = 0;

        for (int i = 0; i < map_size; i++)
        {
            if (map[i] == '0' || map[i] == '1' || map[i] == '2' || map[i] == '3' || map[i] == '4' ||
                map[i] == '5' || map[i] == '6' || map[i] == '7' || map[i] == '8' || map[i] == '9' ||
                map[i] == 'a' || map[i] == 'b' || map[i] == 'c' || map[i] == 'd' || map[i] == 'e' ||
                map[i] == 'f' || map[i] == 'g' || map[i] == 'h' || map[i] == 'i' || map[i] == 'j' ||
                map[i] == 'L' || map[i] == 'k' || map[i] == 'l' || map[i] == 'm' || map[i] == 'n')
            {
                ground_count++;
            }
            else if (map[i] == 'B' || map[i] == 'F' || map[i] == 'H' || map[i] == 'G' || map[i] == 'I')
            {
                enemy_count++;
            }
            else if (map[i] == 'p')
            {
                item_count++;
            }
        }

        for (int i = 0; i < scenario_map_size; i++)
        {
            if (scenario_map[i] == '1' || scenario_map[i] == '2' || scenario_map[i] == '3' || scenario_map[i] == '4' || scenario_map[i] == '5' ||
                scenario_map[i] == '6' || scenario_map[i] == '7' || scenario_map[i] == '8' || scenario_map[i] == '9' || scenario_map[i] == 'a' ||
                scenario_map[i] == 'b' || scenario_map[i] == 'W' || scenario_map[i] == 'w' || scenario_map[i] == 'C' || scenario_map[i] == 'L')
            {
                object_count++;
            }
        }

        Ground grounds[ground_count];
        ground_count = 0;

        Enemy enemies[enemy_count];
        enemy_count = 0;

        Object objects[object_count];
        object_count = 0;

        Item items[item_count];
        item_count = 0;

        int temp_col = 0;

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
            else if (map[i] == 'I')
            {
                init_spike(&enemies[enemy_count], create_vector(col * 128, row * 128));
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
            else if (map[i] == 'd')
            {
                init_platform(&grounds[ground_count], create_vector(col * 128, row * 128), 0);
                ground_count++;
                col++;
            }
            else if (map[i] == 'e')
            {
                init_platform(&grounds[ground_count], create_vector(col * 128, row * 128), 1);
                ground_count++;
                col++;
            }
            else if (map[i] == 'f')
            {
                init_platform(&grounds[ground_count], create_vector(col * 128, row * 128), 2);
                ground_count++;
                col++;
            }
            else if (map[i] == 'g')
            {
                init_platform(&grounds[ground_count], create_vector(col * 128, row * 128), 3);
                ground_count++;
                col++;
            }
            else if (map[i] == 'k')
            {
                init_platform(&grounds[ground_count], create_vector(col * 128, row * 128), 4);
                ground_count++;
                col++;
            }
            else if (map[i] == 'l')
            {
                init_platform(&grounds[ground_count], create_vector(col * 128, row * 128), 5);
                ground_count++;
                col++;
            }
            else if (map[i] == 'm')
            {
                init_platform(&grounds[ground_count], create_vector(col * 128, row * 128), 6);
                ground_count++;
                col++;
            }
            else if (map[i] == 'n')
            {
                init_platform(&grounds[ground_count], create_vector(col * 128, row * 128), 7);
                ground_count++;
                col++;
            }
            else if (map[i] == 'h')
            {
                init_bridge(&grounds[ground_count], create_vector(col * 128, row * 128), 0);
                ground_count++;
                col++;
            }
            else if (map[i] == 'i')
            {
                init_bridge(&grounds[ground_count], create_vector(col * 128, row * 128), 1);
                ground_count++;
                col++;
            }
            else if (map[i] == 'j')
            {
                init_bridge(&grounds[ground_count], create_vector(col * 128, row * 128), 2);
                ground_count++;
                col++;
            }
            else if (map[i] == 'L')
            {
                init_lava(&grounds[ground_count], create_vector(col * 128, row * 128), 0);
                ground_count++;
                col++;
            }
            else if (map[i] == 'p')
            {
                init_potion(&items[item_count], create_vector(col * 128, row * 128), 0);
                item_count++;
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
                temp_col = col;
                col = 0;
            }
        }

        BITMAP *level_background = create_bitmap(temp_col * 128, row * 128);
        clear_to_color(level_background, 0xFF00FF);

        row = col = 0;
        for (int i = 0; i < scenario_map_size; i++)
        {
            if (scenario_map[i] == '1')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 0);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == '2')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 1);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == '3')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 2);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == '4')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 3);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == '5')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 9);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == '6')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 16);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == '7')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 17);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == '8')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 18);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == '9')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 19);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == 'a')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 20);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == 'b')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 21);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == 'W')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 4);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == 'w')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 8);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == 'C')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 10);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == 'L')
            {
                init_object(&objects[object_count], create_vector(col * 128, row * 128), 11);
                object_count++;
                col++;
            }
            else if (scenario_map[i] == '*' || scenario_map[i] == 'X')
            {
                col++;
            }
            else if (scenario_map[i] == '\n')
            {
                row++;
                col = 0;
            }
        }

        int rbs_size = map_size - not_objs + 1;
        RigidBody *rbs[rbs_size];
        rbs[0] = &player.rb;

        for (int i = 0; i < object_count; i++)
        {
            if (objects[i].sprite_frame != 4)
                draw_object(level_background, scenario_sprite, &objects[i], create_vector(0, 0));
        }

        for (int i = 0; i < ground_count; i++)
        {
            rbs[i + 1] = &grounds[i].rb;

            if (!(strcmp(grounds[i].rb.cb.tag, "platform") == 0 || strcmp(grounds[i].rb.cb.tag, "bridge") == 0))
                draw_ground(level_background, ground_sprite, &grounds[i], create_vector(0, 0));
        }

        for (int i = 0; i < enemy_count; i++)
        {
            rbs[i + ground_count + 1] = &enemies[i].rb;
        }

        for (int i = 0; i < item_count; i++)
        {
            rbs[i + ground_count + enemy_count + 1] = &items[i].rb;
        }

        set_enemies_ref(enemies, enemy_count);

        rbs[rbs_size - 1] = &player.sword_rb;

#pragma endregion
        while (playing_first_level && !close_game)
        {
            if (player.rb.pos.y >= grounds[ground_count - 1].rb.cb.max.y ||
                player.rb.pos.x <= -256 || player.life <= 0)
            {
                player.life = 0;
                player.rb.cb.enabled = 0;
                player.sword_rb.cb.enabled = 0;
            }
            if (player.rb.pos.y >= grounds[ground_count - 1].rb.cb.max.y + 256)
            {
                playing_first_level = 0;
                death_on = 1;
                break;
            }
            keyboard_input();
            //USER INPUT
            if (key_down(KEY_ESC))
            {
                playing_first_level = 0;
                menu_on = 1;
                break;
            }
            if (key_down(KEY_W) || key_down(KEY_SPACE))
            {
                if (player.can_jump)
                {
                    set_velocity_axis(&player, "vertical", -20);
                }
            }
            if ((key_holding(KEY_A) || key_holding(KEY_D)) && !player.attacking && !player.bow_attack)
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

            if (key_down(KEY_Q))
            {
                if (!player.taking_damage)
                {
                    player.attacking = 1;
                    player_animation_counter = 0;
                }
            }
            if (key_down(KEY_E))
            {
                if (!player.taking_damage)
                {
                    player.bow_attack = 1;
                    player_animation_counter = 0;
                }
            }

            //UPDATE

            while (counter > 0)
            {
                update_all(rbs, rbs_size, camera);

                //linear interpolation between camera and player's position
                Vector offset_camera = create_vector(-SCREEN_WIDTH / 2 + 64, -200);

                if (player.life > 0)
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
                        if (strcmp(enemies[i].rb.cb.tag, "ghost") != 0)
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
                        if (strcmp(enemies[i].rb.cb.tag, "bat") == 0 || strcmp(enemies[i].rb.cb.tag, "fox") == 0)
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
                        else if (strcmp(enemies[i].rb.cb.tag, "harpy") == 0)
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
                        else if (strcmp(enemies[i].rb.cb.tag, "ghost") == 0)
                        {
                            if (enemies[i].attack == 1)
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
                        else if (strcmp(enemies[i].rb.cb.tag, "spike") == 0)
                        {

                            if (game_timer % 70 < 32 && game_timer % 70 != 0)
                            {
                                enemies[i].animation_frame = 0;
                            }
                            else if (game_timer % 70 > 36 && game_timer % 70 < 66)
                            {
                                enemies[i].animation_frame = 4;
                            }
                            else if (game_timer % 4 == 0)
                            {
                                enemies[i].animation_frame++;
                                enemies[i].animation_frame %= 8;
                            }
                        }
                    }
                    else
                    {
                        if (strcmp(enemies[i].rb.cb.tag, "bat") == 0)
                            enemies[i].animation_frame = 3;
                        else if (strcmp(enemies[i].rb.cb.tag, "spike") != 0)
                            enemies[i].animation_frame = 0;
                    }
                }

                for (int i = 0; i < object_count; i++)
                {
                    if (objects[i].sprite_frame >= 4 && objects[i].sprite_frame <= 7)
                    {
                        if (game_timer % 4 == 0)
                        {
                            objects[i].sprite_frame++;
                            objects[i].sprite_frame %= 4;
                            objects[i].sprite_frame += 4;
                        }
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
                    if (player_animation_counter % 4 == 0)
                    {
                        player.animation_frame++;
                        player.animation_frame %= 8;
                    }
                }

                if (player.animation_frame >= 11 && player.animation_frame <= 16)
                {
                    if (player_animation_counter % 2 == 1)
                    {
                        player.animation_frame++;

                        if (player.animation_frame > 16)
                        {
                            player.animation_frame = 8;
                            player.attacking = 0;
                            player.sword_rb.cb.enabled = 0;
                        }
                    }
                }

                if (player.animation_frame >= 17 && player.animation_frame <= 21)
                {
                    if (player_animation_counter % 2 == 0)
                    {
                        player.animation_frame++;

                        if (player.animation_frame > 21)
                        {
                            player.animation_frame = 8;
                            player.bow_attack = 0;
                        }
                    }
                }

                for (int i2 = 0; i2 < ground_count; i2++)
                {
                    if (strcmp(grounds[i2].rb.cb.tag, "lava") == 0)
                    {
                        if (grounds[i2].animation_frame >= 0 && grounds[i2].animation_frame <= 3)
                        {
                            if (game_timer % 4 == 0)
                            {
                                grounds[i2].animation_frame++;
                                grounds[i2].animation_frame %= 4;
                            }
                        }
                    }
                }

                counter--;
            }

            //DRAWING
            masked_blit(montain_sprite, buffer, camera.x * 0.1f, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            masked_blit(ground_background_sprite, buffer, camera.x * 0.4f, camera.y - 128, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

            for (int i = 0; i < ground_count; i++)
            {
                if (strcmp(grounds[i].rb.cb.tag, "platform") == 0)
                {
                    if (grounds[i].rb.pos.x + 128 >= camera.x && grounds[i].rb.pos.x <= camera.x + SCREEN_WIDTH)
                    {
                        if (grounds[i].rb.pos.y + 128 >= camera.y && grounds[i].rb.pos.y <= camera.y + SCREEN_HEIGHT)
                        {
                            draw_platform(buffer, platform_sprite, &grounds[i], camera);
                        }
                    }
                }
            }

            for (int i = 0; i < object_count; i++)
            {
                if (objects[i].sprite_frame >= 4 && objects[i].sprite_frame <= 7)
                {
                    if (objects[i].position.x + 128 >= camera.x && objects[i].position.x <= camera.x + SCREEN_WIDTH)
                    {
                        if (objects[i].position.y + 128 >= camera.y && objects[i].position.y <= camera.y + SCREEN_HEIGHT)
                        {
                            draw_object(buffer, scenario_sprite, &objects[i], camera);
                        }
                    }
                }
            }
            masked_blit(level_background, buffer, camera.x, camera.y, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

            for (int i = 0; i < ground_count; i++)
            {
                if (strcmp(grounds[i].rb.cb.tag, "lava") == 0)
                {
                    if (grounds[i].rb.pos.x + 128 >= camera.x && grounds[i].rb.pos.x <= camera.x + SCREEN_WIDTH)
                    {
                        if (grounds[i].rb.pos.y + 128 >= camera.y && grounds[i].rb.pos.y <= camera.y + SCREEN_HEIGHT)
                        {
                            draw_lava(buffer, lava_sprite, &grounds[i], camera);
                        }
                    }
                }
            }

            for (int i = 0; i < item_count; i++)
            {
                if (strcmp(items[i].rb.cb.tag, "potion") == 0)
                {
                    if (items[i].rb.pos.x + 128 >= camera.x && items[i].rb.pos.x <= camera.x + SCREEN_WIDTH)
                    {
                        if (items[i].rb.pos.y + 128 >= camera.y && items[i].rb.pos.y <= camera.y + SCREEN_HEIGHT)
                        {
                            draw_potion(buffer, potion_sprite, &items[i], camera);
                        }
                    }
                }
            }

            draw_player(buffer, player_sprite, &player, camera);

            for (int i = 0; i < enemy_count; i++)
            {
                if (strcmp(enemies[i].rb.cb.tag, "bat") == 0 && enemies[i].rb.pos.y <= 1000)
                {
                    if (enemies[i].rb.pos.x + 128 >= camera.x && enemies[i].rb.pos.x <= camera.x + SCREEN_WIDTH)
                    {
                        if (enemies[i].rb.pos.y + 128 >= camera.y && enemies[i].rb.pos.y <= camera.y + SCREEN_HEIGHT)
                        {
                            draw_bat(buffer, bat_sprite, &enemies[i], camera);
                        }
                    }
                    if (enemies[i].alive == 0 && enemies[i].rb.pos.y >= 1000)
                        enemies[i].rb.pos.y = 1001;
                }
                else if (strcmp(enemies[i].rb.cb.tag, "fox") == 0 && enemies[i].rb.pos.y <= 1000)
                {
                    if (enemies[i].rb.pos.x + 128 >= camera.x && enemies[i].rb.pos.x <= camera.x + SCREEN_WIDTH)
                    {
                        if (enemies[i].rb.pos.y + 128 >= camera.y && enemies[i].rb.pos.y <= camera.y + SCREEN_HEIGHT)
                        {
                            draw_fox(buffer, fox_sprite, &enemies[i], camera);
                        }
                    }
                    if (enemies[i].alive == 0 && enemies[i].rb.pos.y >= 1000)
                        enemies[i].rb.pos.y = 1001;
                }
                else if (strcmp(enemies[i].rb.cb.tag, "harpy") == 0 && enemies[i].rb.pos.y <= 1000)
                {
                    if (enemies[i].rb.pos.x + 128 >= camera.x && enemies[i].rb.pos.x <= camera.x + SCREEN_WIDTH)
                    {
                        if (enemies[i].rb.pos.y + 128 >= camera.y && enemies[i].rb.pos.y <= camera.y + SCREEN_HEIGHT)
                        {
                            draw_harpy(buffer, harpy_sprite, &enemies[i], camera);
                        }
                    }
                    if (enemies[i].alive == 0 && enemies[i].rb.pos.y >= 1000)
                        enemies[i].rb.pos.y = 1001;
                }
                else if (strcmp(enemies[i].rb.cb.tag, "ghost") == 0 && enemies[i].rb.pos.y <= 1000)
                {
                    if (enemies[i].rb.pos.x + 128 >= camera.x && enemies[i].rb.pos.x <= camera.x + SCREEN_WIDTH)
                    {
                        if (enemies[i].rb.pos.y + 128 >= camera.y && enemies[i].rb.pos.y <= camera.y + SCREEN_HEIGHT)
                        {
                            draw_ghost(buffer, ghost_sprite, &enemies[i], camera);
                        }
                    }
                    if (enemies[i].alive == 0 && enemies[i].rb.pos.y >= 1000)
                        enemies[i].rb.pos.y = 1001;
                }
                else if (strcmp(enemies[i].rb.cb.tag, "spike") == 0)
                {
                    if (enemies[i].rb.pos.x + 128 >= camera.x && enemies[i].rb.pos.x <= camera.x + SCREEN_WIDTH)
                    {
                        if (enemies[i].rb.pos.y + 128 >= camera.y && enemies[i].rb.pos.y <= camera.y + SCREEN_HEIGHT)
                        {
                            draw_spike(buffer, spike_sprite, &enemies[i], camera);
                        }
                    }
                }
            }

            for (int i = 0; i < ground_count; i++)
            {
                if (strcmp(grounds[i].rb.cb.tag, "bridge") == 0)
                {
                    if (grounds[i].rb.pos.x + 128 >= camera.x && grounds[i].rb.pos.x <= camera.x + SCREEN_WIDTH)
                    {
                        if (grounds[i].rb.pos.y + 128 >= camera.y && grounds[i].rb.pos.y <= camera.y + SCREEN_HEIGHT)
                        {
                            draw_bridge(buffer, bridge_sprite, &grounds[i], camera);
                        }
                    }
                }
            }

            draw_lifebar(buffer, lifebar_sprite, player);

            draw_sprite(screen, buffer, 0, 0);
            clear_to_color(buffer, 0x40AEBF);
        }

        free(map);
        free(scenario_map);
        destroy_bitmap(level_background);

        for (int i = 0; i < rbs_size; i++)
        {
            destroy_list(rbs[i]->collidingWith);
        }
#pragma endregion

#pragma region death screen
        //VARIABLES
        int shx = 290;
        int shy = 417;
        int snd = 0;

        //BITMAPS
        BITMAP *death = load_bitmap(DEATHSCREEN_PATH, NULL);

        //SAMPLES
        SAMPLE *sound_death = load_sample(DEATH_SOUND);

        //DEATH SAMPLE
        play_sample(sound_death, 255, 128, 1000, 1);

        animation_frame = 0;

        while (death_on)
        {
            keyboard_input();

            //INPUT
            if (key_down(KEY_RIGHT) || key_down(KEY_LEFT) || key_down(KEY_DOWN) || key_down(KEY_UP))
            {
                snd = 1;
            }

            if (key_down(KEY_ENTER) || key_down(KEY_ESC))
            {
                death_on = 0;
                menu_on = 1;
                break;
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
                masked_blit(arrow_sprite, buffer, r_img_pos, c_img_pos, shx, shy, 32, 32);

                if (snd)
                {
                    play_sample(select, 255, 128, 1000, 0);
                    snd = 0;
                }

                draw_sprite(screen, buffer, 0, 0);
                clear(buffer);
                draw_sprite(buffer, death, 0, 0);

                counter--;
            }
        }

        destroy_bitmap(death);
        destroy_bitmap(arrow);
        destroy_sample(select);
        destroy_sample(sound_death);
#pragma endregion
    }

    destroy_bitmap(buffer);
    destroy_bitmap(lifebar_sprite);
    destroy_bitmap(lava_sprite);
    destroy_bitmap(player_sprite);
    destroy_bitmap(harpy_sprite);
    destroy_bitmap(ghost_sprite);
    destroy_bitmap(bat_sprite);
    destroy_bitmap(fox_sprite);
    destroy_bitmap(ground_sprite);
    destroy_bitmap(platform_sprite);
    destroy_bitmap(bridge_sprite);
    destroy_bitmap(spike_sprite);
    destroy_bitmap(scenario_sprite);
    destroy_bitmap(potion_sprite);
    destroy_bitmap(montain_sprite);
    destroy_bitmap(ground_background_sprite);

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
    else if (player->rb.velocity.x == 0 && player->attacking == 0 && player->bow_attack == 0)
    {
        player->animation_frame = 8;
    }
    else if (player->rb.velocity.x == 0 && player->attacking != 0 && player->bow_attack == 0)
    {
        if (player->animation_frame < 11)
        {
            player->animation_frame = 11;
        }

        if (player->animation_frame < 16)
        {
            player->attacking = 1;
            if (player->animation_frame >= 15)
                player->sword_rb.cb.enabled = 1;
        }
    }
    else if (player->rb.velocity.x == 0 && player->attacking == 0 && player->bow_attack != 0)
    {
        if (player->animation_frame < 17)
        {
            player->animation_frame = 17;
        }
    }

    if (!player->can_jump || player->rb.velocity.y != 0)
    {
        if (player->attacking && !player->bow_attack)
        {
            if (player->animation_frame < 11)
            {
                player->animation_frame = 11;
            }
            if (player->animation_frame < 17)
            {
                player->attacking = 1;
                if (player->animation_frame >= 16)
                {
                    player->sword_rb.cb.enabled = 1;
                }
            }
        }
        else if (!player->attacking && player->bow_attack)
        {
            if (player->animation_frame < 17)
            {
                player->animation_frame = 17;
            }
        }
        else if (!player->attacking && !player->bow_attack)
        {
            player->animation_frame = 10;
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
                draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - floor(camera.x), player->rb.pos.y - floor(camera.y), DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - floor(camera.x), player->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
            }
        }
        else
        {
            draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - floor(camera.x), player->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
        }
    }
    else
    {
        if (player->invulnerability == 1 && player->life > 0)
        {
            if (game_timer % 4 == 0)
            {
                draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - floor(camera.x), player->rb.pos.y - floor(camera.y), DRAW_SPRITE_TRANS, DRAW_SPRITE_H_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - floor(camera.x), player->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
            }
        }
        else
        {
            draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - floor(camera.x), player->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
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
            draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - floor(camera.x), bat->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
        }
        else
        {
            if (game_timer % 2 == 0)
            {
                draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - floor(camera.x), bat->rb.pos.y - floor(camera.y), DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - floor(camera.x), bat->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
            }
        }
    }
    else
    {
        if (bat->taking_damage == 0 || bat->alive == 0)
        {
            draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - floor(camera.x), bat->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
        }
        else
        {
            if (game_timer % 2 == 0)
            {
                draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - floor(camera.x), bat->rb.pos.y - floor(camera.y), DRAW_SPRITE_TRANS, DRAW_SPRITE_H_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, bat_sprite, bat->rb.pos.x - floor(camera.x), bat->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
            }
        }
    }

    destroy_bitmap(bat_sprite);
}

void draw_fox(BITMAP *bmp, BITMAP *sprite, Enemy *fox, Vector camera)
{
    BITMAP *fox_sprite = create_bitmap(96, 96);
    clear_to_color(fox_sprite, makecol(255, 0, 255));

    //rect(bmp, fox->rb.cb.min.x - floor(camera.x), fox->rb.cb.min.y - floor(camera.y), fox->rb.cb.max.x - floor(camera.x), fox->rb.cb.max.y - floor(camera.y), makecol(255,0,0));

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
            draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - floor(camera.x), fox->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
        }
        else
        {
            if (game_timer % 2 == 0)
            {
                draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - floor(camera.x), fox->rb.pos.y - floor(camera.y), DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - floor(camera.x), fox->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
            }
        }
    }
    else
    {
        if (fox->taking_damage == 0 || fox->alive == 0)
        {
            draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - floor(camera.x), fox->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
        }
        else
        {
            if (game_timer % 2 == 0)
            {
                draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - floor(camera.x), fox->rb.pos.y - floor(camera.y), DRAW_SPRITE_TRANS, DRAW_SPRITE_H_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, fox_sprite, fox->rb.pos.x - floor(camera.x), fox->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
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
            draw_sprite_ex(bmp, harpy_sprite, harpy->rb.pos.x - floor(camera.x), harpy->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
        }
        else
        {
            if (game_timer % 2 == 0)
            {
                draw_sprite_ex(bmp, harpy_sprite, harpy->rb.pos.x - floor(camera.x), harpy->rb.pos.y - floor(camera.y), DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, harpy_sprite, harpy->rb.pos.x - floor(camera.x), harpy->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
            }
        }
    }
    else
    {
        if (harpy->taking_damage == 0 || harpy->alive == 0)
        {
            draw_sprite_ex(bmp, harpy_sprite, harpy->rb.pos.x - floor(camera.x), harpy->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
        }
        else
        {
            if (game_timer % 2 == 0)
            {
                draw_sprite_ex(bmp, harpy_sprite, harpy->rb.pos.x - floor(camera.x), harpy->rb.pos.y - floor(camera.y), DRAW_SPRITE_TRANS, DRAW_SPRITE_H_FLIP);
            }
            else
            {
                draw_sprite_ex(bmp, harpy_sprite, harpy->rb.pos.x - floor(camera.x), harpy->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
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
            draw_sprite_ex(bmp, ghost_sprite, ghost->rb.pos.x - floor(camera.x), ghost->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
        }
        else
        {
            draw_sprite_ex(bmp, ghost_sprite, ghost->rb.pos.x - floor(camera.x), ghost->rb.pos.y - floor(camera.y), DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
        }
    }
    else
    {
        if (ghost->attack == 1)
        {
            draw_sprite_ex(bmp, ghost_sprite, ghost->rb.pos.x - floor(camera.x), ghost->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
        }
        else
        {
            draw_sprite_ex(bmp, ghost_sprite, ghost->rb.pos.x - floor(camera.x), ghost->rb.pos.y - floor(camera.y), DRAW_SPRITE_TRANS, DRAW_SPRITE_H_FLIP);
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

    draw_sprite_ex(bmp, ground_sprite, ground->rb.pos.x - floor(camera.x), ground->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);

    destroy_bitmap(ground_sprite);
}

void draw_platform(BITMAP *bmp, BITMAP *sprite, Ground *platform, Vector camera)
{
    BITMAP *platform_sprite = create_bitmap(128, 128);
    clear_to_color(platform_sprite, makecol(255, 0, 255));

    int r_img_pos = platform->animation_frame % BAT_SPRITE_COLS;
    int c_img_pos = platform->animation_frame / BAT_SPRITE_COLS;

    r_img_pos *= BAT_TILE_SIZE;
    c_img_pos *= BAT_TILE_SIZE;

    //draw the a part of the sprite sheet to the screen and scales it
    masked_stretch_blit(sprite, platform_sprite, r_img_pos, c_img_pos, 32, 32, 0, 0, 128, 128);

    draw_sprite_ex(bmp, platform_sprite, platform->rb.pos.x - floor(camera.x), platform->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);

    destroy_bitmap(platform_sprite);
}

void draw_lava(BITMAP *bmp, BITMAP *sprite, Ground *lava, Vector camera)
{
    BITMAP *lava_sprite = create_bitmap(128, 128);
    clear_to_color(lava_sprite, makecol(255, 0, 255));

    int r_img_pos = lava->animation_frame % LAVA_SPRITE_COLS;
    int c_img_pos = lava->animation_frame / LAVA_SPRITE_COLS;

    r_img_pos *= LAVA_TILE_SIZE;
    c_img_pos *= LAVA_TILE_SIZE;

    //draw the a part of the sprite sheet to the screen and scales it
    masked_stretch_blit(sprite, lava_sprite, r_img_pos, c_img_pos, 32, 32, 0, 0, 128, 128);

    draw_sprite_ex(bmp, lava_sprite, lava->rb.pos.x - floor(camera.x), lava->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);

    destroy_bitmap(lava_sprite);
}

void draw_bridge(BITMAP *bmp, BITMAP *sprite, Ground *bridge, Vector camera)
{
    BITMAP *bridge_sprite = create_bitmap(128, 128);
    clear_to_color(bridge_sprite, makecol(255, 0, 255));

    int r_img_pos = bridge->animation_frame % LAVA_SPRITE_COLS;
    int c_img_pos = bridge->animation_frame / LAVA_SPRITE_COLS;

    r_img_pos *= LAVA_TILE_SIZE;
    c_img_pos *= LAVA_TILE_SIZE;

    //draw the a part of the sprite sheet to the screen and scales it
    masked_stretch_blit(sprite, bridge_sprite, r_img_pos, c_img_pos, 32, 32, 0, 0, 128, 128);

    draw_sprite_ex(bmp, bridge_sprite, bridge->rb.pos.x - floor(camera.x), bridge->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);

    destroy_bitmap(bridge_sprite);
}

void draw_spike(BITMAP *bmp, BITMAP *sprite, Enemy *spike, Vector camera)
{
    BITMAP *spike_sprite = create_bitmap(128, 128);
    clear_to_color(spike_sprite, makecol(255, 0, 255));

    int r_img_pos = spike->animation_frame % SPIKE_SPRITE_COLS;
    int c_img_pos = spike->animation_frame / SPIKE_SPRITE_COLS;

    r_img_pos *= SPIKE_TILE_SIZE;
    c_img_pos *= SPIKE_TILE_SIZE;

    //draw the a part of the sprite sheet to the screen and scales it
    masked_stretch_blit(sprite, spike_sprite, r_img_pos, c_img_pos, 32, 32, 0, 0, 128, 128);

    draw_sprite_ex(bmp, spike_sprite, spike->rb.pos.x - floor(camera.x), spike->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);

    destroy_bitmap(spike_sprite);
}

void draw_object(BITMAP *bmp, BITMAP *sprite, Object *scenario, Vector camera)
{
    BITMAP *scenario_sprite = create_bitmap(256, 256);
    clear_to_color(scenario_sprite, makecol(255, 0, 255));

    int r_img_pos = scenario->sprite_frame % SCENARIO_SPRITE_COLS;
    int c_img_pos = scenario->sprite_frame / SCENARIO_SPRITE_COLS;

    r_img_pos *= SCENARIO_TILE_SIZE;
    c_img_pos *= SCENARIO_TILE_SIZE;

    //draw the a part of the sprite sheet to the screen and scales it
    if (scenario->sprite_frame == 0 || scenario->sprite_frame == 1 || scenario->sprite_frame == 16 || scenario->sprite_frame == 17)
        masked_stretch_blit(sprite, scenario_sprite, r_img_pos, c_img_pos, 64, 64, 0, 0, 256, 256);
    else
        masked_stretch_blit(sprite, scenario_sprite, r_img_pos, c_img_pos, 64, 64, 0, 0, 128, 128);

    if (scenario->sprite_frame >= 0 && scenario->sprite_frame <= 1)
    {
        draw_sprite_ex(bmp, scenario_sprite, scenario->position.x - floor(camera.x), scenario->position.y - 100 - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
    }
    else if (scenario->sprite_frame >= 2 && scenario->sprite_frame <= 3 || scenario->sprite_frame >= 18 && scenario->sprite_frame <= 21)
    {
        draw_sprite_ex(bmp, scenario_sprite, scenario->position.x - floor(camera.x), scenario->position.y + 28 - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
    }
    else if (scenario->sprite_frame >= 16 && scenario->sprite_frame <= 17)
    {
        draw_sprite_ex(bmp, scenario_sprite, scenario->position.x - floor(camera.x), scenario->position.y - 72 - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
    }
    else
    {
        draw_sprite_ex(bmp, scenario_sprite, scenario->position.x - floor(camera.x), scenario->position.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
    }

    destroy_bitmap(scenario_sprite);
}

void draw_potion(BITMAP *bmp, BITMAP *sprite, Item *potion, Vector camera)
{
    if (potion->rb.cb.enabled)
    {
        BITMAP *potion_sprite = create_bitmap(64, 64);
        clear_to_color(potion_sprite, makecol(255, 0, 255));

        int r_img_pos = potion->animation_frame % POTION_SPRITE_COLS;
        int c_img_pos = potion->animation_frame / POTION_SPRITE_COLS;

        r_img_pos *= POTION_TILE_SIZE;
        c_img_pos *= POTION_TILE_SIZE;

        //draw the a part of the sprite sheet to the screen and scales it
        masked_stretch_blit(sprite, potion_sprite, r_img_pos, c_img_pos, 32, 32, 0, 0, 64, 64);

        draw_sprite_ex(bmp, potion_sprite, potion->rb.pos.x - floor(camera.x), potion->rb.pos.y - floor(camera.y), DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);

        destroy_bitmap(potion_sprite);
    }
}

void draw_lifebar(BITMAP *bmp, BITMAP *sprite, Player player)
{
    char player_life[4];
    itoa(player.life, player_life, 10);
    strcat(player_life, "%");
    rectfill(bmp, 73, 34, 73 + floor(122 * player.life / 100.0f), 49, makecol(255, 0, 0));
    draw_sprite(bmp, sprite, 10, 10);
    textout_ex(bmp, font, player_life, 64 + 55, 38, makecol(255, 255, 0), -1);
}