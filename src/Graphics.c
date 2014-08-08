#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "Config.h"
#include "Graphics.h"
#include "Font.h"

#define PI 3.14159265

void initialiseGraphics() {
    //Do font init here
}

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
}

void drawCharacter(int cenX, int cenY, int size, int character, int8_t grid[][yres]) {
    //Non-rotated character

    character -= 32; //Font array starts at ASCII 32

    //Find character in array, if width not zero continue

    //Find number of vertices
    int vertices = font_simplex[character][0];

    int x =2; //Font array starting position
    //Initialise pen position
    int charX, posX = font_simplex[character][x];
    int charY, posY = font_simplex[character][x+1];
    while (vertices > 0) {

        charX = font_simplex[character][x];
        charY = font_simplex[character][x+1];

        if(charX == -1 && charY == -1) { //Pen up

          //Move pen to new position
          posX = font_simplex[character][x+2];
          posY = font_simplex[character][x+3];
          x += 2;
          continue;
        }

        //Check if we need to plot a line
        int nextX = font_simplex[character][x+2];
        int nextY = font_simplex[character][x+3];

        if(nextX == -1 && nextY == -1) {
          x+=2;
          continue;
        }

        //Plot the line
        plotLine(cenX+posX,cenY-posY,cenX+nextX,cenY-nextY,grid);

        //Set this vertex to complete
        vertices--;

        //Move pen to new position
        posX = nextX; posY = nextY;
        x+=2;

    }
}

void drawString(int posX, int posY, int size, char text[], int length, int8_t grid[][yres]) {
    //Non rotated string

    int previousCharWidth = -1;
    int currentCharWidth;

    for (int i=0;i<length;i++) {

        //Convert char to ascii code
        int asciiChar = (int)text[i];

        //Find the current characters width
        currentCharWidth = font_simplex[asciiChar-32][2];

        //Check if this is the first character to be drawn
        if(previousCharWidth == -1) {
            previousCharWidth = currentCharWidth;

            drawCharacter(posX,posY,size,asciiChar,grid);
            continue;
        }

        //Find characters position
        posX += previousCharWidth /2 + currentCharWidth /2;

        drawCharacter(posX,posY,size,asciiChar,grid);
    }
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

void plotCircle(int xm, int ym, int r,int8_t grid[][yres]) {

   int x = -r, y = 0, err = 2-2*r; /* II. Quadrant */
   do {
      setPixel(grid,xm-x, ym+y); /*   I. Quadrant */
      setPixel(grid,xm-y, ym-x); /*  II. Quadrant */
      setPixel(grid,xm+x, ym-y); /* III. Quadrant */
      setPixel(grid,xm+y, ym+x); /*  IV. Quadrant */
      r = err;
      if (r <= y) err += ++y*2+1;           /* e_xy+e_y < 0 */
      if (r > x || err > y) err += ++x*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
   } while (x < 0);
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
