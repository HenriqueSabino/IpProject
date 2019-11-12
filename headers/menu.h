#ifndef MENU_H
#define MENU_H

#define LOGO_PATH "../assets/Menu/logo.bmp"
#define ARROW_PATH "../assets/Menu/seta-direita.bmp"
#define DEATHSCREEN_PATH "../assets/Menu/deathscreen.bmp"

#define INTRO_SOUND "../sounds/intro.wav"
#define SELECT_SOUND "../sounds/select.wav"
#define ENTER_SOUND "../sounds/buble.wav"
#define DEATH_SOUND "../sounds/Deathscreen.wav"

int menu(int timer);
void deathscreen();

#endif // !"MENU_H"