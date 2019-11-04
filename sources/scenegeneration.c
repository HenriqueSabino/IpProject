#include <stdio.h>
#include "../headers/scenegeneration.h"

void readMap(int l, int c, char map[l][c], FILE *mapPointer, char *path)
{
    mapPointer = fopen(path, "r");
    
    if ( mapPointer == NULL )
    {
        printf("Map file faild to open.\n");
    }
    else
    {
        printf("The file is now opened.\n");

        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < c; j++)
            {
                map[i][j] = '*';
            }
        }

        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < c; j++)
            {
                char c;
                c = fgetc(mapPointer);

                while (c == '\n')
                {
                    c = fgetc(mapPointer);
                }
                
                map[i][j] = c;

            }
        }

        fclose(mapPointer);
    }
}