#include <allegro.h>
#include <stdio.h>
#include "../headers/constants.h"
#include "../headers/rigidbody.h"
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

void draw_ball(BITMAP *bmp, RigidBody rb);

int main()
{
    allegro_init();
    install_keyboard();
    install_timer();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 600, 400, 0, 0);

    LOCK_VARIABLE(close_game);
    LOCK_FUNCTION(close_program);

    LOCK_VARIABLE(counter);
    LOCK_FUNCTION(increment);

    install_int_ex(increment, MSEC_TO_TIMER(1.0 / FPS * 1000));

    RigidBody ball;
    ball.gravity_scale = 0.1f;
    ball.acceleration = create_vector(0, 0);
    ball.velocity = create_vector(0, -10);
    ball.pos = create_vector(SCREEN_W / 2, SCREEN_H / 2);
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);

    while (!close_game)
    {
        keyboard_input();

        //USER INPUT
        if (key_down(KEY_ESC))
        {
            close_program();
        }
        if (key_down(KEY_W))
        {
            ball.velocity.y += -10;
        }

        //UPDATE
        while (counter > 0)
        {
            update_limit_pos(&ball, create_vector(0, 0), create_vector(SCREEN_W, SCREEN_H));
            counter--;
        }

        //DRAWING
        draw_ball(buffer, ball);

        draw_sprite(screen, buffer, 0, 0);
        clear(buffer);
    }
    return 0;
}
END_OF_MAIN();

void draw_ball(BITMAP *bmp, RigidBody rb)
{
    circlefill(bmp, rb.pos.x, rb.pos.y, 10, makecol(255, 0, 0));
}