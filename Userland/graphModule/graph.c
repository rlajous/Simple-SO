#include <graph.h>
#include <stdio.h>
#include "syscalls.h"

int width = 1;
int height = 1;

void setVideo(){
	getResolution(&height,&width);
    //printf("%d       %d\n",width,height);
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
void graph_line(double a, double b) {
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
    graph_cuadratic(0.0,a,b);

}
double truncar(double nro){
     unsigned long x = 10 * nro;
     double y = (double)x / (double)10;
     return y;
}

void graph_cuadratic(double a, double b, double c) {
    
    double maxWidth=(width/2/10);
    double maxHeight=(height/10/2);
    //printGraphic(1,10,10);
    for(int y=height/2; y>-(height/2); y--) {
        for(int x=-(width/2); x<width/2; x++) {
            
            if (y==0)
            {
                printGraphic(1,(height/2)-y,x+(width/2));
            }
            else if (x==0)
            {
                printGraphic(1,(height/2)-y,x+(width/2));
                
            }
                
        }
    }
    
    for(double x=-maxWidth; x <maxWidth; x+=0.1){
        printGraphic(1,(int)((maxHeight-(x*x*a + x*b + c))*10),(int)((x+maxWidth)*10));

        //printf("  x= %d  y=  %d\n",(int)((x+maxWidth)*10),(int)((maxHeight-(x*x*a + x*b + c))*10));
        //printf(" %d",(int) (a)  );
    }



	/*

    for(double y=height/2/10; y>-(height/2/10); y-=0.1) {
        for(double x=-(width/2/10); x<width/2/10; x+=0.1) {
            
            if (truncar(y)==0.0)
            {
                printGraphic(1);
            }
            else if (truncar(x)==0.0)
            {
                printGraphic(1);
                
            }else if(truncar(y) == truncar(x*x*a + x*b + c)){

                printGraphic(1);

            }else{

                printGraphic(0);

            }
                
        }
    }
    */
}
