#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
void nixbpeFunction(char * characters, int location, int nixbpeIndex); //Figure out the nixbpe values and store it.
void notation(int nIndex,char* opcode,char* symtab); //Figures out the format that should be printed out
bool ImmediateAddressing(int nIndex); //checks the nixbpe array for n=1 && i=1
bool indirect(int nIndex); //looks for n=1 && i=0
bool simple(int nIndex); // looks for (n=0&&i=0) or (n=1&&i=1)
bool direct(int nIndex); // looks for (b=0&&p=0)
bool pc_relative(int nIndex); //looks for (b=0&&p=1)
bool base(int nIndex); // looks for (b=1&&p=0)
bool BASEloader(int nIndex, char* symtab);//checks if base is being using and outputs BASE.

char* hexToBinary(char* hexText);

void transform(char* recordLine);
char* getBitArray(int destinationIndex, char* origin, int originIndex, int endIndex);
char* getLengthArray(int destinationIndex, char* origin, int originIndex, int endIndex);
char* getOpcodeBitArray(int destinationIndex, char* origin, int originIndex, int endIndex);
char* convertBitsToString(char* bits);
char* searchForOperation(int arrayToSearch, int arrayIndex, const char* opcode);
int searchForOpcode(const char *opcode);

char startingAddress[24]; //array to hold bits of address of the first instruction on the line
char lengthOfRecord[8]; //array to hold bits of length of record
char opcodeBits[7]; //bit array to hold opcode
char bitString[6]; //opcode to string
char opcodeName[24];
int format; //format of opcode

char opcodesF1[6][7];
char mnemonicF1[6][4];
char opcodesF2[11][7];
char mnemonicF2[11][4];
char opcodesF34[42][7];
char mnemonicF34[42][4];

char binaryBits[512];
char hexConversion[512];

int numElementsInArray;
int nixbpe[6][512];
int mnemnixbpe; // need this to be passed to nixbpe notation in order to retrieve the op string
bool baseLoader;


