#include <allegro.h>
#include <stdio.h>
#include "../headers/constants.h"
#include "../headers/player.h"
#include "../headers/keyboard.h"

volatile int close_game = FALSE;
void close_program()
{
    close_game = TRUE;
}
END_OF_FUNCTION(close_program)

volatile int counter = 0;
void increment()
{
    counter++;
}
END_OF_FUNCTION(increment)

void draw_player(BITMAP *bmp, BITMAP *sprite, Player player);

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

    LOCK_VARIABLE(counter);
    LOCK_FUNCTION(increment);

    install_int_ex(increment, MSEC_TO_TIMER(1.0 / FPS * 1000));

    Player player;
    init_player(&player);
    player.rb.pos = create_vector(SCREEN_W / 2, 0);

    RigidBody ground;
    ground.gravity_scale = 0;
    ground.velocity = create_vector(0, 0);
    ground.acceleration = create_vector(0, 0);
    ground.pos = create_vector(60, SCREEN_H / 2);
    ground.cb.width = 500;
    ground.cb.height = 20;
    ground.cb.min = create_vector(60, SCREEN_H / 2);
    ground.cb.max = create_vector(ground.cb.min.x + ground.cb.width, ground.cb.min.y + ground.cb.height);
    ground.cb.tag = "ground";
    ground.cb.solid = 0;

    RigidBody wall;
    wall.gravity_scale = 0;
    wall.velocity = create_vector(0, 0);
    wall.acceleration = create_vector(0, 0);
    wall.pos = create_vector(SCREEN_W / 2, SCREEN_H / 2 - 20);
    wall.cb.width = 20;
    wall.cb.height = 20;
    wall.cb.min = create_vector(SCREEN_W / 2, SCREEN_H / 2 - 20);
    wall.cb.max = create_vector(wall.cb.min.x + wall.cb.width, wall.cb.min.y + wall.cb.height);
    wall.cb.tag = "wall";
    wall.cb.solid = 0;

    RigidBody *rbs[] = {&player.rb, &ground, &wall};

    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP *player_sprite = load_bitmap(PLAYER_SPRITE_SHEET, NULL);
    if (player_sprite == NULL)
        allegro_message("error");

    while (!close_game)
    {
        keyboard_input();

        //USER INPUT
        if (key_down(KEY_ESC))
        {
            close_program();
        }
        if (key_down(KEY_W) || key_down(KEY_SPACE))
        {
            set_velocity_axis(&player, "vertical", -10);
        }
        if (key_holding(KEY_A) || key_holding(KEY_D))
        {
            if (key_holding(KEY_A))
            {
                set_velocity_axis(&player, "horizontal", -5);
            }
            else
            {
                set_velocity_axis(&player, "horizontal", 5);
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
            counter--;
        }

        //DRAWING
        draw_player(buffer, player_sprite, player);

        rect(buffer, player.rb.cb.min.x, player.rb.cb.min.y, player.rb.cb.max.x, player.rb.cb.max.y, makecol(255, 0, 0));
        rectfill(buffer, ground.cb.min.x, ground.cb.min.y, ground.cb.max.x, ground.cb.max.y, makecol(255, 0, 0));
        rectfill(buffer, wall.cb.min.x, wall.cb.min.y, wall.cb.max.x, wall.cb.max.y, makecol(255, 0, 0));
        draw_sprite(screen, buffer, 0, 0);
        clear(buffer);
    }

    destroy_bitmap(buffer);
    destroy_bitmap(player_sprite);

    return 0;
}
END_OF_MAIN();

void draw_player(BITMAP *bmp, BITMAP *sprite, Player player)
{
    //draw the a part of the sprite sheet to the screen and scales it
    masked_stretch_blit(sprite, bmp, 0, 0, 50, 50, player.rb.pos.x, player.rb.pos.y, 100, 100);
}