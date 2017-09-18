#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "format.h"

//Checks to make the bit string is 32 bits
int isBinary(char* ptr) {
	if (strlen(ptr) != 32) return 1;
	while (*ptr != '\0') {
              if (*ptr != '0' && *ptr != '1')  return 2;
              ptr++;
        }
	return 0;
}
float Pow (int power, int base){
    float result = 1;
    int i = 1;
    int negative=0;
    if (base < 0) {
       base = base * -1;
       negative=1;
    }
    for (; i<=base; i++) {
        result = result*power;  
    }
    if (negative == 1) result = 1/result;
    return result;
} 
int LOG10(double LOG){
    int result=0;
    if (LOG<0) LOG=LOG*-1;
    while (LOG/10>=1){
           LOG=LOG/10;
           result++;
    }
    while (LOG*10<1){
           LOG=LOG*10;
           result--;
    }
    return result;
}
//Reverses the string
int reverseStr(char* str) {
   int i = strlen(str)-1;
   int j = 0;
   
   char temp;
   
   while (j < i ) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i--;
		j++;
   }
   
   return 0;
}

//Converts the bit string according to the two's complement rule
char* convertToInt(char* ptr) {
	int i = 0;
	int result = 0;
	int negative = 0;
	char* intResult = (char*) malloc(sizeof(char)*34);
	
	if (ptr[0] == '1') {
		negative = 1;
		reverseStr(ptr);
		char* temp = ptr;
		char* reverse = ptr;
		for (; *temp != '1' && *temp != '\0'; temp++) {
			*temp = '1';
		}
		if (*temp == '1') {
			*temp = '0';
		}
		reverseStr(ptr);
		
		for (; *reverse != '\0'; reverse++) {
			if (*reverse == '1') {
				*reverse = '0';
			}
			else {
				*reverse = '1';
			}
		}
	}
	for (; *ptr != '\0'; ptr++) {
		if (negative == 1) {
			result = result * 2 + ((*ptr - '0')*-1);
		}
		else {
			result = result * 2 + (*ptr - '0');
		}
	}
	
	if (result == 0) {
	intResult[0] = '0';
	intResult[1] = '\0';
	return intResult;
	}
	
	for (; result != 0; result = result/10) {
		int b = result%10;
		if (b < 0) {
			b = b*-1;
		}
		intResult[i] = b + '0';
		i++;
	}
	
	if (negative == 1) {
		intResult[i] = '-';
		i++;
	}
	
	intResult[i] = '\0';
	reverseStr(intResult);
	return intResult;
}

//Convert the bit string to single precision float
char* convertToFloat(char* ptr) {
	int negative;
	int exp = 0;
	float mant = 1.0;

	
	char* floatResult = (char*) malloc(sizeof(char)*16);
	char* tempResult = floatResult;
		
	negative = ptr[0] -'0';
	int i = 1;
	for (; i <= 8; i++) {
		
		exp = exp*2 + (ptr[i] - '0');
		
	}
	
	int min = 1;
	int max = 23;
	
	if (exp == 0) {
		min = 0;
		max = 22;
		mant = 0.0;
	}
	
	char* temp = &ptr[9];
	int j = min;
	for (; j <= max; j++) {
		if (*temp == '1') {
			mant = mant + Pow(2, (j*-1));
		}
		temp++;
	}
	
	if (exp == 255) {
		if (mant != 1.0) {
			printf("NaN\n");
			exit(0);
		}
		else {
			if (negative == 1) {
				printf("ninf\n");
				exit(0);
			}
			else {
				printf("pinf\n");
				exit(0);
			}
			
		}
		
	}
	else if (exp == 0 && mant == 0.0) {
		if (negative == 0) {
			printf("0.0e0\n");
			exit(0);
		}
		else {
			printf("-0.0e0\n");
			exit(0);
		}
	}	
	
	float mantissa = mant*Pow(2,(exp-127));
	int exponent = 0;
        //printf("RESULT: %f",mantissa);
	exponent = LOG10(mantissa);
	//printf("RESULT: %d",exponent);
	if (exponent < 0) {
		exponent--;
		int expTemp = exponent;
		while (expTemp != 0) {
			mantissa = mantissa *10;
			expTemp++;
		}
	}
	else {
		int expTemp = exponent;
		while (expTemp != 0) {
			mantissa = mantissa/10;
			expTemp--;
		}
	}
	
	if (negative == 1) {
		*floatResult = '-';
		floatResult++;
	}
	
	int y = 0;	
	for (; y < 7 && mantissa != 0;y++) {
		if (y == 1) {
			*floatResult = '.';
			floatResult++;
		}		
		*floatResult = (int)mantissa%10 + '0';
		mantissa = (mantissa - (*floatResult-'0'))*10;
		floatResult++;
	}
	
	*floatResult = 'e';
	floatResult++;
		
	if (exponent == 0) {
		*floatResult = '0';
		floatResult++;
	}
	
	if (exponent < 0) {
		*floatResult = '-';
		floatResult++;
	}
	
	char* reverseExp = floatResult; 
	for (; exponent != 0; exponent/=10) {
		int b = exponent%10;
		if (b < 0) {
			b = b*-1;
		}
		*floatResult = b + '0';
		floatResult++;
	}
	
	reverseStr(reverseExp);
	
	*floatResult = '\0';
	
	return tempResult;
}

int main(int argc, char** argv) {
	int malformed = 0;
	char* result;
	
	if (argc < 3) {
		printf("Error: You didn't input enough arguments!");
		return 0;
	}
	
	if (argc > 3) {
		printf("Error: You inputted too many arguments!");
		return 0;
	}
	
	//check if the first argument is in the correct format 
        switch (isBinary(argv[1])){
                case (1):{ 
                     printf("Error: The inputted sequence is not 32 bits\n");
                     malformed = 1;
                     break;
                } 
                case (2): {
                     printf("Error: The inputted sequence contains digits other than 1 and 0\n");
                     malformed = 1;
                     break;
                }
                default:
                     break; 
        }
        // process the second argument and check if it is malformed 
	if (strcasecmp(argv[2],"int") == 0) {
		result = convertToInt(argv[1]);
	}
	else if (strcasecmp(argv[2],"float") == 0) {
		result = convertToFloat(argv[1]);
	}
	else {
		printf("Error: Output form entered is not valid form\n");
		malformed = 1;
	}
	switch (malformed){
                case (1):{ 
                     return 0;
                     break;
                } 
                
                default:
                     printf("%s\n",result);
                     free(result);
                     return 0;
                     break; 
        }		
}
