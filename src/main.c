#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parse_pipe.h>

#define NAME_SIZE 255

int main() {
    printf("\nPlease enter the file you'd like to translate: ");
    char fileName[NAME_SIZE];
    fgets(fileName, sizeof(fileName), stdin);
    fileName[strlen(fileName) - 1] = '\0';

    // Set file pointer
    FILE *pF = NULL;
    pF = fopen(fileName, "r");
    if(pF == NULL) {
        printf("Failed to open file...\n");
        return 1;
    }

    fseek(pF, 0, SEEK_END); // Sets the file position indicator to the last element in the contiguous block
    int fSize = ftell(pF); // ftell returns the offset of the position indicator from the initial address
    rewind(pF); // Returns the position pointer to base

    char *buffer = malloc(fSize + 1); // +1 for null terminator
    if(buffer == NULL) {
        fclose(pF);
        return 1;
    }

    // Read the file contents into the buffer
    fread(buffer, sizeof(char), fSize, pF);
    buffer[fSize + 1] = '\0';

    //printf("file contents:\n%s\n", buffer);

    Token *output = lexFile(buffer, fSize);
    if(output == NULL) return 0;
    printf("And the value is:%s\n", output->args);
    free(output->args);
    free(output);

    fclose(pF);
    return 0;
}