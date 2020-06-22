
/*************************************************************
Name: Tom Nguyen and Kellen Gillooley
username: Kellen Gillooley: CSSC1024@edoras.sdsu.edu
         Tom Nguyen: CSSC0883@edoras.sdsu.edu
Project: CS530 Assignment 1
Date: February 11, 2017
File: proj1.c
Notes: A hexdump program that will open a text file and write either the 
ASCII hex value or the binary value as well as the printable ASCII characters.
Any non-printable characters will be printed as a '.' but still display the
hex or binary value.
**************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
void hexdump(char * characters, int length);
void binarydump (char* characters, int length);

/*************************************************************
function: HEXDUMP
Notes:   Takes an array of characters and out print the 
      hexadeciaml value for them.
I/O: input parameters: pointer to the array of characters and 
       the length of array of characters.
     output: print out the hexadecimal value for the array of 
       charatcers.
**************************************************************/
void hexdump(char * characters, int length) {
	int i,one=-1; //controls the space for hex print out
	char *contents = (char*) characters;
	char printableChars[17];

	for(i = 0; i < length; i++) {        
		if((i%16) == 0) {
			if (i != 0) 
				printf(" %s\n", printableChars);
			printf(" %06x:", i); //replace 6 with number of digits for address
			if ( i < 16) {
				printf(" ");
			}
		}

		if(one==1){
			printf(" "); //print space every four hex letters.
			one = 0; //set counter one to zero
		}
		else
			one++;
		printf("%02X", contents[i]);
		if (!isprint(contents[i]))
			printableChars[i % 16] = '.';
		else
			printableChars[i % 16] = contents[i];
		printableChars[(i % 16) + 1] = '\0'; //terminator to allow array to print

	}

	while((i%16) != 0) {
		printf("  ");
		i++;
		if(i%2 ==0)
			printf(" ");
	}

	printf(" %s\n", printableChars);
}

/*************************************************************
function: BINARYDUMP
Notes:    Takes an array of characters and out print the
          binary value for them.
I/O:  input parameters: pointer to the array of characters and 
         the length of array of characters.
      output: print out the binary value for the array of 
         charatcers.

**************************************************************/
void binarydump (char* characters, int length){
	int i,n,ii; //n is decimal value, ii for the second loop.
	char *content = (char*) characters;
	char printableCharas[7];

	for(i = 0; i < length; i++) {
		if((i%6) == 0) {
			if (i != 0) 
				printf(" %s\n", printableCharas);
			printf(" %06x:", i); //replace 6 with number of digits for address
		}

		n =  content[i];
		char hex[17],OnZ[65]=""; // One aNd Zero holds bit patterns
		sprintf(hex,"%x",content[i]);

		if(n<16){
			if(n>7)
				strcat(OnZ,"0000");
			else if (n>3)
				strcat(OnZ,"00000");
			else if (n>1)
				strcat(OnZ,"000000");
			else
				strcat(OnZ,"0000000");
		}
		for(ii=0; hex[ii]!='\0'; ii++)
		{
			switch(hex[ii])
			{
			case '0':
				strcat(OnZ, "0000");
				break;
			case '1':
				strcat(OnZ, "0001");
				break;
			case '2':
				strcat(OnZ, "0010");
				break;
			case '3':
				strcat(OnZ, "0011");
				break;
			case '4':
				strcat(OnZ, "0100");
				break;
			case '5':
				strcat(OnZ, "0101");
				break;
			case '6':
				strcat(OnZ, "0110");
				break;
			case '7':
				strcat(OnZ, "0111");
				break;
			case '8':
				strcat(OnZ, "1000");
				break;
			case '9':
				strcat(OnZ, "1001");
				break;
			case 'a':
			case 'A':
				strcat(OnZ, "1010");
				break;
			case 'b':
			case 'B':
				strcat(OnZ, "1011");
				break;
			case 'c':
			case 'C':
				strcat(OnZ, "1100");
				break;
			case 'd':
			case 'D':
				strcat(OnZ, "1101");
				break;
			case 'e':
			case 'E':
				strcat(OnZ, "1110");
				break;
			case 'f':
			case 'F':
				strcat(OnZ, "1111");
				break;
			default:
				printf("error");
			}
		}

		printf(" %s",OnZ);
		if (!isprint(content[i]))
			printableCharas[i % 6] = '.';
		else
			printableCharas[i % 6] = content[i];

		printableCharas[(i % 6) + 1] = '\0'; //terminator to allow array to print
	}

	while((i%6) != 0) {
		printf("         ");
		i++;
	}
	printf(" %s\n", printableCharas);

}

/*************************************************************
main
Notes: By convention the main should appear at the end of file.
**************************************************************/
int main( int argc, char *argv[]){
	if (argc < 2) {
		printf("Not enough arguments entered");
		exit(0);
	} 

	int size;
	FILE *fp; 

	if(strcmp(argv[1], "-b")==0) {
		fp = fopen(argv[2], "r");
		fseek(fp,0,SEEK_END);
		size=ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char fileArray[size];
		fread(fileArray, sizeof(fileArray), 1, fp); //what needs to go in for 1? 
		binarydump (fileArray, sizeof(fileArray)); //says fileArray is not initialized
		fclose(fp);
	}
	else {
		fp = fopen(argv[1], "r");
		fseek(fp,0,SEEK_END);
		size=ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char fileArray[size];
		fread(fileArray, sizeof(fileArray), 1, fp); //what needs to go in for 1?     
		hexdump(fileArray, sizeof(fileArray)); //says fileArray is not initialized
		fclose(fp);
	}
	return 0;
}
/*************************[EOF: xsd.c]************************/