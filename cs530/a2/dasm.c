#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// #include "header.h"

/*
DEFINE ALL FUNCTIONS AND GLOBALS HERE.
*/
void parseOC(char* thisLine);
void parseSymTab(char* symLine);
void parseModification(char* modLine, char** test);
void parseHeader(char* headerRecord);
void parseText(char* textRecord);
void parseEnd(char* endRecord);
void getOperation(char** binaryBits, char** mnemonic, char** opCode);
void nixbpeFunction(char * characters, int location, int nixbpeIndex); //Figure out the nixbpe values and store it.
void notation(int nIndex, int dispIndex, char* recordLine) ; //Figures out the format that should be printed out

char* hexToBinary(char* hexText);


void transform(char* recordLine);
char* getBitArray(int destinationIndex, char* origin, int originIndex, int endIndex);
char* getLengthArray(int destinationIndex, char* origin, int originIndex, int endIndex);
char* getOpcodeBitArray(int destinationIndex, char* origin, int originIndex, int endIndex);
char* convertBitsToString(char* bits);
char* searchForOperation(int arrayToSearch, int arrayIndex, const char* opcode);
int searchForOpcode(const char *opcode);
void getDisp(int destinationIndex, char* origin, int originIndex, int endIndex);
void convertHexToBinaryArray(int destinationIndex, char* origin, int originIndex, int endIndex);
void RESW (char * currentAddress, char * nextAddress); //prints RESW
int convertHexToInt(char* hexToConvert);

char startingAddressForTextRecord[25]; //array to hold bits of address of the first instruction on the line
int programCounter; // array to hold starting address then increments for instructions
char *progptr;
char lengthOfRecord[9]; //array to hold bits of length of record
char opcodeBits[8]; //bit array to hold opcode
char bitString[7]; //opcode to string
char opcodeName[25];
char opcodeName2[25];
int format; //format of opcode
int z = 0;
int y = 0; //this variable is used for outprinting label in (strcmp(outputLabel,symbols[y])==0)
bool LTORG=false; //if lit tab was used set to true, default false.
char EOFlength[12]; //The address for End in string 002F04. Used to get the final result for RESW


char opcodesF1[7][8];
char mnemonicF1[7][5];
char opcodesF2[12][8];
char mnemonicF2[12][5];
char opcodesF34[43][8];
char mnemonicF34[43][5];

// data storage for symTab
char* symbols[20];
char* symValues[20];

// data storage for litTab
char* literals[20];
char* lengths[20];
char* literalAddresses[20];
int litTab = 0;
int litCounter = 0;

int symCounter = 0;
int symValCounter = 0;

char binaryBits[512];
char hexConversion[512];

int numElementsInArray;
int nixbpe[256][6];

char constValue[32];
char negCheck[32];
int symValueInts[30];
int literalAddressInts[30];
int displacement;
char symFlag[256]; //record the flag in the symtab so to be used in in RESW
int symValInt;
char operandValue[20];
char outputLabel[20];
char outputSymbol[20];
int symsUsedCounter = 0;
char plusExtension = (char) 0;
char commaX[3];

int baseFlag = 0;
int storeValue;
int baseValue;
int baseValueLogan;

int negFlag = 0;




int main(int argc, char **argv) {
    commaX[0] = '\0';
    FILE *ptr_file;
    FILE *symFile;
    char line[256];
    char line2[256];
    char fileName[256];

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

     argc=2;
     argv[1]="C:/Users/tom/Desktop/projects/cs530/a2/sample.obj";
   

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
                printf("Error inccorect number of arguments.");
            } else {
                strcpy(fileName, argv[1]);

                char *tok = strtok(fileName, ".");

                strcat(tok, ".sym");

                symFile = fopen(tok, "r");
                while (!feof(symFile)) {
                    fgets (line2, sizeof line2, symFile); // line2 is a line in the .sym file

                    z++;
                    if(z > 2) {
                        if(strstr(line2, "Name") != NULL) {
                            fgets (line2, sizeof line2, symFile);
                            fgets (line2, sizeof line2, symFile);

                            litTab = 1;
                        }
                        parseSymTab(line2);


                    }
                }

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
        parseHeader(thisLine);
    }
    if (thisLine[0] == 'T') {
        // printf("%s", thisLine);
        parseText(thisLine);
    }
    if (thisLine[0] == 'M') {
        parseModification(thisLine, test);
    }
    if (thisLine[0] == 'E') {
        parseEnd(thisLine);
    }
}


