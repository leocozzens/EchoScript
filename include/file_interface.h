#ifndef FILE_INTERFACE_H
#define FILE_INTERFACE_H

// C Standard Libraries
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Local headers
#include <structs.h>

void clear_input(void);
char *get_input(char *request, char *retStr, int buffSize);
FileData *get_file(char *fileName);
void close_file(FileData **file);
void write_text(char *fileName, FileData *writeFile);

#endif