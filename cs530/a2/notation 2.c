#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
   DEFINE ALL FUNCTIONS AND GLOBALS HERE.
*/
bool ImmediateAddressing();
bool indirect();
bool simple();
bool direct();
bool pc_relative();
bool base();
void notation();
void nixbpe (char * characters, int length, int location); //Figure out the nixbpe values and store it.
int nixbpe[6][512];
/*
   Main: 
*/
int main(void){
int size;
   FILE *fp;
   fp = fopen("C:/Users/tom/Desktop/projects/cs530/a2/test2.txt", "r");
   fseek(fp,0,SEEK_END);//seeks to the end of file.
   size=ftell(fp);//the length of file stored into size
	fseek(fp, 0, SEEK_SET);//set the pointer back to the start of file.
	char fileArray[size];
	fread(fileArray, sizeof(fileArray), 1, fp); //read file and store it into fileArray
   int location=6;//location should be set after op code.
   nixbpe(fileArray, sizeof(fileArray), location);
   notation();    
   fclose(fp);
}

void notation(){//from book page 499. Having a hard time calculating target address.
   if(n==1 && i==1 && x==0 && b==0 && p==0 && e==0)//simple addressing type
      printf("op c"); //c will be disp
   if(n==1 && i==1 && x==0 && b==0 && p==0 && e==1)
      printf("+op m");// m will be addr format 4 instruction
   if(n==1 && i==1 && x==0 && b==0 && p==1 && e==0)
      printf("op m"); // (pc)+disp
   if(n==1 && i==1 && x==0 && b==1 && p==0 && e==0)
      printf("op m"); // (b) + disp
   if(n==1 && i==1 && x==1 && b==0 && p==0 && e==0)
      printf("op c,X"); //disp + (X)
   if(n==1 && i==1 && x==1 && b==0 && p==0 && e==1)
      printf("+op m,X"); //addr+(X) format 4 instruction
   if(n==1 && i==1 && x==1 && b==0 && p==1 && e==0)
      printf("op m,X"); // (PC)+disp+(X)
   if(n==1 && i==1 && x==1 && b==1 && p==0 && e==0)
      printf("op m,X");// (B)+disp+(X)
   if(n==0 && i==0 && x==0)
      printf("op m"); // b/p/e/disp
   if(n==0 && i==0 && x==1)//simple addressing type stops
      printf("op m,X"); // b/p/e/disp+(X)
   if(n==1 && i==0 && x==0 && b==0 && p==0 && e==0)//indirect addressing type
      printf("op @c"); // disp
   if(n==1 && i==0 && x==0 && b==0 && p==0 && e==1)
      printf("+op @m"); // addr
   if(n==1 && i==0 && x==0 && b==0 && p==1 && e==0)
      printf("op @m"); // (PC) + disp
   if(n==1 && i==0 && x==0 && b==1 && p==0 && e==0)//indirect addresing ends
      printf("op @m"); // (B) + disp
   if(n==0 && i==1 && x==0 && b==0 && p==0 && e==0)//immediate types
      printf("op #c");// disp
   if(n==0 && i==1 && x==0 && b==0 && p==0 && e==1)
      printf("+op #m"); //addr
   if(n==0 && i==1 && x==0 && b==0 && p==1 && e==0)
      printf("op #m"); //(PC)+disp
   if(n==0 && i==1 && x==0 && b==1 && p==0 && e==0)//immediate type ends
      printf("op #m"); // (B)+disp
}

void nixbpe (char characters,  int location){//checks each character from given location for nixbpe
   int j,initialized,Location=0;
   for(initialized=0; initialized<6; initialized++){
    nixbpe[initialized][location]=0
   }
    for( j=0; j<6; j++){
      if(nixbpe[j][location]==0){// location of n
         if(characters[j]=='1')
            nixbpe[j][location]=1;
      }
      if(nixbpe[j][location]==1){// location of i
         if(characters[j]=='1')
            nixbpe[j][location]=1;
      }
      if(nixbpe[j][location]==2){// location of x
         if(characters[j]=='1')
            nixbpe[j][location]=1;
      }
      if(nixbpe[j][location]==3){// location of b
         if(characters[j]=='1')
            nixbpe[j][location]=1;
      }
      if(nixbpe[j][location]==4){// location of p
         if(characters[j]=='1')
            nixbpe[j][location]=1;
      }
      if(nixbpe[j][location]==5){// location of e
         if(characters[j]=='1')
            nixbpe[j][location]=1;
      }
   }
   //for debugging
   printf("n=%d i=%d x=%d b=%d p=%d e=%d",nixbpe[0][location],nixbpe[1][location],nixbpe[2][location],nixbpe[3][location],nixbpe[4][location],nixbpe[5][location]);
  
}


bool ImmediateAddressing(){ //checks for immediate addressing for format 3 and 4
   if(n==0 && i==1)
      return true;
   return false;
}

bool indirect(){ //checks for indirect addressing for format 3 and 4
   if(n==1 && i==0)
      return true;
  return false;
}

bool simple(){ //check for simple addressing for format 3 and 4
   if(n==0 && i==0)
      return true;
   if(n==1 && i==1)
      return true;
   return false;
}

bool direct(){ //check for direct addressing for format 3 only. format 4 will always use direct addressing.
   if(b==0 && p==0)
      return true;
   return false;
}

bool pc_relative(){ //check for pc-relative addressing for format 3 only
   if(b==0 && p==1)
      return true;
   return false;
}

bool base(){ //check for base addressing for format 3 only
   if(b==1 && p==0)
      return true;
   return false;
}