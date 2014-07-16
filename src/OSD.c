
#include <stdint.h>
#include <stdlib.h>

#include "Config.h"
#include "OSD.h"
#include "Graphics.h"

void updateOSD(int8_t grid[][yres]) {
    
    //Display craft attitude information
    drawAttitude(grid);
    
    //showCompas();
}

void drawAttitude(int8_t grid[][yres]) {
    
    int thickness = 2;
    
    //Draw craft center
    drawPoint(xres/2,yres/2,thickness,grid);
	//Left
    setPixel(grid,xres/2-1,yres/2+2);
    setPixel(grid,xres/2-1,yres/2+3);
    setPixel(grid,xres/2-2,yres/2+2);
    setPixel(grid,xres/2-2,yres/2+3);
    
    setPixel(grid,xres/2-3,yres/2+4);
    setPixel(grid,xres/2-3,yres/2+5);
    setPixel(grid,xres/2-4,yres/2+4);
    setPixel(grid,xres/2-4,yres/2+5);
    
    setPixel(grid,xres/2-5,yres/2+2);
    setPixel(grid,xres/2-5,yres/2+3);
    setPixel(grid,xres/2-6,yres/2+2);
    setPixel(grid,xres/2-6,yres/2+3);
    
    setPixel(grid,xres/2-7,yres/2);
    setPixel(grid,xres/2-8,yres/2);
    setPixel(grid,xres/2-7,yres/2+1);
    setPixel(grid,xres/2-8,yres/2+1);
    
    setPixel(grid,xres/2-9,yres/2);
    setPixel(grid,xres/2-10,yres/2);
    setPixel(grid,xres/2-9,yres/2+1);
    setPixel(grid,xres/2-10,yres/2+1);
    
    //Right
    setPixel(grid,xres/2+1,yres/2+2);
    setPixel(grid,xres/2+1,yres/2+3);
    setPixel(grid,xres/2+2,yres/2+2);
    setPixel(grid,xres/2+2,yres/2+3);
    
    setPixel(grid,xres/2+3,yres/2+4);
    setPixel(grid,xres/2+3,yres/2+5);
    setPixel(grid,xres/2+4,yres/2+4);
    setPixel(grid,xres/2+4,yres/2+5);
    
    setPixel(grid,xres/2+5,yres/2+2);
    setPixel(grid,xres/2+5,yres/2+3);
    setPixel(grid,xres/2+6,yres/2+2);
    setPixel(grid,xres/2+6,yres/2+3);
    
    setPixel(grid,xres/2+7,yres/2);
    setPixel(grid,xres/2+8,yres/2);
    setPixel(grid,xres/2+7,yres/2+1);
    setPixel(grid,xres/2+8,yres/2+1);
    
    setPixel(grid,xres/2+9,yres/2);
    setPixel(grid,xres/2+10,yres/2);
    setPixel(grid,xres/2+9,yres/2+1);
    setPixel(grid,xres/2+10,yres/2+1);
    
	//Draw horizon
	plotLine(xres/2+13,yres/2,xres/2+33,yres/2,grid);
    plotLine(xres/2+13,yres/2+1,xres/2+33,yres/2,grid);
	
	//Draw positive steps
    
    //Draw negative steps
}

