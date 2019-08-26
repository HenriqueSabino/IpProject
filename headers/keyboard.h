#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <allegro.h>

int p_keys[KEY_MAX];
void keyboard_input();
int key_down(int key);
int key_up(int key);
int key_holding(int key);

#endif