// Will take in a line from the SymTab and separate them
// into symbols and values
void parseSymTab(char* symLine) {
   char* symLineString = symLine;
   int findlength=0; //variable used for loops then is passed to sysflag.
//    for(findlength=0; ;findlength++){
// //            printf("symLine: %s\n",apples);
// //      printf("symLine: %c\n",apples[12]);
// //      printf("symLine size: %d\n", strlen apples);
//       
//    }
   while(symLineString[findlength++]!='\0');

    char *symbol = strtok(symLine, " ");

    char *symval = strtok(NULL, " ");
                                                    


    if(strstr(symbol, "\n") == NULL && litTab != 1){
        symbols[symCounter] = strdup(symbol);
        symFlag[symCounter] = symLineString[findlength-3];
        symCounter++;
        symValues[symValCounter] = strdup(symval);
        symValCounter++;
       

    } else if (strstr(symbol, "\n") != NULL) {
        litTab = 1;
    } else {
        if(symval != '\0') {
            char *literalAddress = strtok(NULL, " ");

            literals[litCounter] = strdup(symbol);
            lengths[litCounter] = strdup(symval);
            literalAddresses[litCounter] = strdup(literalAddress);

            litCounter++;
        }
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
    int j;
    for (j = 1; j < 7; j++) {
        nameOfProgram[j-1] = headerRecord[j];
        startingAddress[j-1] = headerRecord[j+6];
        lengthOfProgram[j-1] = headerRecord[j+12];
        EOFlength[j-1]=lengthOfProgram[j-1];
    }
    
    nameOfProgram[7] = '\0';
    startingAddress[7] = '\0';
    programCounter = strtol(startingAddress, &progptr, 10);
    lengthOfProgram[7] = '\0';
    printf("%s\tSTART\t%s\n", nameOfProgram, startingAddress);

    /*
    Need to print vars to output file.
    */
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
    int j;
    int t;
    for (i = 1; i < 7; i++) {
        addressFirstInstruction[i-1] = endRecord[i];
    }
    addressFirstInstruction[7] = '\0';
    /*
    print to output file.
    */
    char *TESTER = addressFirstInstruction;
    char *tcheck = TESTER;
    int cmpAddress = 0;
    char * position; //this is for the white space removal in the printout symbols[y]
    do {
        int valueA = *tcheck == '1'?1:0;
        cmpAddress = (cmpAddress<<1)|valueA;
        tcheck++;
    } while (*tcheck);
      for(y;y<symCounter;y++){
            position = symbols[y];
            j=0;

             while(position[j]!='\0')
                printf("%c",position[j++]);
               if(y<symCounter-1)
                RESW(symValues[y],symValues[y+1]);
             else
                RESW(symValues[y],EOFlength);

      }

    for (j=0; j<symCounter; j++){
        if (cmpAddress == symValueInts[j]) {
        
        	printf("\tEND\t%s\n", symbols[j]);
        	break;
        }
    }
}

/*
Populates binaryBits with individual bits of each hex digit.
Example:
E becomes 1110, and is stored in the array as
['1', '1', '1', '0']
at indices 0, 1, 2, 3 respectively.
*/


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
    // printf("Starting Address (Binary): %s\n", startingAddressForTextRecord);

    // convert binary to hex
    char *SA = startingAddressForTextRecord;
    char *checker = SA;
    int startingAddressInHex = 0;
    do {
        int value = *checker == '1'?1:0;
        startingAddressInHex = (startingAddressInHex<<1)|value;
        checker++;
    } while (*checker);
    // printf("Starting Address (Hex): %04x\n", startingAddressInHex);

    /*
    Get length of Instructions in Text Record
    */
    arrayIndex = 0;
    index = end;
    end = 32;
    getLengthArray(arrayIndex, recordLine, index, end);
    // printf("Record Length (Binary) %s\n", lengthOfRecord);

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
    // printf("Record Length (Decimal in Bits) %d\n", lengthInDecimal);

    /*
    Loop through all instructions until end of Text Record
    */
    while (index < lengthInDecimal+32) {
        getOpcodeBitArray(arrayIndex, recordLine, index, end); // gives 6 opcodebits


        convertBitsToString(opcodeBits);

        nixbpeFunction(recordLine, index+6, nixbpeIndex);
        notation(nixbpeIndex, index+12, recordLine);



        searchForOpcode(bitString);
        // printf("The Format: %d\n", format);
        if (format == 4) {
            index += 32;
            end += 32;
        } else {
            index += 24;
            end += 24;
        }


        programCounter += 3;
        // printf("TESTING in decimal: %d\n", programCounter);
        // printf("TESTING in hex: %x\n", programCounter);
        arrayIndex = 0;
        nixbpeIndex++;
    }
}

