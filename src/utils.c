// Standard C Libraries
#include <stdlib.h>

// Local headers
// Will need this package soon #include <structs.h>

char **dynamic_grid(int rows, int columns) {
    char **grid = NULL;
    grid = malloc(rows * (sizeof(char*))); // Allocate memory to the size of rows * char pointers

    if(grid == NULL) { // Error handling: Failed to allocate memory for grid.cells so return an empty grid
        grid = NULL;

        return grid;
    }

    for(int i = 0; i < rows; i++) {
        grid[i] = (char*) malloc(columns * (sizeof(char))); // Allocate each index of grid to a new set of columns * char size
    }
    return grid;
}

char **grid_add_rows(char **grid, int height, int width, int moreRows) {
    char **newGrid = realloc(grid, (sizeof(*grid) * (height + moreRows)));
    if(grid == NULL) return NULL;

    for(int i = 0; i < moreRows; i++) {
        newGrid[height + i] = (char*) malloc(width * (sizeof(**newGrid)));
        if(newGrid[height + i] == NULL) {
            for(int j = 0; j < i; j++) free(newGrid[j]);
            free(newGrid);
            return NULL;
        }
    }
    return newGrid;
}

int **grid_add_columns(int **grid, int height, int desiredWidth) {
    for(int i = 0; i < height; i++) {
        grid[i] = realloc(grid[i], sizeof(*grid[i]) * desiredWidth);
        if(grid[i] == NULL) {
            for(int j = 0; j < i; j++) free(grid[j]);
            free(grid);
            return NULL;
        }
    }
    return grid;
}

_Bool grid_free(char **target, int rows) { // Free's memory of 2D array on heap, also checks for error and will return true if any of the pointers memory addresses are undefined
    if(target == NULL) return 1;
    for(int i = 0; i < rows; i++) {
        if(target[i] != NULL) free(target[i]); // Loop through each index of the target array and free the row at each index denoted by its first block of memory
        else return 1;
    }
    free(target); // Now free the pointer to the first set pointer heap array
    return 0;
}