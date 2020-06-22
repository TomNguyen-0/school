Group Members: Tom Nguyen (820468110) and Daniel Reyes
CS 370, Section 2
April 28, 2017
Lab Assignment #3


Contributions:
Tom: Circuit Schematic File and Library File
Daniel: Consulted on equation/ciruit and Readme File


Files: Circuit Schematic File (.cct), Library File (.clf), and Winzip (.zip)
-Lab3 Part1.ctt
-Lab3 Part2.ctt
-TNguyen.clf
-TNguyen.zip


* Circuit Schematic File: This file includes the two main components: The Factory Preset Model and the User-Programmable Model. The goal of these models is to detect specific 8 bit binary sequences within a continuous serial input stream. Upon detecting the correct sequence, the output should be a logical true value. In any other case, false.


* SECRET KEY: We used 00010111 as the secret key for the factory preset model.


* Library File: This file includes the individual parts (circuits) for the Circuit Schematic File to use and piece together the entire anti-theft machine.


* Design Process: For this anti-theft machine, we focused on keeping the circuits as simple as possible, using a minimal number of gates, in order to minimize the total cost.


How steps to obtain the cirucuits:
1. Made a state diagram of the usercode
2. take the state diagram and covert it to a state table
3. took the state table and made a kmap of it
4. took the kmap of it and made the equation from it
5. took the equation and figure out the next state circuits.
6. to reduce the amount of circuits made a chip that contains flip flops and 4 variables A, B, C, and X
7. Made each requirement on the lab assignment into a single chip.
8. after making all the chips plugged it into the program LogicWorks and tested it 

******************************Parts used in the cct file:***********************************

Lab3DA:
A flip flip that has four AND gates connected to it. On the left side we want to put the eqution we got in step 5.

Lab3Lock:
Taken from lecture 18 slides. after 16 attempts output will be one.

Lab3 8Part:
contains: Lab3Lock
Take in the inputs and store it in a shifter. Then output the input withint the shifter.

Lab3 Save:
contains (2) Lab3 Hex:
The input is the output. 8 inputs 8 outputs and a the save button is
set as clock. Each time the clock is pushed this will allow the inputs that 
are sitting be pushed to the output. The reset will be set to the reset flip flop 
insid the Lab3 Hex.

Lab3 Hex:
Take the inputs and store it in the four flip flops. When save is pressed it will then put it out as outputs.
 
Lab3 Programs:
contains Lab3 Save and Lab3 Hex:
compares each input and ouput with XOR and AND gates. When they are all matched up then
the status will be a 1 otherwise it will output STATUS: 0.