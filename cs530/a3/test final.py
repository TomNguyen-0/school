#Checks if the int is between 0 and 9
def digit(var):
        if(isinstance(var,int)):
                Inumber = a
        else:
                return print("invalid digit")
        if(Inumber>10 or Inumber<0):
		
#checks for a valid operation
def operation(var):
        if(var != '+' and var != '-' and var != '*' and var != '/' and var != '%'):
#                #invalid operation
                print("invalid operation")
        else:
                print("valid operation")
			
def ischar(var):
        if(var.isalpha()):
                print("an alpha ")
        else:
                print("not an alpha")
