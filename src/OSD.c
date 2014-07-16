
#include <stdint.h>
#include <stdlib.h>

#include "Config.h"
#include "OSD.h"

void updateOSD(int8_t grid[][yres]) {
    
    //Display craft attitude information
    drawAttitude(grid);
}

void drawAttitude(int8_t grid[][yres]) {
    
    //Draw craft center
    setPixel(grid,xres/2,yres/2);
    setPixel(grid,xres/2+1,yres/2);
    setPixel(grid,xres/2,yres/2+1);
    setPixel(grid,xres/2+1,yres/2+1);
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

//http://members.chello.at/~easyfilter/bresenham.html
void plotLine(int x0, int y0, int x1, int y1,int8_t grid[][yres])
{
   int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1; 
   int err = dx+dy, e2; /* error value e_xy */
 
   for(;;){  /* loop */
      setPixel(grid, x0,y0);
      if (x0==x1 && y0==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   }
}

void setPixel(int8_t grid[][yres], int x, int y) {
    //TODO: set pixel colour
	grid[x][y]=1;
}