char* getBitArray(int destinationIndex, char* origin, int originIndex, int endIndex) {
    for (originIndex; originIndex < endIndex; originIndex++) {
        startingAddressForTextRecord[destinationIndex++] = origin[originIndex];
    }
    return startingAddressForTextRecord;
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
    int k;//a free variable used for loops/while
    if (arrayToSearch == 1) {
        strcpy(opcodeName, mnemonicF1[arrayIndex]);
        strcpy(opcodeName2, mnemonicF1[arrayIndex]);
        printf("%s\t%s\n", opcodeName, operandValue);
        outputLabel[0] = '\0';
        commaX[0] = '\0';
        return opcodeName;
    }
    if (arrayToSearch == 2) {
        strcpy(opcodeName, mnemonicF2[arrayIndex]);
        strcpy(opcodeName2, mnemonicF2[arrayIndex]);
        printf("%s\t%s\n", opcodeName, operandValue);
        outputLabel[0] = '\0';
        commaX[0] = '\0';
        return opcodeName;
    }
    if (arrayToSearch == 34) {
        strcpy(opcodeName, mnemonicF34[arrayIndex]);
        strcpy(opcodeName2, mnemonicF34[arrayIndex]);
        if (baseFlag == 1) {
            baseValue = storeValue;
            baseFlag = 0;
        }
        printf("%s\t%c%s\t%s%s\n", outputLabel, plusExtension, opcodeName, operandValue, commaX);
        
        if(LTORG )
         printf("\t\tLTORG\n ");
        if(strcmp(opcodeName, "LDB") == 0)
         if(operandValue[0]=='#'){
            printf("\tBASE\t");
            k=1;
            while(operandValue[k]!='\0'){
               printf("%c",operandValue[k++]);
            }
            printf("\n");
         }   
        else
         printf("\tBASE\t%s\n",operandValue);
         
          if(y <= symCounter)
             if(strcmp(outputLabel,symbols[y])==0)
                y++;
//                 char *apples;
//                 apples =lengthOfRecord;
//          printf("apples: %s\n", apples);      
         //for(strcmp(outputLabel,symbols[y])==0){
         //}
        // printf("hex to int: %d\n",convertHexToInt(symValues[yy++]));
     //   printf("programcounter: %d\n",programCounter);

     //   printf("symValues: %s\n",symValues[yy++]);
      //  printf("displacement: %d\n",displacement);
     //   printf("outputLabel: %s\n",outputLabel);
     //    printf("symbols: %s\n",symbols[0]);
        
         
        outputLabel[0] = '\0';
        plusExtension = (char) 0;
        commaX[0] = '\0';
        return opcodeName;
    }
}

void RESW (char * currentAddress,char * nextAddress){ //prints RESW
    int nSubtractC; //nAddress-cAddress
    int nAddress,cAddress; // the Decimal value for the string that was passed in.
    nAddress=convertHexToInt(nextAddress);
    cAddress=convertHexToInt(currentAddress);
    nSubtractC = nAddress-cAddress;
    if(nSubtractC<0)
      nSubtractC = cAddress-nAddress;
    if(symFlag[y]=='R'){
       if (nSubtractC %3==0)
           printf("\tRESW\t%d\n",nSubtractC/3);
       else
        printf("\tRESB\t%d\n",nSubtractC);
    }
    if(symFlag[y]=='A'){
      if(nSubtractC %3==0)
         printf("\tWORD\t%d\n",nSubtractC);
      else
         printf("\tBYTE\tX'%s'\n",currentAddress);
    }
       //  printf("",);
//    }
//    printf("nextAddress:%d\n",nextAddress);
//    printf("currentAddress:%d\n",currentAddress);
   
}

