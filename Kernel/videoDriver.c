#include <videoDriver.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const VIDEO = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000 + 80*2*24;
static uint8_t fontColor = 0x2;
static const uint32_t WIDTH = 80;
static const uint32_t HEIGHT = 25 ;
static uint8_t * mouse = (uint8_t*)0xB8001;
static char screen[26*160];
static uint8_t * currentScreen = screen + 80*2*24;
static int mousescreen = 1;


void updateScreen(){
	for (int i = 0; i < HEIGHT; i++) {
		memcpy(VIDEO + i*WIDTH*2, screen + i*WIDTH*2, WIDTH*2);
	}
}
void scrollUp(){
	memcpy(screen, screen + WIDTH*2, WIDTH*2*(HEIGHT-1));
	for (int i = 0; i < WIDTH * 2; i+=2){
		screen[i + 80*2*24] = ' ';
	}
	updateScreen();

}
void backspace(){
	if (currentVideo > VIDEO) {
		currentVideo -= 2;
		currentScreen -= 2;
		printChar(' ');
		currentVideo -= 2;
		currentScreen -= 2;
	}
}

void newline() {
	do{
		printChar(' ');
	}while((uint32_t)(currentVideo - VIDEO) % (WIDTH * 2) != 0);
}
/*
void changeFontColor(char newColor) {
	fontColor = newColor;
}
*/
void printChar(char c){
	// Si el puntero del VIDEO sobre pasa los parametros donde esta la pantalla lo posiciona en la ultima linea y mueve todo 1 renglon para arriba
	if(currentVideo >= (VIDEO + WIDTH*2*HEIGHT)){
		scrollUp();
		currentVideo = VIDEO + WIDTH*2*24;
		currentScreen = screen + WIDTH*2*24;
	}
	if(c=='\b'){
		backspace();
	}else if(c=='\n'){
		newline();
	}else{
		*currentVideo = c;
		*currentScreen = c;
		currentVideo ++;
		currentScreen++;
		*currentVideo = fontColor;
		*currentScreen = fontColor;
		currentScreen++;
		currentVideo ++;
	}
}
void cleanBack(){
	for(int x = 1;x<WIDTH*HEIGHT*2-1;x += 2){
			VIDEO[x] = 0X07;
			*(screen+x) = 0X07;
	}
}

void copyscreen(char *buffer){
	int y = 0;
	for (int x = 0;x<WIDTH*HEIGHT*2; x += 2)
		if(screen[x+1] == 0X6F)
			buffer[y++] = screen[x];
	buffer[y] = 0;
}
void printPosition(uint8_t x,uint8_t y,uint8_t flag){
	uint8_t flag2 = 0;
	if(!flag){
		cleanBack();
	}	
	mouse = (VIDEO + x*2*WIDTH + y*2+1);
	mousescreen = x*2*WIDTH + y*2+1;
	if(flag){
		*mouse = 0X6F;
		screen[mousescreen] = 0X6F;
		for(int x = 1;x<WIDTH*HEIGHT*2-1;x += 2){
			if(VIDEO+x <= mouse){
				if(screen[x] == 0X6F || flag2)
					flag2 = 1;
				else
					flag2 = 0;
				if(flag2)
					screen[x] = 0X6F;
			}else
				screen[x] = 0X07;
		}
		updateScreen();
	}	
	else{	
		*mouse = 0X9F;
	}

}

void printDec(uint64_t value){
	printBase(value, 10);
}

void printHex(uint64_t value){
	printBase(value, 16);
}

void printBin(uint64_t value){
	printBase(value, 2);
}

void printBase(uint64_t value, uint32_t base){
    uintToBase(value, buffer, base);
    printString(buffer);
}
void printString(const char * string) {
	int i;
	printChar('x');
	for (i = 0; string[i] != 0; i++){
		printChar(string[i]);
	}
}

void clear(){
	for (int i = 0; i < HEIGHT * WIDTH; i++){
		VIDEO[i * 2] = ' ';
		screen[i * 2] = ' ';
	}
	currentScreen = screen + 80*2*24;
	currentVideo = VIDEO + 80*2*24;
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base){
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2){
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}
