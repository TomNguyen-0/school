void transform(char* recordLine) {
	int index; //index tracks the location of first unchecked bit in the array recordLine
	int end; //index to track the end of next section to examine
	int format; //int to represent the type of instruction being used
	char length[1]; // String to represent the length of the recordLine being examined
	char opcodeName[1];
	char opcodeBits[6]; //bit array to hold opcode
	char address[24]; //array to hold bits of address of the first instruction on the line
	char tempLength[8]; //temporary bit array to hold the bits for length of the line
	int arrayIndex; //int to hold the index of an array being used
	char opcodesF1[6];
	char opcodesF2[11];
	char opcodesF34[42];
	char mnemonicF1[6];
	char mnemonicF2[11];
	char mnemonicF34[42];
	//variable to hold operation

	opcodesF1[0] = "110001";
	mnemonicF1[0] = "FIX";
	opcodesF1[1] = "110000";
	mnemonicF1[1] = "FLOAT";
	opcodesF1[2] = "111101";
	mnemonicF1[2] = "HIO";
	opcodesF1[3] = "110010";
	mnemonicF1[3] = "NORM";
	opcodesF1[4] = "111100";
	mnemonicF1[4] = "SIO";
	opcodesF1[5] = "111110";
	mnemonicF1[5] = "TIO";

	opcodesF2[0] = "100100";
	mnemonicF2[0] = "ADDR";
	opcodesF2[1] = "101101";
	mnemonicF2[1] = "CLEAR";
	opcodesF2[2] = "101000";
	mnemonicF2[2] = "COMPR";
	opcodesF2[3] = "100111";
	mnemonicF2[3] = "DIVR";
	opcodesF2[4] = "100110";
	mnemonicF2[4] = "MULR";
	opcodesF2[5] = "101011";
	mnemonicF2[5] = "RMO";
	opcodesF2[6] = "101001";
	mnemonicF2[6] = "SHIFTL";
	opcodesF2[7] = "101010";
	mnemonicF2[7] = "SHIFTR";
	opcodesF2[8] = "100101";
	mnemonicF2[8] = "SUBR";
	opcodesF2[9] = "101100";
	mnemonicF2[9] = "SVC";
	opcodesF2[10] = "101110";
	mnemonicF2[10] = "TIXR";

	opcodesF34[0] = "000110";
	mnemoicF34[0] = "ADD";
	opcodesF34[1] = "010110";
	mnemoicF34[1] = "ADDF";
	opcodesF34[2] = "010000";
	mnemoicF34[2] = "AND";
	opcodesF34[3] = "001010";
	mnemoicF34[3] = "COMP";
	opcodesF34[4] = "100010";
	mnemoicF34[4] = "COMPF";
	opcodesF34[5] = "001001";
	mnemoicF34[5] = "DIV";
	opcodesF34[6] = "011001";
	mnemoicF34[6] = "DIVF";
	opcodesF34[7] = "001111";
	mnemoicF34[7] = "J";
	opcodesF34[8] = "001100";
	mnemoicF34[8] = "JEQ";
	opcodesF34[9] = "001101";
	mnemoicF34[9] = "JGT";
	opcodesF34[10] = "001110";
	mnemoicF34[10] = "JLT";
	opcodesF34[11] = "010010";
	mnemoicF34[11] = "JSUB";
	opcodesF34[12] = "000000";
	mnemoicF34[12] = "LDA";
	opcodesF34[13] = "011010";
	mnemoicF34[13] = "LDB";
	opcodesF34[14] = "010100";
	mnemoicF34[14] = "LDCH";
	opcodesF34[15] = "011100";
	mnemoicF34[15] = "LDF";
	opcodesF34[16] = "000010";
	mnemoicF34[16] = "LDL";
	opcodesF34[17] = "011011";
	mnemoicF34[17] = "LDS";
	opcodesF34[18] = "011101";
	mnemoicF34[18] = "LDT";
	opcodesF34[19] = "000001";
	mnemoicF34[19] = "LDX";
	opcodesF34[20] = "110100";
	mnemoicF34[20] = "LPS";
	opcodesF34[21] = "001000";
	mnemoicF34[21] = "MUL";
	opcodesF34[22] = "011000";
	mnemoicF34[22] = "MULF";
	opcodesF34[23] = "010001";
	mnemoicF34[23] = "OR";
	opcodesF34[24] = "110110";
	mnemoicF34[24] = "RD";
	opcodesF34[25] = "010011";
	mnemoicF34[25] = "RSUB";
	opcodesF34[26] = "111011";
	mnemoicF34[26] = "SSK";
	opcodesF34[27] = "000011";
	mnemoicF34[27] = "STA";
	opcodesF34[28] = "011110";
	mnemoicF34[28] = "STB";
	opcodesF34[29] = "010101";
	mnemoicF34[29] = "STCH";
	opcodesF34[30] = "100000";
	mnemoicF34[30] = "STF";
	opcodesF34[31] = "110101";
	mnemoicF34[31] = "STI";
	opcodesF34[32] = "000101";
	mnemoicF34[32] = "STL";
	opcodesF34[33] = "011111";
	mnemoicF34[33] = "STS";
	opcodesF34[34] = "111010";
	mnemoicF34[34] = "STSW";
	opcodesF34[35] = "100001";
	mnemoicF34[35] = "STT";
	opcodesF34[36] = "000100";
	mnemoicF34[36] = "STX";
	opcodesF34[37] = "000111";
	mnemoicF34[37] = "SUB";
	opcodesF34[38] = "010111";
	mnemoicF34[38] = "SUBF";
	opcodesF34[39] = "111000";
	mnemoicF34[39] = "TD";
	opcodesF34[40] = "001011";
	mnemoicF34[40] = "TIX";
	opcodesF34[41] = "110111";
	mnemoicF34[41] = "WD";

	//grab 24 bits for the address (24 bits = 6 hex nibbles)
	end = 24;
	index = 0;
	arrayIndex = 0;
	address = getBitArray(address, arrayIndex, recordLine, index, end);
	index = end;


	end = length + 8; //set end to 8 bits after length, in order to grab 8 bits for the length
	arrayIndex = 0;
	tempLength = getBitArray(tempLength, arrayIndex, recordLine, index, end);
	index = end;
	length = convertBitsToString(tempLength, 8);

//modify this section after getting info from tom, loop through line
	end = length + 6;
	arrayIndex = 0;
	opcodeBits = getBitArray(opcodeBits, arrayIndex, recordLine, index, end);
	index = end;
	opcode = convertBitsToString(opcodeBits, 6);
	format = searchForOpcode(opcode);
	operation = searchForOperation(format, opcode);
}