int searchForOpcode(const char *opcode) {
    int instructionFormat = -1; //if -1 is returned then instruction isn't in appendix A
    int i;
    for (i = 0; i < 6; i++) {
        if (strcmp(opcodesF1[i], opcode) == 0) {
            instructionFormat = 1;
            searchForOperation(instructionFormat, i, opcode);
            return instructionFormat;
        }
    }

    for (i = 0; i <11; i++) {
        if (strcmp(opcodesF2[i], opcode) == 0) {
            instructionFormat = 2;
            searchForOperation(instructionFormat, i, opcode);
            return instructionFormat;
        }
    }

    for (i = 0; i < 42; i++) {
        if (strcmp(opcodesF34[i], opcode) == 0) {
            instructionFormat = 34;
            searchForOperation(instructionFormat, i, opcode);
            return instructionFormat;
        }
    }
    return instructionFormat;
}

void nixbpeFunction (char* characters,  int location, int nixbpeIndex) {//checks each character from given location for nixbpe
    int j,initialized;
    for(initialized=0; initialized<6; initialized++) {
        nixbpe[initialized][nixbpeIndex]=0;
    }
    for( j=0; j<6; j++) {
        if(nixbpe[j][nixbpeIndex]==0) {// location of n
            if(characters[location]=='1')
            nixbpe[j][nixbpeIndex]=1;
        }
        if(nixbpe[j][nixbpeIndex]==1) {// location of i
            if(characters[location]=='1')
            nixbpe[j][nixbpeIndex]=1;
        }
        if(nixbpe[j][nixbpeIndex]==2) {// location of x
            if(characters[location]=='1')
            nixbpe[j][nixbpeIndex]=1;
        }
        if(nixbpe[j][nixbpeIndex]==3) {// location of b
            if(characters[location]=='1')
            nixbpe[j][nixbpeIndex]=1;
        }
        if(nixbpe[j][nixbpeIndex]==4) {// location of p
            if(characters[location]=='1')
            nixbpe[j][nixbpeIndex]=1;
        }
        if(nixbpe[j][nixbpeIndex]==5) {// location of e
            if(characters[location]=='1')
            nixbpe[j][nixbpeIndex]=1;
        }
        location++;
    }

    // printf("n=%d i=%d x=%d b=%d p=%d e=%d\n",nixbpe[0][nixbpeIndex],nixbpe[1][nixbpeIndex],nixbpe[2][nixbpeIndex],nixbpe[3][nixbpeIndex],nixbpe[4][nixbpeIndex],nixbpe[5][nixbpeIndex]);

}