int main(int argc, char **argv) {
    FILE *ptr_file;
    char line[256];
    baseLoader = false;

    // Format 1
    strcpy(opcodesF1[0], "110001");
    strcpy(mnemonicF1[0], "FIX");
    strcpy(opcodesF1[1], "110000");
    strcpy(mnemonicF1[1], "FLOAT");
    strcpy(opcodesF1[2], "111101");
    strcpy(mnemonicF1[2], "HIO");
    strcpy(opcodesF1[3], "110010");
    strcpy(mnemonicF1[3], "NORM");
    strcpy(opcodesF1[4], "111100");
    strcpy(mnemonicF1[4], "SIO");
    strcpy(opcodesF1[5], "111110");
    strcpy(mnemonicF1[5], "TIO");

    // Format 2
    strcpy(opcodesF2[0], "100100");
    strcpy(mnemonicF2[0], "ADDR");
    strcpy(opcodesF2[1], "101101");
    strcpy(mnemonicF2[1], "CLEAR");
    strcpy(opcodesF2[2], "101000");
    strcpy(mnemonicF2[2], "COMPR");
    strcpy(opcodesF2[3], "100111");
    strcpy(mnemonicF2[3], "DIVR");
    strcpy(opcodesF2[4], "100110");
    strcpy(mnemonicF2[4], "MULR");
    strcpy(opcodesF2[5], "101011");
    strcpy(mnemonicF2[5], "RMO");
    strcpy(opcodesF2[6], "101001");
    strcpy(mnemonicF2[6], "SHIFTL");
    strcpy(opcodesF2[7], "101010");
    strcpy(mnemonicF2[7], "SHIFTR");
    strcpy(opcodesF2[8], "100101");
    strcpy(mnemonicF2[8], "SUBR");
    strcpy(opcodesF2[9], "101100");
    strcpy(mnemonicF2[9], "SVC");
    strcpy(opcodesF2[10], "101110");
    strcpy(mnemonicF2[10], "TIXR");

    // Format 3/4
    strcpy(opcodesF34[0], "000110");
    strcpy(mnemonicF34[0], "ADD");
    strcpy(opcodesF34[1], "010110");
    strcpy(mnemonicF34[1], "ADDF");
    strcpy(opcodesF34[2], "010000");
    strcpy(mnemonicF34[2], "AND");
    strcpy(opcodesF34[3], "001010");
    strcpy(mnemonicF34[3], "COMP");
    strcpy(opcodesF34[4], "100010");
    strcpy(mnemonicF34[4], "COMPF");
    strcpy(opcodesF34[5], "001001");
    strcpy(mnemonicF34[5], "DIV");
    strcpy(opcodesF34[6], "011001");
    strcpy(mnemonicF34[6], "DIVF");
    strcpy(opcodesF34[7], "001111");
    strcpy(mnemonicF34[7], "J");
    strcpy(opcodesF34[8], "001100");
    strcpy(mnemonicF34[8], "JEQ");
    strcpy(opcodesF34[9], "001101");
    strcpy(mnemonicF34[9], "JGT");
    strcpy(opcodesF34[10], "001110");
    strcpy(mnemonicF34[10], "JLT");
    strcpy(opcodesF34[11], "010010");
    strcpy(mnemonicF34[11], "JSUB");
    strcpy(opcodesF34[12], "000000");
    strcpy(mnemonicF34[12], "LDA");
    strcpy(opcodesF34[13], "011010");
    strcpy(mnemonicF34[13], "LDB");
    strcpy(opcodesF34[14], "010100");
    strcpy(mnemonicF34[14], "LDCH");
    strcpy(opcodesF34[15], "011100");
    strcpy(mnemonicF34[15], "LDF");
    strcpy(opcodesF34[16], "000010");
    strcpy(mnemonicF34[16], "LDL");
    strcpy(opcodesF34[17], "011011");
    strcpy(mnemonicF34[17], "LDS");
    strcpy(opcodesF34[18], "011101");
    strcpy(mnemonicF34[18], "LDT");
    strcpy(opcodesF34[19], "000001");
    strcpy(mnemonicF34[19], "LDX");
    strcpy(opcodesF34[20], "110100");
    strcpy(mnemonicF34[20], "LPS");
    strcpy(opcodesF34[21], "001000");
    strcpy(mnemonicF34[21], "MUL");
    strcpy(opcodesF34[22], "011000");
    strcpy(mnemonicF34[22], "MULF");
    strcpy(opcodesF34[23], "010001");
    strcpy(mnemonicF34[23], "OR");
    strcpy(opcodesF34[24], "110110");
    strcpy(mnemonicF34[24], "RD");
    strcpy(opcodesF34[25], "010011");
    strcpy(mnemonicF34[25], "RSUB");
    strcpy(opcodesF34[26], "111011");
    strcpy(mnemonicF34[26], "SSK");
    strcpy(opcodesF34[27], "000011");
    strcpy(mnemonicF34[27], "STA");
    strcpy(opcodesF34[28], "011110");
    strcpy(mnemonicF34[28], "STB");
    strcpy(opcodesF34[29], "010101");
    strcpy(mnemonicF34[29], "STCH");
    strcpy(opcodesF34[30], "100000");
    strcpy(mnemonicF34[30], "STF");
    strcpy(opcodesF34[31], "110101");
    strcpy(mnemonicF34[31], "STI");
    strcpy(opcodesF34[32], "000101");
    strcpy(mnemonicF34[32], "STL");
    strcpy(opcodesF34[33], "011111");
    strcpy(mnemonicF34[33], "STS");
    strcpy(opcodesF34[34], "111010");
    strcpy(mnemonicF34[34], "STSW");
    strcpy(opcodesF34[35], "100001");
    strcpy(mnemonicF34[35], "STT");
    strcpy(opcodesF34[36], "000100");
    strcpy(mnemonicF34[36], "STX");
    strcpy(opcodesF34[37], "000111");
    strcpy(mnemonicF34[37], "SUB");
    strcpy(opcodesF34[38], "010111");
    strcpy(mnemonicF34[38], "SUBF");
    strcpy(opcodesF34[39], "111000");
    strcpy(mnemonicF34[39], "TD");
    strcpy(opcodesF34[40], "001011");
    strcpy(mnemonicF34[40], "TIX");
    strcpy(opcodesF34[41], "110111");
    strcpy(mnemonicF34[41], "WD");

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
    int i;
    for (i=1; i<7; i++){
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
    int i;
	for (i = 1; i < 7; i++) {
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

    // Splits the bits on 4 and prints, just to see hex values visually.
    // for (int i = 0; i < numElementsInArray; i++) {
    // 	if (i % 4 == 0) {
    // 		printf("\n");
    // 	}
    // 	printf("%d", binaryBits[i]-48);
    // }
    // printf("\n");

    transform(binaryBits);

    // printf("%s\n", binaryBits);
    // printf("%d\n", numElementsInArray);

}

void parseEnd(char* endRecord) {
    char addressFirstInstruction[12];
    int i;
    for (i = 1; i < 7; i++) {
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
    return binaryBits;
}

void transform(char* recordLine) {
    int index; //index tracks the location of first unchecked bit in the array recordLine
    int end; //index to track the end of next section to examine

    int arrayIndex; //int to hold the index of an array being used
    int nixbpeIndex; // int to hold the index of array for nixbpe
    
    /*
        Get Starting Address
    */
    arrayIndex = 0;
    index = 0;
    end = 24;
    nixbpeIndex=0;
    getBitArray(arrayIndex, recordLine, index, end);
    printf("Starting Address (Binary): %s\n", startingAddress);

    // convert binary to hex
    char *SA = startingAddress;
    char *checker = SA;
    int startingAddressInHex = 0;
    do {
        int value = *checker == '1'?1:0;
        startingAddressInHex = (startingAddressInHex<<1)|value;
        checker++;
    } while (*checker);
    printf("Starting Address (Hex): %04x\n", startingAddressInHex);

    /*
        Get length of Instructions in Text Record
    */
    arrayIndex = 0;
    index = end;
    end = 32;
    getLengthArray(arrayIndex, recordLine, index, end);
    printf("Record Length (Binary) %s\n", lengthOfRecord);

    /*
        Go through instructions in Text Record
    */
    arrayIndex = 0;
    index = end;
    end = index + 6;

    // convert binary to decimal
    char *LOR = lengthOfRecord;
    char *temp_check = LOR;
    int lengthInDecimal = 0;
    do {
        int val = *temp_check == '1'?1:0;
        lengthInDecimal = (lengthInDecimal<<1)|val;
        temp_check++;
    } while (*temp_check);
    lengthInDecimal *= 8; // Because each byte is 8 bits
    printf("Record Length (Decimal in Bits) %d\n", lengthInDecimal);

    /*
        Loop through all instructions until end of Text Record
    */
    while (index < lengthInDecimal+32) {
        getOpcodeBitArray(arrayIndex, recordLine, index, end); // gives 6 opcodebits
        printf("Opcode Bits %s\n", opcodeBits);

        
        convertBitsToString(opcodeBits);
        printf("Opcode String %s\n", bitString);

        /*
            Defined inside of transform because then we either have to make the opcodes/mnemonics
            global or pass all of them into the function.
        */
        
        nixbpeFunction(recordLine, index+6,nixbpeIndex);
        

         
        format = searchForOpcode(bitString);
        
       notation(nixbpeIndex, searchForOperation(format,mnemnixbpe , bitString),"symtab"); //I need to be passed the opcode here. and symtab*********************************
       // char* searchForOperation(int arrayToSearch, int arrayIndex, const char* opcode)
        
        printf("The Format: %d\n", format);

        index += 24;
        end += 24;
        arrayIndex = 0;
        nixbpeIndex++;
    }
}

char* getBitArray(int destinationIndex, char* origin, int originIndex, int endIndex) {
    for (originIndex; originIndex < endIndex; originIndex++) {
        startingAddress[destinationIndex++] = origin[originIndex];
    }
    return startingAddress;
}

char* getLengthArray(int destinationIndex, char* origin, int originIndex, int endIndex) {
    for (originIndex; originIndex < endIndex; originIndex++) {
        lengthOfRecord[destinationIndex++] = origin[originIndex];
    }
    return lengthOfRecord;
}

char* getOpcodeBitArray(int destinationIndex, char* origin, int originIndex, int endIndex) {
    for (originIndex; originIndex < endIndex; originIndex++) {
        opcodeBits[destinationIndex++] = origin[originIndex];
    }
    opcodeBits[6] = '\0';
    return opcodeBits;
}

char* convertBitsToString(char* bits) {
    int i;
    for (i = 0; i < 6; i++) {
        bitString[i] = bits[i];
    }
    return bitString;
}

char* searchForOperation(int arrayToSearch, int arrayIndex, const char* opcode) {
    if (arrayToSearch == 1) {
        strcpy(opcodeName, mnemonicF1[arrayIndex]);
        return opcodeName;
    }
    if (arrayToSearch == 2) {
        strcpy(opcodeName, mnemonicF2[arrayIndex]);
        return opcodeName;
    }
    if (arrayToSearch == 34) {
        strcpy(opcodeName, mnemonicF34[arrayIndex]);
        return opcodeName;
    }
}

int searchForOpcode(const char *opcode) {
    int instructionFormat = -1; //if -1 is returned then instruction isn't in appendix A
    int i;
    for (i = 0; i < 6; i++) {
        if (strcmp(opcodesF1[i], opcode) == 0) {
            instructionFormat = 1;
            searchForOperation(instructionFormat, i, opcode);
            mnemnixbpe = i; // need this to be passed to nixbpe notation in order to retrieve the op string
            return instructionFormat;
        }
    }

    for (i = 0; i <11; i++) {
        if (strcmp(opcodesF2[i], opcode) == 0) {
            instructionFormat = 2;
            searchForOperation(instructionFormat, i, opcode);
            mnemnixbpe = i; // need this to be passed to nixbpe notation in order to retrieve the op string            
            return instructionFormat;
        }
    }

    for (i = 0; i < 42; i++) {
        if (strcmp(opcodesF34[i], opcode) == 0) {
            instructionFormat = 34;
            searchForOperation(instructionFormat, i, opcode);
            mnemnixbpe = i; // need this to be passed to nixbpe notation in order to retrieve the op string
            return instructionFormat;
        }
    }
    return instructionFormat;
}

void nixbpeFunction (char* characters,  int location, int nixbpeIndex){//checks each character from given location for nixbpe
   int j,initialized;
   for(initialized=0; initialized<6; initialized++){
    nixbpe[initialized][nixbpeIndex]=0;
   }
    for( j=0; j<6; j++){
      if(nixbpe[j][nixbpeIndex]==0){// location of n
         if(characters[location]=='1')
            nixbpe[j][nixbpeIndex]=1;
      }
      if(nixbpe[j][nixbpeIndex]==1){// location of i
         if(characters[location]=='1')
            nixbpe[j][nixbpeIndex]=1;
      }
      if(nixbpe[j][nixbpeIndex]==2){// location of x
         if(characters[location]=='1')
            nixbpe[j][nixbpeIndex]=1;
      }
      if(nixbpe[j][nixbpeIndex]==3){// location of b
         if(characters[location]=='1')
            nixbpe[j][nixbpeIndex]=1;
      }
      if(nixbpe[j][nixbpeIndex]==4){// location of p
         if(characters[location]=='1')
            nixbpe[j][nixbpeIndex]=1;
      }
      if(nixbpe[j][nixbpeIndex]==5){// location of e
         if(characters[location]=='1')
            nixbpe[j][nixbpeIndex]=1;
      }
      location++;
      
      
   }
   //for debugging
   printf("n=%d i=%d x=%d b=%d p=%d e=%d\n",nixbpe[0][nixbpeIndex],nixbpe[1][nixbpeIndex],nixbpe[2][nixbpeIndex],nixbpe[3][nixbpeIndex],nixbpe[4][nixbpeIndex],nixbpe[5][nixbpeIndex]);
  
}


void notation(int nIndex,char* opcode,char* symtab){//from book page 499. Having a hard time calculating target address.
   int error=0;
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){//simple addressing type
      //printf("%s c\n",opcode); //c (is for constant) will be disp
      printf("%s %s\n",opcode,symtab);
      error=1;
   }
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==1){
      //printf("+%s m\n",opcode);// m will be addr format 4 instruction
      printf("+%s %s\n",opcode,symtab);
      error=1;
   }
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==1 && nixbpe[5][nIndex]==0){
      //printf("%s m\n",opcode); // (pc)+disp
      printf("%s %s\n",opcode,symtab);
      error=1;
   }
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==1 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){
      //printf("%s m\n",opcode); // (b) + disp
      printf("%s %s\n",opcode,symtab);
      error=1;
   }
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==1 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){
      //printf("%s c,X\n",opcode); //disp + (X)
      printf("%s %s,X\n",opcode,symtab);
      error=1;
   }
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==1 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==1){
      //printf("+%s m,X\n",opcode); //addr+(X) format 4 instruction
      printf("+%s %s,X\n",opcode,symtab);
      error=1;
   }   
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==1 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==1 && nixbpe[5][nIndex]==0){
      //printf("%s m,X\n",opcode); // (PC)+disp+(X)
      printf("%s %s,X\n",opcode,symtab);
      error=1;
   }   
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==1 && nixbpe[3][nIndex]==1 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){
      //printf("%s m,X\n",opcode);// (B)+disp+(X)
      printf("%s %s,X\n",opcode,symtab);
      error=1;
   }   
   if(nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]==0 && nixbpe[2][nIndex]==0){
      //printf("%s m\n",opcode); // b/p/e/disp
      printf("%s %s\n",opcode,symtab);
      error=1;
   }   
   if(nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]==0 && nixbpe[2][nIndex]==1){//simple addressing type stops
      //printf("%s m,X\n",opcode); // b/p/e/disp+(X)
      printf("%s %s,X\n",opcode,symtab);
      error=1;
   }   
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==0 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){//indirect addressing type
      //printf("%s @c\n",opcode); // disp
      printf("%s @%s\n",opcode,symtab);
      error=1;
   }   
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==0 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==1){
      //printf("+%s @m\n",opcode); // addr
      printf("+%s @%s\n",opcode,symtab);
      error=1;
   }   
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==0 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==1 && nixbpe[5][nIndex]==0){
      //printf("%s @m\n",opcode); // (PC) + disp
      printf("%s @%s\n",opcode,symtab);
      error=1;
   }   
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==0 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==1 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){//indirect addresing ends
      //printf("%s @m\n",opcode); // (B) + disp
      printf("%s @%s\n",opcode,symtab);
      error=1;
   }   
   if(nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){//immediate types
      //printf("%s #c\n",opcode);// disp
      printf("%s #%s\n",opcode,symtab);
      error=1;
   }   
   if(nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==1){
      //printf("+%s #m\n",opcode); //addr
      printf("+%s #%s\n",opcode,symtab);
      error=1;
   }   
   if(nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==1 && nixbpe[5][nIndex]==0){
      //printf("%s #m\n",opcode); //(PC)+disp
      printf("%s #%s\n",opcode,symtab);
      error=1;
   }   
   if(nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==1 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){//immediate type ends
      //printf("%s #m\n",opcode); // (B)+disp
      printf("%s #%s\n",opcode,symtab); 
      error=1;
   }   
   if(error==0)//something went wrong
    printf("Error\n");// do not know what to print here.
}

