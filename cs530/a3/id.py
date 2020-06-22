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

test = '_ab+1cdefG'
test2 = 'a+'
print(isId(test))