void notation(int nIndex, int dispIndex, char* recordLine) {
    int error=0;
    int i;
    operandValue[0] = '\0';
    LTORG=false;

    for (i=0; i<symCounter; i++){
        symValueInts[i] = convertHexToInt(symValues[i]);
    }

    for (i=0; i<litCounter; i++){
        literalAddressInts[i] = convertHexToInt(literalAddresses[i]);
    }


    // 110000 op c
    if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        sprintf(operandValue+1,"%d",displacement);

        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                if (strcmp(opcodeName2, "LDB") == 0) {
                    baseValueLogan = symValueInts[i];
                    strncpy(operandValue, symbols[i], 10);
                } else if (strcmp(opcodeName2, "RSUB") == 0) {
                	strncpy(operandValue, symbols[i], 10);
                }
            }
        }

        error=1;
        format = 3;
    }
    // 110001 +op m
    if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==1){
        getDisp(0, recordLine, dispIndex+4, dispIndex+20);
        plusExtension = '+';
        sprintf(operandValue+1,"%d",displacement);
        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                strncpy(operandValue, symbols[i], 10);
                if (strcmp(opcodeName2, "LDB") == 0) {
                    baseValueLogan = symValueInts[i];
                    strncpy(operandValue, symbols[i], 10);
                } else if (strcmp(opcodeName2, "RSUB") == 0) {
                	strncpy(operandValue, symbols[i], 10);
                }
            }
        }
        error=1;
        format = 4;
        programCounter++;
    }
    // 110010 op m
    if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==1 && nixbpe[5][nIndex]==0){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        sprintf(operandValue+1,"%d",displacement);
        for (i=0; i<litCounter; i++){
            if(displacement == literalAddressInts[i]){
                strncpy(operandValue, literals[i], 10);
                                LTORG=true;
                if (strcmp(opcodeName2, "LDB") == 0) {
                    baseValueLogan = symValueInts[i];
                    strncpy(operandValue, symbols[i], 10);
                } else if (strcmp(opcodeName2, "RSUB") == 0) {
                	strncpy(operandValue, symbols[i], 10);
                }
                format = 4;
                programCounter++;
                break;
            } else {
                format = 3;
            }
        }
        /*
			Flag is set if value is negative, and if it
			is not negative, then you add the programCounter + 3.
        */
        if (negFlag == 0) {
        	displacement = displacement + programCounter + 3;
        }

        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                strncpy(operandValue, symbols[i], 10);
                if (strcmp(opcodeName2, "LDB") == 0) {
                    baseValueLogan = symValueInts[i];
                    strncpy(operandValue, symbols[i], 10);
                } else if (strcmp(opcodeName2, "RSUB") == 0) {
                	strncpy(operandValue, symbols[i], 10);
                }

            }
        }
        error=1;
    }
    // 110100 op m
    if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==1 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        sprintf(operandValue+1,"%d",displacement);
        for (i=0; i<symCounter; i++){
            if(baseValueLogan == symValueInts[i]){
               strncpy(operandValue, symbols[i], 10);
            }
        }
        error=1;
        format = 3;
    }
    // 111000 op c,X
    if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==1 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        commaX[0] = ',';
        commaX[1] = 'X';
        sprintf(operandValue+1,"%d",displacement);
        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                if (strcmp(opcodeName2, "LDB") == 0) {
                    baseValueLogan = symValueInts[i];
                    strncpy(operandValue, symbols[i], 10);
                } else if (strcmp(opcodeName2, "RSUB") == 0) {
                	strncpy(operandValue, symbols[i], 10);
                }
            }
        }
        error=1;
        format = 3;
    }
    // 111001 +op m,X
    if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==1 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==1){
        getDisp(0, recordLine, dispIndex+4, dispIndex+20);
        commaX[0] = ',';
        commaX[1] = 'X';
        plusExtension = '+';
        sprintf(operandValue+1,"%d",displacement);
        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                strncpy(operandValue+1, symbols[i], 10);
                if (strcmp(opcodeName2, "LDB")) {
                    baseValueLogan = symValueInts[i];
                }
            }
        }
        error=1;
        format = 4;
        programCounter++;
    }
    // 111010 op m,X
    if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==1 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==1 && nixbpe[5][nIndex]==0){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        commaX[0] = ',';
        commaX[1] = 'X';
        sprintf(operandValue+1,"%d",displacement);

        if (negFlag == 0) {
        	displacement = displacement + programCounter + 3;
        }
        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }

        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                strncpy(operandValue, symbols[i], 10);
                if (strcmp(opcodeName2, "LDB")) {
                    baseValueLogan = symValueInts[i];
                }
            }
        }
        error=1;
        format = 3;

    }
    // 111100 op m,X
    if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==1 && nixbpe[3][nIndex]==1 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        commaX[0] = ',';
        commaX[1] = 'X';
        sprintf(operandValue+1,"%d",displacement);
        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(baseValueLogan == symValueInts[i]){
               strncpy(operandValue, symbols[i], 10);
            }
        }
        error=1;
        format = 3;
    }
    // 000 op m
    if(nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]==0 && nixbpe[2][nIndex]==0){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        sprintf(operandValue+1,"%d",displacement);
        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                strncpy(operandValue, symbols[i], 10);
            }
        }



        error=1;
        format = 3;
    }
    // 001 op m,X
    if(nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]==0 && nixbpe[2][nIndex]==1){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        commaX[0] = ',';
        commaX[1] = 'X';
        sprintf(operandValue+1,"%d",displacement);
        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                strncpy(operandValue+1, symbols[i], 10);
                if (strcmp(opcodeName2, "LDB")) {
                    baseValueLogan = symValueInts[i];
                }
            }
        }
        error=1;
        format = 3;
    }
    // 100000 op @c
    if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==0 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        operandValue[0] = '@';
        sprintf(operandValue+1,"%d",displacement);

        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                if (strcmp(opcodeName2, "LDB") == 0) {
                    baseValueLogan = symValueInts[i];
                    strncpy(operandValue, symbols[i], 10);
                } else if (strcmp(opcodeName2, "RSUB") == 0) {
                	strncpy(operandValue, symbols[i], 10);
                }
            }
        }
        error=1;
        format = 3;
    }
    // 100001 +op @m
    if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==0 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==1){
        getDisp(0, recordLine, dispIndex+4, dispIndex+20);
        operandValue[0] = '@';
        plusExtension = '+';
        sprintf(operandValue+1,"%d",displacement);
        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                strncpy(operandValue+1, symbols[i], 10);
                if (strcmp(opcodeName2, "LDB")) {
                    baseValueLogan = symValueInts[i];
                }
            }
        }
        error=1;
        format = 4;
        programCounter++;
    }
    // 100010 op @m
    if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==0 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==1 && nixbpe[5][nIndex]==0){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        operandValue[0] = '@';
        sprintf(operandValue+1,"%d",displacement);
        for (i=0; i<litCounter; i++){
            if(displacement == literalAddressInts[i]){
                strncpy(operandValue, literals[i], 10);
                                LTORG=true;
                if (strcmp(opcodeName2, "LDB") == 0) {
                    baseValueLogan = symValueInts[i];
                    strncpy(operandValue, symbols[i], 10);
                } else if (strcmp(opcodeName2, "RSUB") == 0) {
                	strncpy(operandValue, symbols[i], 10);
                }
                format = 4;
                programCounter++;
                break;
            } else {
                format = 3;
            }
        }
        /*
			Flag is set if value is negative, and if it
			is not negative, then you add the programCounter + 3.
        */
        if (negFlag == 0) {
        	displacement = displacement + programCounter + 3;
        }

        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                strncpy(operandValue, symbols[i], 10);
                if (strcmp(opcodeName2, "LDB") == 0) {
                    baseValueLogan = symValueInts[i];
                    strncpy(operandValue, symbols[i], 10);
                } else if (strcmp(opcodeName2, "RSUB") == 0) {
                	strncpy(operandValue, symbols[i], 10);
                }

            }
        }
        error=1;
    }
    // 100100 op @m
    if(nixbpe[0][nIndex]==1 && nixbpe[1][nIndex]==0 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==1 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        operandValue[0] = '@';
        sprintf(operandValue+1,"%d",displacement);
        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                strncpy(operandValue, symbols[i], 10);
                if (strcmp(opcodeName2, "LDB") == 0) {
                    baseValueLogan = symValueInts[i];
                    strncpy(operandValue, symbols[i], 10);
                } else if (strcmp(opcodeName2, "RSUB") == 0) {
                	strncpy(operandValue, symbols[i], 10);
                }

            }
        }
        error=1;
        format = 3;
    }
    // 010000 op #c
    if(nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        operandValue[0] = '#';
        sprintf(operandValue+1,"%d",displacement);
        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                strncpy(outputSymbol, symbols[i], 10);
                if (strcmp(opcodeName2, "LDB")) {
                    baseValueLogan = symValueInts[i];
                }
            }
        }

        error=1;
        format = 3;
    }
    // 010001 +op #m
    if(nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==1){
        getDisp(0, recordLine, dispIndex+4, dispIndex+20);
        operandValue[0] = '#';
        plusExtension = '+';
        sprintf(operandValue+1,"%d",displacement);
        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                strncpy(operandValue+1, symbols[i], 10);
                if (strcmp(opcodeName2, "LDB")) {
                    baseValueLogan = symValueInts[i];
                }
            }
        }
        error=1;
        format = 4;
        programCounter++;
    }
    // 010010 op #m
    if(nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==0 && nixbpe[4][nIndex]==1 && nixbpe[5][nIndex]==0){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        operandValue[0] = '#';
        sprintf(operandValue+1,"%d",displacement);

        for (i=0; i<litCounter; i++){
            if(displacement == literalAddressInts[i]){
                strncpy(operandValue, literals[i], 10);
                                LTORG=true;
                if (strcmp(opcodeName2, "LDB") == 0) {
                    baseValueLogan = symValueInts[i];
                    strncpy(operandValue, symbols[i], 10);
                } else if (strcmp(opcodeName2, "RSUB") == 0) {
                	strncpy(operandValue, symbols[i], 10);
                }
                format = 4;
                programCounter++;
                break;
            } else {
                format = 3;
            }
        }
        /*
			Flag is set if value is negative, and if it
			is not negative, then you add the programCounter + 3.
        */
        if (negFlag == 0) {
        	displacement = displacement + programCounter + 3;
        }

        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                strncpy(operandValue, symbols[i], 10);
                if (strcmp(opcodeName2, "LDB") == 0) {
                    baseValueLogan = symValueInts[i];
                    strncpy(operandValue, symbols[i], 10);
                } else if (strcmp(opcodeName2, "RSUB") == 0) {
                	strncpy(operandValue, symbols[i], 10);
                }

            }
        }
        error=1;
        format = 3;
    }
    // 010100 op #m
    if(nixbpe[0][nIndex]==0 && nixbpe[1][nIndex]==1 && nixbpe[2][nIndex]==0 && nixbpe[3][nIndex]==1 && nixbpe[4][nIndex]==0 && nixbpe[5][nIndex]==0){
        getDisp(0, recordLine, dispIndex, dispIndex+12);
        operandValue[0] = '#';
        sprintf(operandValue+1,"%d",displacement);
        if (programCounter == symValueInts[symsUsedCounter]) {
        	strncpy(outputLabel, symbols[symsUsedCounter], 10);
            symsUsedCounter++;
        }
        for (i=0; i<symCounter; i++){
            if(displacement == symValueInts[i]){
                strncpy(operandValue, symbols[i], 10);
                if (strcmp(opcodeName2, "LDB") == 0) {
                    baseValueLogan = symValueInts[i];
                    strncpy(operandValue, symbols[i], 10);
                } else if (strcmp(opcodeName2, "RSUB") == 0) {
                	strncpy(operandValue, symbols[i], 10);
                }

            }
        }

        error=1;
        format = 3;
    }
    if(error==0)//something went wrong
    printf("Error\n");// do not know what to print here.
}

