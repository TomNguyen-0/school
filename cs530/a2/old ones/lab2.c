#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "header.h"

void parseOC(char* thisLine);

int main(int argc, char **argv) {
    FILE *ptr_file;
    char line[256];

    // Checking command line arguments and storing
    // the file in ptr_file
   if (argc > 1) {
        if (argc > 2) {
            printf("Too many args!");
        } else {
            ptr_file = fopen(argv[1],"r");
        }

        // Checks to see if the file is empty
        // if it isn't send it to the parser
        // take a line and put it in the parser
        if (ptr_file != NULL) {
            if (argc > 2) {
                printf("yep.");
            } else {
                while (!feof(ptr_file)) {
                    fgets (line, sizeof line, ptr_file);
                    parseOC(line);
                }
            }
        }
    }
    fclose(ptr_file);
    return 0;
}


void parseOC(char* thisLine) {
     if (thisLine[0] == 'H') {
         printf("this is a header record!\n");
         printf("%s", thisLine);
         // write header function to parse into
         // Name, Start address, and Length of program
     }
     if (thisLine[0] == 'T') {
         printf("this is a text record!\n");
         printf("%s", thisLine);
         // write text record function to parse into
         // Starting Address, Length of record, instructions/directives?
     }
     if (thisLine[0] == 'M') {
         printf("this is a modification record!\n");
         printf("%s", thisLine);
         // write modification record function to parse into
         // starting address to change, size in half bytes
     }
     if (thisLine[0] == 'E') {
         printf("this is an end record!\n");
         printf("%s", thisLine);
         // write end function to parse last address of program
     }
}