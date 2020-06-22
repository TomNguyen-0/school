#Checks if the int is between 0 and 9
def isDigit(var):
        if(isinstance(var,int)):
                Inumber = a
        else:
                return False
        if(Inumber>10 or Inumber<0):
#invalid digit
                return False
        else:
                return True

#checks for a valid operation
def isOp(var):
        if(var != '+' and var != '-' and var != '*' and var != '/' and var != '%'):
                #invalid operation
                return False
        elif(var != '+' or var != '-' or var != '*' or var != '/' or var != '%'):
                return True

#Checks for if it is an alphabet
def isChar(var): 
#        char = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
        if(var.isalpha()):
                return True
        else:
                return False
#        for j in range(len(char)):
#                if(var[i] == char[j]):
#                        continue
#                elif (j == 51):
#                        print("not a char")
#                        return 0

def checkFirst(item):
	if item == '_':
		return True
	else:
		return item.isalpha()
	
def digitOrChar(item):
	if item.isdigit():
		return True
	elif item == '_':
		return True
	else:
		return item.isalpha()
	
def isId(string):
	for index in range (len(string)):
		if index == 0:
			if not checkFirst(string[index]):
				return False
		else:
			if  not digitOrChar(string[index]):
				return False
	return True

#reads the line and return true if the line is valid
def isLine(var):
        length = len(var)
        start = True
        opstart = False
        for i in range(len(var)):
                if(start):
                        if(isId(var[i])):
                                start=False
                                continue
                        elif(isOp(var[i])):#double operation is found
                                return False
                        elif(var[i] == ';'):
                                return True
                        else:
                                return False
                elif (isChar(var[i]) or isDigit(var[i])):
                        continue
                #space has two options the next is either an op or an id
                elif (var[i] == " "):
                        if(not start and not opstart):
                                opstart=True
                                continue
                        elif(not start and opstart):
                                opstart=False
                                start = True
                                continue
                        return False
                elif (opstart):
                        if(isOp(var[i])):
                                continue
                        else:
                                return False
                else:
                        return False
        return False
                        
def isRule(line):
        #break and return tokenizedLine at end of line 
                #maybe done with while (! end of line) ?
        tokenLine=''
        parsedLine = line.split(' ')
        for i in range (len(parsedLine)):
                if isId(parsedLine[i]):
                        tokenLine +='id '
                elif isOp(parsedLine[i]):
                        tokenLine += 'op '
                elif (parsedLine[i] == '='):
                        tokenLine += '= '
                elif (parsedLine[i] == ';'):
                        tokenLine += '; '
                elif(parsedLine[i] == '\n'):
                        tokenLine +='\n'
                        continue
                else:
                        return False
        return tokenLine

def isSyntax(line):
        tokenizedLine = isRule(line)
        return tokenizedLine

def notExpChar(character):
	if character == 'id':
		return False
	elif character == 'op':
		return False
	elif character == '(':
		return False
	elif chacter == ')':
		return False
	else:
		return True

def isValid(line):#This method will not work for parenthesis. example "((" will trigger false
        tokenLine=''
#        print(line)
        parsedLine = line.split(' ')
#        print(parsedLine)
        for i in range(len(parsedLine)):
                if(i+1 == len(parsedLine)):
                        return True
                if (parsedLine[i] == parsedLine[i+1]):
                        return False
        return True;
#old code:
#	if "=" in lineOfTokens:
#		if ";" in lineOfTokens:
#			return isAssignment(lineOfTokens)
#		else:
#			return False #assignment needs both = and ;, expression doesnt have either 
#	else:
#		return isExpression(lineOfTokens)

#checks if this line has any parenthesis
def ifParenthesis(line):
        for i in range(len(line)):
                if(line[i] == '(' or line[i] ==')'):
                        return True
        return False

def countParenthesis(line):
        count = 0
        for i in range(len(parsedLine)):
                if(parsedLine[i] == '(' or parsedLine[i] ==')'):
                        count+=1
        return count

def addSpace(line):
        tokenLine=''
        parsedLine = line.split(' ')
        for i in range (len(parsedLine)):
                if(ifParenthesis(parsedLine[i])):
                        var = list(parsedLine[i])
                        word = ''
                        for j in range(len(var)):
                                if(var[j] == '('):
                                        if(word == ''):
                                                tokenLine+='( '
                                        else:
                                                tokenLine+=' '
                                                tokenLine+=word
                                                tokenLine+='( '
                                                word=''
                                elif(var[j] != ')'):
                                        word += var[j]
                                        if(j+1 == len(var)):
                                                tokenLine +=word
                                                tokenLine += ' '
                                                word =''
                                else:
                                        tokenLine += word
                                        tokenLine += ' '
                                        tokenLine += ') '
                                        word = ''
                elif(parsedLine[i] == '\n'):
                        tokenLine +='\n'
                        continue
                else:
                        tokenLine += parsedLine[i]
                        tokenLine += ' '
        return tokenLine
        

def pRule(line):
        tokenLine=''
        parsedLine = line.split(' ')
        for i in range (len(parsedLine)):
                #print(parsedLine[i])
                #print(tokenLine)
                if isId(parsedLine[i]):
                        tokenLine +='id '
                elif isOp(parsedLine[i]):
                        tokenLine += 'op '
                elif (parsedLine[i] == '='):
                        tokenLine += '= '
                elif (parsedLine[i] == ';'):
                        tokenLine += '; '
                elif(parsedLine[i] == '\n'):
                        continue
                elif(parsedLine[i] ==')'):
                        tokenLine +=') '
                elif(parsedLine[i] =='('):
                        tokenLine += '( '
                else:
                        return False
        return tokenLine

def isExpression(line):
        tokenLine=''
        parsedLine = line.split(' ')
        for i in range(len(parsedLine)):
                if(notExpChar(parsedLine[i])):
                        return False
                if(i+1 == len(parsedLine)):
                        return True
                if(parsedLine[i] == parsedLine[i+1]):
                        return False
                return True
        
def pValid(line):
        if(line==False):
                return False
        tokens = line.split(' ')
        if not tokens[1] == '=':
                return isExpression(line)
        elif not tokens[len(tokens)-1] == ';':
                return isExpression(line)
        else:
                if not tokens[0] == 'id':
                        return False
                else:
                        assignmentLine = line.split('=')
                        alNoSemi = assignmentLine[1]
                        splitted = alNoSemi.split(';')
                        expPortion = splitted[0].strip()
                        return isExpression(expPortion)

text_file = open ("test.txt","r")
#lines= text_file.readline()
#print(isValid(pRule(addSpace(lines))))
lines = text_file.readlines()
#print(addSpace(lines))
#print (pRule(addSpace(lines)))
for line in lines:
        if( ifParenthesis(line)):
                print(pValid(pRule(addSpace(line))))
        else:
                print(pValid(isRule(line)))
#print(lines)
#print(isLine(lines))
text_file.close()
