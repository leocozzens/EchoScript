// C Standard Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Local headers
#include <file_interface.h>
#include <utils.h>
#include <engine.h>

#define NAME_SIZE 255
#define END_LINE '\n'

int main(void) {
    printf("\nPlease enter the file you'd like to translate: ");
    char fileName[NAME_SIZE];
    fgets(fileName, sizeof(fileName), stdin);
    char *endLine = strchr(fileName, END_LINE);
    if(endLine != NULL) *endLine = '\0';

    FileData *input = getFile(fileName);

    render(input->buffer, input->fSize);

    closeFile(&input);
    return 0;
}