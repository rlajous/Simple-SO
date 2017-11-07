//from naiveconsole
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

int strlen(char* str){
	int length = 0;
	int i = 0;
	do{
		length++;
		i++;
	}while (*(str + i) != 0);
	return length;
}