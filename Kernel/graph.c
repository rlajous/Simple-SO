/*comento hasta que putPixel exista

#include <keyboardDriver.h>
#include <videoDriver.h>

extern void putPixel(int x, int y)

//hay que reemplazar por los valores en videoDriver
int width = 1
int height = 1
int charWidth = 1
int charHeight = 1

void graph_axis() {
    for(int y=0; y<height-2*charHeight; y--) {
    	putPixel(width/2, y);
    }
	for(int x=0; x<width; x++) {
    	putPixel(x, (height-2*charHeight)/2);
	}
}

void graph_line(int a, int b) {
	for(int y=0; y<height-2*charHeight; y++) {
		for(int x=0; x<width; x++) {
			yAux = y+(height-2*charHeight)/2;
			xAux = x-width/2;
			if(yAux == xAux*a + b)
				putPixel(x, y);
		}
    }
}

void graph_cuadratic(int a, int b, int c) {
	for(int y=0; y<height-2*charHeight; y++) {
		for(int x=0; x<width; x++) {
			yAux = y+(height-2*charHeight)/2;
			xAux = x-width/2;
			if(yAux == xAux*xAux*a + xAux*b + c)
				putPixel(x, y);
		}
    }
}

*/