bool ImmediateAddressing(int nIndex){ //checks for immediate addressing for format 3 and 4
   if (nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]==1)//if(n==0 && i==1)
      return true;
   return false;
}

bool indirect(int nIndex){ //checks for indirect addressing for format 3 and 4
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==0)//   if(n==1 && i==0)
      return true;
  return false;
}

bool simple(int nIndex){ //check for simple addressing for format 3 and 4
   if(nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]== 0)//if(n==0 && i==0)
      return true;
   if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1)//if(n==1 && i==1)
      return true;
   return false;
}

bool direct(int nIndex){ //check for direct addressing for format 3 only. format 4 will always use direct addressing.
   if(nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0)//if(b==0 && p==0)
      return true;
   return false;
}

bool pc_relative(int nIndex){ //check for pc-relative addressing for format 3 only
   if(nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==1)//if(b==0 && p==1)
      return true;
   return false;
}

bool base(int nIndex){ //check for base addressing for format 3 only
   if(nixbpe[3][nIndex]==1 && nixbpe[0][nIndex]==0 )//if(b==1 && p==0)
      return true;
   return false;
}

bool BASEloader(int nIndex, char* symtab){ //everytime we use LDB c outputs BASE.
//    if(base(nIndex) == true)
//       if(baseLoader == false){
//          printf("BASE %s\n",symtab);
//          baseLoader =true;
//          return true;
//       }
//    if(base (nIndex)==false){
//       baseLoader =false;
//       return false;
//    }
//    return true;
}

bool LTORG(){//every time we use a lit tab variable print out LTORG
   printf("
}

bool ORG(){//every time we use a constant or a predefine variable we print ORG
}
printf("%8s%8s %s",labels, opcode, symtab);