#include <videoDriver.h>
#include <font.h>

#define HEIGHT y_res
#define WIDTH x_res
#define MOUSE_LIMIT HEIGHT/CHAR_HEIGHT* WIDTH

typedef struct {
	unsigned char red, green, blue;
} color;

static int get_res(unsigned char *ptr);
static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static int x_res =0;
static int y_res =0;
static int terminal= 0;

static char buffer[2000] = { ' ' };
static unsigned char ** const VIDEO = (unsigned char**) 0x0005C28;
//static long * currentVideo = (long*)0x0005C28;
//static uint8_t * mouse = (uint8_t*)currentVideo;
static int mousescreen = 0;
static int mousepixel = 0;
static int mouseindex=0;
static color letter = {0,204,0};
static color background = {0,0,0};
static int scrolling=0;
void load_vDriver() {
	x_res = get_res((unsigned char *)0x0005C12);
	y_res = get_res((unsigned char *)0x0005C14);
	mousescreen = MOUSE_LIMIT - WIDTH;
	mouseindex=mousescreen;
}

void setTerminal(int t){
	terminal=t;
	mousescreen= MOUSE_LIMIT - WIDTH +terminal;
}

static int get_res(unsigned char *ptr){
	unsigned char *res_byte=ptr;
	int res=0;
	res+= *(res_byte+1);
	res= res<<8;
	res += *res_byte;
	return res;
}

void getResolution(int* x,int*y){
	(*x)=HEIGHT;
	(*y)=WIDTH;
}

void scrollUp(){
	memcpy(*VIDEO, *VIDEO + (3 * WIDTH * CHAR_HEIGHT), (HEIGHT * WIDTH * 3) - (CHAR_HEIGHT * WIDTH * 3));
	mousescreen= MOUSE_LIMIT - WIDTH;
	scrolling=1;
	for (int i = 0; i < WIDTH/CHAR_WIDTH; i++){
		printChar(' ');
		buffer[i]=' ';
	}
	scrolling=0;
	mousescreen = MOUSE_LIMIT - WIDTH;
	mouseindex = MOUSE_LIMIT - WIDTH + terminal;


}

void backspace(){
	if (mousescreen>MOUSE_LIMIT - WIDTH + terminal)
	{
		mousescreen--;
		putCharAt(' ',mousescreen+1);
		printChar(' ');
		mousescreen--;
		mouseindex--;
	}
}

void newline() {
	mousescreen += WIDTH -mousescreen%WIDTH;
	if(mousescreen>=MOUSE_LIMIT){
		scrollUp();
		//printChar(' ');
		//mousescreen--;
	}
	/*
	do{
		printChar(' ');
	}while((uint32_t)(currentVideo - *VIDEO) % (WIDTH * 2) != 0);
	*/
}

