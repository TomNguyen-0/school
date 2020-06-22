#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "header.h"

/*
    DEFINE ALL FUNCTIONS AND GLOBALS HERE.
*/
void parseOC(char* thisLine);
void parseModification(char* modLine, char** test);
void parseHeader(char* headerRecord);
void parseText(char* textRecord);
void parseEnd(char* endRecord);
void getOperation(char** binaryBits, char** mnemonic, char** opCode);
char* hexToBinary(char* hexText);
char binaryBits[512];
char* mnemonic[256];
char* opCode[512];
int numElementsInArray;

int main(int argc, char **argv) {
    FILE *ptr_file;
    char line[256];

    mnemonic[0] = "ADD";
    opCode[0] = "0"; opCode[1] = "0"; opCode[2] = "0"; opCode[3] = "1";
    opCode[4] = "1"; opCode[5] = "0"; opCode[6] = "0"; opCode[7] = "0";
	// mnemonic[1] = "ADDF";

	// mnemonic[2] = "ADDR";

	// mnemonic[3] = "AND";

	// mnemonic[4] = "CLEAR";

	// mnemonic[5] = "COMP";

	// mnemonic[6] = "COMPF";

	// mnemonic[7] = "COMPR";

	// mnemonic[8] = "DIV";

	// mnemonic[9] = "DIVF";

	// mnemonic[10] = "DIVR";

    // Checking command line arguments and storing
    // the file in ptr_file
    ptr_file = fopen(argv[2], "test.txt");
                    while (!feof(ptr_file)) {
                    fgets (line, sizeof line, ptr_file);
                    parseOC(line);
                }
    
    /*
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
    */
    fclose(ptr_file);
    return 0;
}


void parseOC(char* thisLine) {
    char** test = malloc(8 * sizeof(char*));
     if (thisLine[0] == 'H') {
        printf("this is a header record!\n");
        printf("%s", thisLine);
        parseHeader(thisLine);
     }
     if (thisLine[0] == 'T') {
        printf("this is a text record!\n");
        printf("%s", thisLine);
        parseText(thisLine);
     }
     if (thisLine[0] == 'M') {
        printf("this is a modification record!\n");
        printf("%s", thisLine);
        parseModification(thisLine, test);
     }
     if (thisLine[0] == 'E') {
        printf("this is an end record!\n");
        printf("%s\n", thisLine);
        parseEnd(thisLine);
     }
}


void parseModification(char* modLine, char** test) {
    char modAdd[8]; // Address of where to modify
    char modSize[3]; // How many half-bytes to modify

    for (int i=1; i<7; i++){
        modAdd[i-1] = modLine[i];
    }
    modSize[0] = modLine[7];
    modSize[1] = modLine[8];
    modSize[2] = '\0';
    modAdd[7] = '\0';

    test[2] = modAdd;
    test[0] = modSize;
}

/*
    parses the Header Record
*/
void parseHeader(char* headerRecord) {
	char nameOfProgram[12];
    char startingAddress[12];
    char lengthOfProgram[12];
	for (int i = 1; i < 7; i++) {
		nameOfProgram[i-1] = headerRecord[i];
        startingAddress[i-1] = headerRecord[i+6];
        lengthOfProgram[i-1] = headerRecord[i+12];
	}
	nameOfProgram[7] = '\0';
    startingAddress[7] = '\0';
    lengthOfProgram[7] = '\0';
    /*
        Need to print vars to output file.
    */
    printf("Parsed %s\nParsed %s\nParsed %s\n", nameOfProgram, startingAddress, lengthOfProgram);
}

void parseText(char* textRecord) {
    hexToBinary(textRecord);
    // getOperation(binaryBits, mnemonic, opCode);

    // Splits the bits on 4 and prints, just to see hex values visually.
    for (int i = 0; i < numElementsInArray; i++) {
    	if (i % 4 == 0) {
    		printf("\n");
    	}
    	printf("%d", binaryBits[i]-48);
    }
    printf("\n");
    
    // printf("%s\n", binaryBits);
    // printf("%d\n", numElementsInArray);

}

void parseEnd(char* endRecord) {
    char addressFirstInstruction[12];
    for (int i = 1; i < 7; i++) {
        addressFirstInstruction[i-1] = endRecord[i];
    }
    addressFirstInstruction[7] = '\0';
    /*
        print to output file.
    */
    printf("Parsed %s\n", addressFirstInstruction);
}

/*
	Populates binaryBits with individual bits of each hex digit.
	Example:
		E becomes 1110, and is stored in the array as 
		['1', '1', '1', '0']
		at indices 0, 1, 2, 3 respectively.
*/
char* hexToBinary(char* hexText) {
    int i = 0;
    int j = 0;
    numElementsInArray = 0;
    while(hexText[i]) {
        switch(hexText[i]) {
            case '0':
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	break;
            case '1':
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	break;
            case '2':
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	break;
            case '3':
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	break;
            case '4':
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	break;
            case '5':
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	break;
            case '6':
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	break;
            case '7':
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	break;
            case '8':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	break;
            case '9':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	break;
            case 'A':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	break;
            case 'B':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	break;
            case 'C':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	break;
            case 'D':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	break;
            case 'E':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	break;
            case 'F':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	break;
            case 'a':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	break;
            case 'b':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	break;
            case 'c':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	break;
            case 'd':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	break;
            case 'e':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '0';
            	j++;
            	numElementsInArray++;
            	break;
            case 'f':
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	binaryBits[j] = '1';
            	j++;
            	numElementsInArray++;
            	break;
        }
        i++;
    }
    printf(binaryBits);
    return binaryBits;
}

void getOperation(char** binaryBits, char** mnemonic, char** opCode) {
	int index = 0;

	index++;
}