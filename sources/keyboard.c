#include "../headers/keyboard.h"

void keyboard_input()
{
    for (int i = 0; i < KEY_MAX; i++)
    {
        p_keys[i] = key[i];
    }

    poll_keyboard();
}

int key_down(int _key)
{
    return !p_keys[_key] && key[_key];
}
int key_up(int _key)
{
    return p_keys[_key] && !key[_key];
}
int key_holding(int _key)
{
    return p_keys[_key] && key[_key];
}