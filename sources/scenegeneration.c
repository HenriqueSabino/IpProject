#include <stdio.h>
#include <allegro.h>
#include "../headers/scenegeneration.h"

int readMap(char **map, char *path)
{
    FILE *mapPointer = fopen(path, "r");

    if (mapPointer == NULL)
    {
        allegro_message("ERROR!\nMap file faild to open.");
        return -1;
    }
    else
    {
        int rows, cols;
        fscanf(mapPointer, "%i\n", &rows);
        fscanf(mapPointer, "%i", &cols);

        /* creating two variables to hold the number of rows and columns so that one can 
        have access to them into the main function.*/
        n_rows = rows;
        n_cols = cols;

        char c = fgetc(mapPointer);
        while (c == '\n')
        {
            c = fgetc(mapPointer);
        }

        //creating an array the size of the map
        *map = (char *)malloc(sizeof(char) * rows * cols);

        for (int i = 0; i < rows * cols; i++)
        {
            (*map)[i] = c;
            c = fgetc(mapPointer);
        }

        fclose(mapPointer);

        return rows * cols;
    }
}

void init_object(Object *object, Vector pos, int sprite_frame)
{
    object->position = pos;
    object->sprite_frame = sprite_frame;
}