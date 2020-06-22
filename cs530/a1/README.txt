Assignment #1, Hexdump
File Information: README
Names: Kellen Gillooley and Tom Nguyen 


Class information
CS 530, Spring 2017
Kellen Gillooley: CSSC1024@edoras.sdsu.edu
Tom Nguyen: CSSC0883@edoras.sdsu.edu


File Manifest
README.txt
prog1.c
xsd makefile


Compile Instructions
Compiles as normal file does, without any additional linked libraries needed


Execution Instructions 
This program can execute one of two ways. 
To execute a hexdump of a given input, execute using the command line instructions “xsd <filename>”, where xsd is the name of the program and <filename> is a command line argument passed into the program. <filename> should be the filename of the file to be used for the hexdump. 
To execute a binarydump of a given input, execute using the command line instructions “xsd -b <filename>”, where xsd is the name of the program, -b is a flag to denote a binary dump, and <filename> is a command line argument passed into the program. <filename> should be the filename of the file to be used for the binarydump. 


Design Decisions
Program is broken down into three parts:
        Main method,
        Hexdump method,
        Binarydump method
The main method reads in the file passed in on the command line and processes the command line to determine whether or not a -b flag has been listed on the command line. If the -b flag has been utilized, then the main method will call the binary dump method. Otherwise, the main method will call the hexdump method


The hexdump method takes all of the characters from the file and prints out all of the hex representations of the characters, 16 bytes per line, until the end of the file. The method also lists the address of the first byte in each line at the beginning of each line and the output of the printable form of the characters at the end of the line. For any non-printable character, the program prints a ‘.’ as the printable representation of the character. 
The binarydump method performs the same operations as the hexdump method, but prints out the binary representation of the characters instead of the hex representation. Additionally, the binarydump separates the characters into lines of 6 bytes rather than 16. 


Known Deficiencies or Bugs
There are no known deficiencies or bugs.


Lessons Learned 
We learned many lessons from this assignment. First, we learned how to achieve a complex process like a hexdump from a low level perspective. Instead of looking at hexdump as an overall large or complex task, we can instead look at it as a repeated task on an individual character, in order to achieve the overall goal. Secondly, we took a closer look at how addresses are represented in memory. In this assignment, we looked at how addresses are relative compared to what they represent. In this assignment, the addresses are relative to the start of the file, therefore the addresses start at 000000 and proceed onwards in the corresponding groups of bytes per line. Finally, this assignment represents the key concept of data abstraction. As the characters are inputted as ASCII values, we abstract these characters to represent printable or non-printable characters based on these values. Additionally, we also abstract any ASCII value not falling in the range of a printable character as a ‘.’, instead of retaining its original value based off of the ASCII representation.