void getDisp(int destinationIndex, char* origin, int originIndex, int endIndex) {
	int binIndex = originIndex;
    int i;
    int j;
    for (originIndex; originIndex < endIndex; originIndex++) {
        constValue[destinationIndex++] = origin[originIndex];
    }
    constValue[destinationIndex] = '\0';

    for (i = 0; i < 4; i++) {
    	negCheck[i] = origin[binIndex+i];
    }

    negCheck[4] = '\0';

    /*

		This is where we will do a check of F - 8 in binary.
		If it is, it should flip all the bits and then add 1
		which will make it 2's comp.

		ie. FF4 -> 1111 1111 0100
		flipped -> 0000 0000 1011 -> 00B which is the address for LOOP

    */
    if (strcmp(negCheck, "1111") == 0) {
    	// printf("%s\n", constValue);
    	// Flip all binary values of constValue
    	negFlag = 1;
    	for (j = 0; j < 12; j++) {
    		if (constValue[j] == '1') {
    			constValue[j] = '0';
    		} else {
    			constValue[j] = '1';
    		}
    	}
    }

    char *SA = constValue;
    char *checker = SA;
    int constValueInHex = 0;
    do {
        int value = *checker == '1'?1:0;
        constValueInHex = (constValueInHex<<1)|value;
        checker++;
    } while (*checker);
    displacement = constValueInHex;
}

int convertHexToInt(char* hexToConvert) {
    int li2;
    char * pEnd;
    li2 = strtol (hexToConvert,&pEnd,16);
    return li2;
}


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
