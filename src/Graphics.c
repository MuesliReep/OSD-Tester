#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "Config.h"
#include "Graphics.h"

#define PI 3.14159265

void drawLine(int x, int y, int thickness, int angle, int length, int8_t grid[][yres]){
    //Calculate end points according to the angle and length. (Right angled triangle)
    //
    if(x<0 || y <0 || x > xres || y > yres)
      return;
    
    int A = 0;
    int B = 0;
    int C = length;
    int AB = 90;
    int AC = 180-AB-angle;
    int BC = angle;
    
    calcTriangleSides(&A,&B,&C,&AB,&AC,&BC);

    plotLine(x,y,x+B,y-A,grid);
    
    //TODO: line thickness
    
}

void drawPoint(int x, int y, int thickness,int8_t grid[][yres]) {
    
  if(x<0 || y <0 || x > xres || y > yres)
      return;
    
    for(int ix=x;ix<x+thickness;ix++) {
        for(int iy=y;iy<y+thickness;iy++) {
            setPixel(grid,ix,iy);
        }
    }
    //TODO: out of bounds catch
}

//http://members.chello.at/~easyfilter/bresenham.html
void plotLine(int x0, int y0, int x1, int y1,int8_t grid[][yres]) {
    
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

//Calculate two sides of a right angled traingle given one length and one angle
void calcTriangleSides(int * A, int * B, int * C, int * AB, int * AC, int * BC) {
    //A = overstaand, B = aanliggende, C = schuine
    
    // Sin(BC) = A / C
    float sinBC = sinf((float)*BC*PI/180);
    *A = *C * sinBC;
    
    // Cos(BC) = B / C
  float cosBC = cosf((float)*BC*PI/180);
    *B = *C * cosBC;
    
    //soscastoa hier
    //http://www.wiskunde.net/sinus#.U9OZQ_l_uxb
    //http://wetenschap.infonu.nl/wiskunde/84556-de-lengte-van-een-zijde-van-een-driehoek-berekenen.html
}
