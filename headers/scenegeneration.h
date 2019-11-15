#ifndef SCENEGENERATION_H
#define SCENEGENERATION_H

#include <stdio.h>

//Reads a file and puts the characters to an char array
//returns the size of that array

int n_rows, n_cols;

int readMap(char **map, char *path);

#endif // !_SCENEGENERATION_H