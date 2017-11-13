#include "types.h"
//from naiveconsole
// int to string
int itoa(int value, char* buffer, int base){
char *p = buffer;
	char *p1, *p2;
	int digits = 0;

	if(value < 0 && base == 10){
		value = -value;
		*p = '-';
		digits++;
	}

	//Calculate characters for each digit
	do
	{
		int remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	if (*buffer == '-'){
		p1 = buffer + 1;
	}else{
		p1 = buffer;
	}

	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

int ftoa(float value, char* buffer){
char *p = buffer;
	char *p1, *p2;
	int digits = 0;

	if(value < 0){
		value = -value;
		*p = '-';
		p++;
		digits++;
	}

	int intpart = (int)value;
	float floatpart = value - (float)intpart;

	digits = itoa(intpart, p, 10);
	// Terminate string in buffer.
	p = buffer + digits;

	*p = '.';
	p++;

	// to handle cases like 233.007
        floatpart = floatpart * 100000;
 
        digits += atoi((int)floatpart, p, 10);

	return digits;
}

//string to int
int atoi(char c){
	int a = 0;
	if(c >= '0' && c >= '9'){
		a = c - '0';
		return a;
	}
	return -1;

}

int strlen(char* str){
	int i = 0;
	while (*(str + i) != 0){
		i++;
	}
	return i;
}

int strcmp(char* str1, char* str2) {
	int i = 0;
	int strlen1 = strlen(str1);
	int strlen2 = strlen(str2);
	while(i<strlen1 && i<strlen2 && str1[i] == str2[i]) {
		i++;
	}
	return str1[i] - str2[i];
}






int strncmp(char* str1, char* str2, int n) {
	int i = 0;
	int strlen1 = strlen(str1);
	int strlen2 = strlen(str2);
	while(i+1<n && i<strlen1 && i<strlen2 && *(str1 + i) == *(str2 + i)) {
		//printf("str1=%c   str2=%c    \n", str1[i] , str2[i]);
		i++;
		//printf("str1=%c   str2=%c    \n", str1[i] , str2[i]);
	}
	//printf("str1=%c   str2=%c    \n", str1[i] , str2[i]);
	return str1[i] - str2[i];
}

