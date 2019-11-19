#ifndef SCENEGENERATION_H
#define SCENEGENERATION_H

#include <stdio.h>
#include "vector.h"

#define SCENARIO "..\\assets\\Scenario\\Scenario.bmp"

typedef struct object
{
    Vector position;
    int sprite_frame;
} Object;

void init_object(Object *object, Vector pos, int sprite_frame);

//Reads a file and puts the characters to an char array
//returns the size of that array

int n_rows, n_cols;

int readMap(char **map, char *path);

#endif // !_SCENEGENERATION_H