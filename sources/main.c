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

    printf("%i", screen->w);

    LOCK_VARIABLE(close_game);
    LOCK_FUNCTION(close_program);
    set_close_button_callback(close_program);

    LOCK_VARIABLE(counter);
    LOCK_FUNCTION(increment);

    install_int_ex(increment, MSEC_TO_TIMER(1.0 / FPS * 1000));

    Player player;
    init_player(&player);
    player.rb.pos = create_vector(SCREEN_W / 2, 0);

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
        if (key_down(KEY_A))
        {
            set_velocity_axis(&player, "horizontal", -5);
        }
        if (key_down(KEY_D))
        {
            set_velocity_axis(&player, "horizontal", 5);
        }

        //UPDATE
        while (counter > 0)
        {
            update_player(&player);
            counter--;
        }

        //DRAWING
        draw_player(buffer, player_sprite, player);
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