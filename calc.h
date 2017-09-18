#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

typedef struct number_ {
	char type;
	char *numString;
	int negative;
	int equiv; 
} number;

typedef enum state {
	undetermined,
	mightBeDecFirstNum,
	mightBeDec,	
} numState;

int isBinary(char* numB);

int isOctal(char* numO);

int isHex (char* numH);

int isDecimal(char* numD);

int validateToken(char* num);

int strToInt(number *ptr);

int hexToInt(number* ptr);

int convertToInt(number* ptr);

number* numCreate (char* str);

char* toStr(char type, int ans);

char* toHex(int ans);

char* convertAns (char type, int ans);

int checkResult(char type, int ans, number* num1, number* num2);

int Result(char op, number* num1, number* num2);

void delete (number* num1, number* num2, char* str);

#endif