char* getBitArray(char* destination, int destinationIndex, char* origin, int originIndex, int endIndex) {
	for (originIndex; originIndex < endIndex; originIndex++) {
		destination[destinationIndex++] = origin[originIndex];
	}

	return destination;
}

char* convertBitsToString(char* bits, int arrayLength) {
	char bitString[arrayLength];
	int i;
	for (i = 0; i < arrayLength; i++) {
		bitString[i] = bits[i];
	}
	return bitString;
}

int searchForOpcode(const char **opcode) {
	int instructionFormat = -1; //if -1 is returned then instruction isn't in appendix A
	int i;
	for (i = 0; i < 6; i++) {
		if (opcodesF1[i] = opcode) {
			instructionFormat = 1;
			opcodeName[0] = searchForOperation(instructionFormat, i, opcode);
			return instructionFormat;
		}
	}

	for (i = 0; i <11; i++) {
		if (opcodesF2[i] = opcode) {
			instructionFormat = 2;
			opcodeName[0] = searchForOperation(instructionFormat, i, opcode);
			return instructionFormat;
		}
	}

	for (i = 0; i < 42; i++) {
			if (opcodesF34[i] = opcode) {
					instructionFormat = 34;
					opcodeName[0] = searchForOperation (instructionFormat, i, opcode);
					return instructionFormat;
			}
	}
	return instructionFormat;
}

const char** searchForOperation(int arrayToSearch, int arrayIndex, const char** opcode) {
	if (arrayToSearch = 1) {
		return mnemonicF1[arrayIndex];
		}
	if (arrayToSearch = 2) {
		return mnemonicF2[arrayIndex];
	}
	if (arrayToSearch = 34) {
		return mnemonicF34[arrayIndex];
	}
}
