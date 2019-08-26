#include <allegro.h>

volatile int close_game = FALSE;
void close_program()
{
    close_game = TRUE;
}
END_OF_FUNCTION(close_program)

int main()
{
    allegro_init();
    install_keyboard();
    install_timer();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1366, 768, 0, 0);

    LOCK_VARIABLE(close_game);
    LOCK_FUNCTION(close_program);

    while (!close_game)
    {
        if (key[KEY_ESC])
        {
            close_program();
        }

        textout_centre_ex(screen, font, "Initial code", SCREEN_W / 2, SCREEN_H / 2, makecol(255, 255, 254), -1);
    }
    return 0;
}
END_OF_MAIN();