void printChar(char c) {
	// Si el puntero del VIDEO sobre pasa los parametros donde esta la pantalla lo posiciona en la ultima linea y mueve todo 1 renglon para arriba
	if(mousescreen%(WIDTH/CHAR_WIDTH) == 0 && mousescreen != MOUSE_LIMIT - WIDTH) {
		newline();
	}

	if(mousescreen>=MOUSE_LIMIT){
		scrollUp();
		//mousescreen = WIDTH*3*(HEIGHT-1);
		//currentScreen = screen + WIDTH*2*24;
	}
	if(c=='\b'){
		backspace();
	}else if(c=='\n') {
		newline();
		mouseindex= MOUSE_LIMIT - WIDTH;
	}else if (c>31)
	{
		buffer[mousescreen]=c;
		putCharAt(c,mousescreen);
		/*
		int x=(mousescreen/WIDTH)*CHAR_HEIGHT;
		int y=(mousescreen%WIDTH)*CHAR_WIDTH;
		unsigned char * char_map = pixel_map(c);
		for(int i = 0; i < CHAR_HEIGHT; i++) {
			unsigned char pixel = char_map[i];
			char mask[] = {128, 64, 32, 16, 8, 4, 2, 1};
			char aux;
			for (int j = 0; j < CHAR_WIDTH; j++) {
				aux = pixel & mask[j];
				unsigned char * pixColor = (*VIDEO) + 3 * ((y+j)+(x+i)*WIDTH);
				if (aux != 0) { // Tiene que escribir en ese lugar
					pixColor[0] = letter.blue;
					pixColor[1] = letter.green;
					pixColor[2] = letter.red;
				} else {
					pixColor[0] = 0;
					pixColor[1] = 0;
					pixColor[2] = 0;
				}
			}
		}*/
		mousescreen++;
		mouseindex++;
		if (!scrolling)
		{
			if(mousescreen%(WIDTH/CHAR_WIDTH) == 0 && mousescreen != MOUSE_LIMIT - WIDTH) {
				newline();
			}
		}

	}
}
void cursorLeft(){
	if (mousescreen>MOUSE_LIMIT - WIDTH + terminal)
	{
		mousescreen--;
		putCharAt(buffer[mousescreen+1],mousescreen+1);
	}
}
void cursorRight(){
	if (mousescreen < mouseindex)
	{	
		mousescreen++;
		putCharAt(buffer[mousescreen-1],mousescreen-1);
	}
}
void putCharAt(char c,int index){
	int x=(index/WIDTH)*CHAR_HEIGHT;
	int y=(index%WIDTH)*CHAR_WIDTH;
	unsigned char * char_map = pixel_map(c);
	for(int i = 0; i < CHAR_HEIGHT; i++) {
		unsigned char pixel = char_map[i];
		char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
		char aux;
		for (int j = 0; j < CHAR_WIDTH; j++) {
			aux = pixel & mask[j];
			unsigned char * pixColor = (*VIDEO) + 3 * ((y+j)+(x+i)*WIDTH);
			if (aux != 0) { // Tiene que escribir en ese lugar
				pixColor[0] = letter.blue;
				pixColor[1] = letter.green;
				pixColor[2] = letter.red;
			} else {
				pixColor[0] = 0;
				pixColor[1] = 0;
				pixColor[2] = 0;
			}
		}
	}
}
void blink(){
	int x=(mousescreen/WIDTH)*CHAR_HEIGHT;
	int y=(mousescreen%WIDTH)*CHAR_WIDTH;
	for (int i = 0; i < CHAR_HEIGHT; i++)
	{
		for (int j = 0; j < CHAR_WIDTH; j++)
		{
			unsigned char * pixColor = (*VIDEO) + 3 * ((y+j)+(x+i)*WIDTH);

			if(pixColor[0] == letter.blue){
				pixColor[0] = 0;
			}else{
				pixColor[0] = letter.blue;
			}
			if(pixColor[1] == letter.green){
				pixColor[1] = 0;
			}else{
				pixColor[1] = letter.green;
			}
			if(pixColor[2] == letter.red){
				pixColor[2] = 0;
			}else{
				pixColor[2] = letter.red;
			}

		}
	}
	//mousescreen
}
/*
void printPixel(int matriz){

	putPixelAt(matriz,mousepixel++);
	if (mousepixel==HEIGHT*WIDTH)
	{
		mousepixel=0;
	}

}
*/

void putPixelAt(int color,int xx,int yy) {
	/*
	int x=(index/WIDTH);
	int y=(index%WIDTH);
	*/
	if (yy<WIDTH&&xx<HEIGHT-CHAR_HEIGHT){
		unsigned char * pixColor = (*VIDEO) + 3 * ((yy)+(xx)*WIDTH);
		if (color == 1) { // Tiene que escribir en ese lugar
			pixColor[0] = letter.blue;
			pixColor[1] = letter.green;
			pixColor[2] = letter.red;
		} else {
			pixColor[0] = 0;
			pixColor[1] = 0;
			pixColor[2] = 0;
		}
	}
}

/*
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
*/

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
	//printChar('x');
	for (i = 0; string[i] != 0; i++){
		printChar(string[i]);
	}
}

void clear(){
<<<<<<< Updated upstream
	for (int i = 0; i < HEIGHT/CHAR_HEIGHT; i++){
=======
	for(int i=0; i<47; i++)
>>>>>>> Stashed changes
		newline();
	/*mousescreen = 0;
	for (int i = 0; i < HEIGHT * WIDTH; i++){
		printChar(" ");
>>>>>>> Stashed changes
		//screen[i * 2] = ' ';
	}
	mousescreen = MOUSE_LIMIT - WIDTH + terminal;
	*/
//	currentScreen = screen + 80*2*24;
//	currentVideo = VIDEO + WIDTH*3*(HEIGHT-1);
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
