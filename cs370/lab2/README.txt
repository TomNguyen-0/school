Group Members: Tom Nguyen and Daniel Reyes
CS 370, section 2
March 16, 2017
Lab Assignment #2

1) Contributions:
Tom: 13-bit Data Transmission, ECC Detector
Daniel: ECC Generator

2) Files: README.txt, Circuit Schematic File (TNguyen.cct) and Library File (TNguyen.clf). These files will be contain in a zip file (TNguyen.zip)

- Circuit Schematic File: This file includes the three main components: the ECC Generator, 13-bit Data Transmission, and ECC Detector at main memory. The ECC Generator takes in 8 bits and generates it into a 13-bit vector. The 13-bit Data Transmitter then takes the vector and allows the end user to change bits to represent errors. From here, the ECC Detector will correct one bit errors and display “C”. When there are two bit errors, it will display “X” “X” and an “E”.

- Library File: This file includes the individual parts (circuits) for the Circuit Schematic File to use and piece together the entire error correction circuit.



***************************Parts used in the cct file:******************************
ECC Generator
Takes in 8 bits (hex) and generates it into a 13-bit vector (Hamming Code)
13-bit Data Transmission
Takes the 13-bit Data Transmissions and allow the end user to change the bit to represent error(s). For the rest of the other bits we will push it through to Main Memory.
Main Memory
Will correct one bit error and display 'C'. When there are two bits error display 'X' 'X' and an 'E'

When displaying Error: 
Hex will display: 'X' 'X' This is because there is a buffer that will not allow
any information to pass when there is an error.

Note: If user input more than two errors it will cause problems for the Main Memory output. On every odd error bit after the first two it will display the incorrect output other wise it will output Error and 'X' 'X' on the hex display.

Parts in Main Memory:
LAB2 PART REAL MAIN:
Here we wanted to have the output be 1 whenever H1 was true or when H2 was true. The reason for this is  because C is 1100 and E is 1110. So, we needed H1 to push out 1 for the first 11. If H2 is one H1 needs to also be 1. However if H1 is 1 then H2 will be zero. The rest are just pushed through.

LAB2 PART REAL P:
P will XOR positions 1-12 then afterwards XOR P4 with the result
LAB2 PART C
Output: C8, C4, C2, C1. Takes the input of D0 - D7 put it into the ECC Generator to produce the P0 to P3. Take the result of that and XOR-ing it with input P0 to P3 in order to find the C value.

LAB2 CORRECT2:
Output: C8, C4, C2, C1. Takes the input of D0 - D7 put it into the ECC Generator to produce the P0 to P3. Take the result of that and XOR-ing it with input P0 to P3 in order to find the C value.

LAB2 PART REAL C2:
C is the result of OR-ing C1,  C2, C4, and C8

LAB2 PART H1:
Calculates the H1 and H2 using P and C along with the truth table from lecture 10.

LAB2 F CORRECT:
Here we are correcting the error bit if they are wrong. The eqautions was derive from a truth table that we developed. Each D0 will have a AND_4 that will AND the variables require to produce the value 1 so that later we can XOR it with the input value of DD0 to DD7.

LAB2 F CORRECT WITH BUFFER:
Repeating the values of D0 to D7 after they have been checked and corrected. The buffer will allow to output HI-Z if H2 is 1. H2 is an error that will occur when an even amount of error occurs.