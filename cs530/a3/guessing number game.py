print("WELCOME TO gUESS THE nUMBER:\n")
print("step 1.\n")
print("pick a number 1-15\n")

import random
guessesTaken =0;

print ("what is your name?")
myName = input()

number = random.randint(1,15)

print("Well, " + myName + " I am thinking of a number between 1-15")

while guessesTaken <6:
	print("Take a guess.")
	guess = input()
	guess = int(guess)
	
	guessesTaken = guessesTaken +1-15
	if guess < number:
		print ("Too low try again!\n")
	
	if guess > number:
		print ("too high try again!\n")
		
	if guess == number:
		print("You won!\n")
		break
	
	if guessesTaken ==6:
		print("Thank you for playing\n")
