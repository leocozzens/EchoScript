// C standard headers
#include <stdio.h>
#include <stdlib.h>
// Local headers
#include <str.h>

#define ARG_FAIL    "Incorrect number of arguments"
#define DEMO_USAGE  "./%s [PRIMARY_EXECUTABLE]"
#define FMT_SIZE    2

int main(int argc, char **argv) {
    if(argc != 2) {
        printf(ARG_FAIL "\n" DEMO_USAGE "\n", argv[0] == NULL ? "demo" : argv[0]);
        return 1;
    }
    char *strings[] = {
        argv[1],
        " test 123"
    };

    char *buffer = str_combine(2, strings);
    for(int i = 0; i < 5; i++) {
        system(buffer);
    }

    return 0;
}