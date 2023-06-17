// C Standard Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Local headers
#include <file_interface.h>
#include <utils.h>
#include <engine.h>

#define NAME_SIZE 255

int main(void) {
    char fileName[NAME_SIZE];
    get_input("\nPlease enter the file you'd like to translate: ", fileName, NAME_SIZE);

    FileData *input = get_file(fileName);

    FileData *output = render(input);
    close_file(&input);

    get_input("\nPlease enter the file destination: ", fileName, NAME_SIZE);

    write_text(fileName, output);

    close_file(&output);
    return 0;
}