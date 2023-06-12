#ifndef UTILS_H
#define UTILS_H

// Standard C Libraries
#include <stdlib.h>

// Local headers
// Will need this package soon #include <structs.h>

char **dynamic_grid(int rows, int columns);
char **grid_add_rows(char **grid, int height, int width, int moreRows);
char **grid_add_columns(char **grid, int height, int desiredWidth);
_Bool grid_free(char **target, int rows);

#endif