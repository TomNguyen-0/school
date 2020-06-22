import sys
#Assignment #3, parser for assignments and expressions
#Names: Kellen Gillooley (818216237), Tom Nguyen (820468110) 
#function definitions and implementations

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


def isOp(var): 
        if(var != '+' and var != '-' and var != '*' and var != '/' and var != '%'):
                #invalid operation
                return False
        elif(var != '+' or var != '-' or var != '*' or var != '/' or var != '%'):
                return True

def isRule(line):
        tokenLine=''
        parsedLine = line.split(' ')
        for i in range (len(parsedLine)):
                if(parsedLine[i] ==''):
                        continue
                elif isId(parsedLine[i]):
                        tokenLine +='id '
                elif isOp(parsedLine[i]):
                        tokenLine += 'op '
                elif (parsedLine[i] == '='):
                        tokenLine += '= '
                elif (parsedLine[i] == ';'):
                        tokenLine += '; '
                elif(parsedLine[i] == '\n'):
                        continue
                else:
                        return False
        return tokenLine  
       
def isSyntax(line):
        if( ifParenthesis(line)):
                tokenizedLine= pRule(addSpace(line))
        else:
                tokenizedLine = isRule(line)
        return tokenizedLine

def notExpChar(character):
	if character == 'id':
		return False
	elif character == 'op':
		return False
	elif character == '(':
		return False
	elif character == ')':
		return False
	else:
		return True

def isExpression(line):
        tokenLine=''
        parsedLine = line.split(' ')
        for i in range(len(parsedLine)-1):
                if(notExpChar(parsedLine[i])):
                        return False
                if(i+1 == len(parsedLine)):
                        return True
                if(parsedLine[i] == parsedLine[i+1]):
                        if(parsedLine[i] == ')' or parsedLine[i]=='('):
                                continue
                        return False
        return True

def isValid(line):
        if '=' in line:
                if ';' not in line:
                        return False
                else:
                        assignmentLine = line.split('=',1)
                        lhSide = assignmentLine[0].strip()
                        if not lhSide == 'id':
                                return False
                        alNoSemi = assignmentLine[1]
                        splitted = alNoSemi.rsplit(';',1)
                        expPortion = splitted[0].strip()
                        if '=' in expPortion:
                                return False
                        elif ';' in expPortion:
                                return False
                        else:
                                return isExpression(expPortion)		
        else:
                return isExpression(line)

def ifParenthesis(line):
        for i in range(len(line)):
                if(line[i] == '(' or line[i] ==')'):
                        return True
        return False

def addSpace(line):
        tokenLine=''
        parsedLine = line.split(' ')
        for i in range (len(parsedLine)-1):
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
        for i in range (len(parsedLine)-1):
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

#open files
#sys.argv = ['',"test.txt"]
#inputFile = open(sys.argv[1], "r")
inputFile = open("in.txt", "r")
outputFile = open("out.txt", "w")
with inputFile as file:
        infileContents = file.read().splitlines()
for i in range (len(infileContents)):
        outputFile.write(infileContents[i])
        tokenizedLine = isSyntax(infileContents[i])
        if tokenizedLine == False:
                outputFile.write("	False	Tokenization Failure\n")
        elif((i+1 == len(infileContents)) and (infileContents[i]==' ')):
                continue
        else:
                if isValid(tokenizedLine):
                        outputFile.write("	True\n")
                else:
                        outputFile.write("	False	Syntactical Failure\n") 
inputFile.close()
outputFile.close()


