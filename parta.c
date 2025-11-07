#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {

    // Check if user put in no arguments
    if (argc == 1) {
        printf("ERROR: No arguments\n");
        return 1;
    }

    //Loop over all arguments
    for (int i = 1; i < argc; i++) {
        const char* arg = argv[i];

        //convert each letter to uppercase
        size_t len = strlen(arg);
        for (size_t j = 0; j < len; j++) {
            putchar(toupper(arg[j])); 
        }
        // Put commas between arguments except for the last one
        if ( i < argc - 1) {
            putchar(',');
        }
    }
    putchar('\n');
    return 0;
}
