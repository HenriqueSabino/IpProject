#include <allegro.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../headers/constants.h"
#include "../headers/player.h"
#include "../headers/enemy.h"
#include "../headers/keyboard.h"
#include "../headers/list.h"

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

void draw_bat(BITMAP *bmp, BITMAP *sprite, Enemy* bat, Vector camera);

int main()
{
    allegro_init();
    install_keyboard();
    install_timer();
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 600, 400, 0, 0);

    LOCK_VARIABLE(close_game);
    LOCK_FUNCTION(close_program);
    set_close_button_callback(close_program);

    LOCK_VARIABLE(game_timer);
    LOCK_VARIABLE(counter);
    LOCK_FUNCTION(increment);

    install_int_ex(increment, MSEC_TO_TIMER(1.0 / FPS * 1000));

    Vector camera;

    Player player;
    init_player(&player);
    player.rb.pos = create_vector(SCREEN_W / 2, 0);

    Enemy bat;
    init_enemy(&bat);
    bat.rb.pos = create_vector(50, 50);

    camera = player.rb.pos;
    camera.x -= 100;
    camera.y -= 200;

    RigidBody ground;
    ground.gravity_scale = 0;
    ground.velocity = create_vector(0, 0);
    ground.acceleration = create_vector(0, 0);
    ground.pos = create_vector(60, SCREEN_H / 2);
    ground.cb.width = 500;
    ground.cb.height = 20;
    ground.cb.offset = create_vector(0, 0);
    ground.cb.min = create_vector(60, SCREEN_H / 2);
    ground.cb.max = create_vector(ground.cb.min.x + ground.cb.width, ground.cb.min.y + ground.cb.height);
    strcpy(ground.cb.tag, "ground");
    ground.cb.solid = 0;
    ground.collidingWith = createList();
    ground.onCollisionEnter = NULL;
    ground.onCollisionExit = NULL;
    ground.onCollisionStay = NULL;

    RigidBody wall;
    wall.gravity_scale = 0;
    wall.velocity = create_vector(0, 0);
    wall.acceleration = create_vector(0, 0);
    wall.pos = create_vector(SCREEN_W / 2, SCREEN_H / 2 - 20);
    wall.cb.width = 20;
    wall.cb.height = 20;
    wall.cb.offset = create_vector(0, 0);
    wall.cb.min = create_vector(SCREEN_W / 2, SCREEN_H / 2 - 20);
    wall.cb.max = create_vector(wall.cb.min.x + wall.cb.width, wall.cb.min.y + wall.cb.height);
    strcpy(wall.cb.tag, "ground");
    wall.cb.solid = 0;
    wall.collidingWith = createList();
    wall.onCollisionEnter = NULL;
    wall.onCollisionExit = NULL;
    wall.onCollisionStay = NULL;

    RigidBody *rbs[] = {&player.rb, &ground, &wall};

    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP *player_sprite = load_bitmap(PLAYER_SPRITE_SHEET, NULL);
    if (player_sprite == NULL)
        allegro_message("error");
    
    BITMAP *bat_sprite = load_bitmap(BAT, NULL);
    if (bat_sprite == NULL)
        allegro_message("error");

    while (!close_game)
    {
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
                set_velocity_axis(&player, "vertical", -10);
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

        //UPDATE
        while (counter > 0)
        {
            //update_player(&player);
            update_all(rbs, 3);

            //linear interpolation between camera and player's position
            camera.x = 0.9f * camera.x + 0.1f * (player.rb.pos.x - 100);
            camera.y = 0.9f * camera.y + 0.1f * (player.rb.pos.y - 200);

            if (player.animation_frame >= 0 && player.animation_frame <= 7)
            {
                if (game_timer % 4 == 0)
                {
                    player.animation_frame++;
                    player.animation_frame %= 8;
                }
            }
            if(bat.animation_frame >= 0 && bat.animation_frame <=3)
            {
                if (game_timer % 4 == 0)
                {
                    bat.animation_frame++;
                    bat.animation_frame %= 4;
                }
            }

            counter--;
        }

        //DRAWING
        draw_player(buffer, player_sprite, &player, camera);
        draw_bat(buffer, bat_sprite, &bat, camera);

        rect(buffer, player.rb.cb.min.x - camera.x, player.rb.cb.min.y - camera.y, player.rb.cb.max.x - camera.x, player.rb.cb.max.y - camera.y, makecol(255, 0, 0));
        rect(buffer, bat.rb.cb.min.x - camera.x, bat.rb.cb.min.y - camera.y, bat.rb.cb.max.x - camera.x, bat.rb.cb.max.y - camera.y, makecol(255, 0, 0));
        rectfill(buffer, ground.cb.min.x - camera.x, ground.cb.min.y - camera.y, ground.cb.max.x - camera.x, ground.cb.max.y - camera.y, makecol(255, 0, 0));
        rectfill(buffer, wall.cb.min.x - camera.x, wall.cb.min.y - camera.y, wall.cb.max.x - camera.x, wall.cb.max.y - camera.y, makecol(255, 0, 0));
        draw_sprite(screen, buffer, 0, 0);
        clear(buffer);
    }

    destroy_bitmap(buffer);
    destroy_bitmap(player_sprite);
    destroy_bitmap(bat_sprite);

    for (int i = 0; i < 3; i++)
    {
        destroy_list(rbs[i]->collidingWith);
    }

    return 0;
}
END_OF_MAIN();

void draw_player(BITMAP *bmp, BITMAP *sprite, Player *player, Vector camera)
{

    BITMAP *player_sprite = create_bitmap(128, 128);
    clear(player_sprite);

    if (abs(player->rb.velocity.x) > 0 && player->animation_frame > 7)
    {
        player->animation_frame = 0;
    }
    else if (player->rb.velocity.x == 0)
    {
        player->animation_frame = 8;
    }

    if (!player->can_jump || player->rb.velocity.y != 0)
    {
        player->animation_frame = 10;
    }

    int r_img_pos = player->animation_frame % PLAYER_SPRITE_COLS;
    int c_img_pos = player->animation_frame / PLAYER_SPRITE_COLS;

    r_img_pos *= PLAYER_TILE_SIZE + PLAYER_SPRITESHEET_OFFSET;
    c_img_pos *= PLAYER_TILE_SIZE + PLAYER_SPRITESHEET_OFFSET;

    //draw the a part of the sprite sheet to the screen and scales it
    masked_stretch_blit(sprite, player_sprite, r_img_pos, c_img_pos, 50, 50, 0, 0, 128, 128);

    if (player->facing_right)
    {
        draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - camera.x, player->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
    }
    else
    {
        draw_sprite_ex(bmp, player_sprite, player->rb.pos.x - camera.x, player->rb.pos.y - camera.y, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
    }

    destroy_bitmap(player_sprite);
}

void draw_bat(BITMAP *bmp, BITMAP *sprite, Enemy* bat, Vector camera)
{
    BITMAP *bat_sprite = create_bitmap(64, 64);
    clear(bat_sprite);

    int r_img_pos = bat->animation_frame % BAT_SPRITE_COLS;
    int c_img_pos = bat->animation_frame / BAT_SPRITE_COLS;

    r_img_pos *= BAT_TILE_SIZE + BAT_SPRITESHEET_OFFSET;
    c_img_pos *= BAT_TILE_SIZE + BAT_SPRITESHEET_OFFSET;

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