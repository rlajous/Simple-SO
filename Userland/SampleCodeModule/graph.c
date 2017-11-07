#include <graph.h>
#include <stdio.h>
#include "syscalls.h"
int width = 1;
int height = 1;

void setVideo(){
	getResolution(&height,&width);
    printf("%d       %d\n",width,height);
}
/*
void graph_axis() {
    for(int y=0; y<height-2; y--) {
    	putPixel(width/2, y);
    }
	for(int x=0; x<width; x++) {
    	putPixel(x, (height-2)/2);
	}
}
*/
void graph_line(int a, int b) {
	/*for(int y=height/2; y>-(height/2); y--) {
		for(int x=-(width/2); x<width/2; x++) {
			int yAux = y+(height-2)/2;
			int xAux = x-width/2;
			if (y==0)
    		{
    			printGraphic(1);
    		}
    		else if (x==0)
    		{
    			printGraphic(1);
    			
    		}else if(y == ((x*a) - b)){
				printGraphic(1);
			}else{
    			printGraphic(0);
			}
    			
		}
    }*/
    graph_cuadratic(0,a,b);

}

void graph_cuadratic(int a, int b, int c) {
	
    for(int y=height/2; y>-(height/2); y--) {
        for(int x=-(width/2); x<width/2; x++) {
            int yAux = y+(height-2)/2;
            int xAux = x-width/2;
            if (y==0)
            {
                printGraphic(1);
            }
            else if (x==0)
            {
                printGraphic(1);
                
            }else if(y == x*x*a + x*b + c){
                printGraphic(1);
            }else{
                printGraphic(0);
            }
                
        }
    }
}
