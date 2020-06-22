/*
David Arce - cssc0858@edoras.sdsu.edu
Logan Lasiter - cssc1034@edoras.sdsu.edu
Kellen Gillooley - cssc1024@edoras.sdsu.edu
Tom Nguyen - cssc0883@edoras.sdsu.edu

CS 530 Spring 2017

Assignment #2, Disassembler 'dasm'
header.h
*/

#ifndef header_h
#define header_h

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

#endif
