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
    //For future use
}

void drawLine(int x, int y, int thickness, int angle, int length, int8_t grid[][yres]){
    //Calculate end points according to the angle and length. (Right angled triangle)
    //
    if(x<0 || y <0 || x > xres-1 || y > yres-1)
      return;

    float A = 0.0;
    float B = 0.0;
    float C = length;
    float AB = 90.0;
    float AC = 180.0-AB-angle;
    float BC = angle;

    calcTriangleSides_float(&A,&B,&C,&AB,&AC,&BC);

    plotLine(x,y,x+round_int(B),y-round_int(A),grid);

    //TODO: line thickness

}

void drawPoint(int x, int y, int thickness,int8_t grid[][yres]) {

  if(x<0 || y <0 || x > xres-1 || y > yres-1)
      return;

    for(int ix=x;ix<x+thickness;ix++) {
        for(int iy=y;iy<y+thickness;iy++) {
            setPixel(grid,ix,iy);
        }
    }
}

void drawCharacter(int cenX, int cenY, int size, int rotation, int character, int8_t grid[][yres]) {

    if(cenX<0 || cenY <0 || cenX > xres-1 || cenY > yres-1)
        return;

    character -= 32; //Font array starts at ASCII 32

    //Calculate the size multiplier, used during drawing
    float sizeMX = 1.0;
    sizeMX = (float)size / 10.0;

    //Find number of vertices
    int vertices = font_simplex[character][0];

    int x =2; //Font array starting position

    //Initialise pen position
    int pointX, nextX, penX = font_simplex[character][x];
    int pointY, nextY, penY = font_simplex[character][x+1];

    int nextXR, penXR; // Used to store points during rotation
    int nextYR, penYR;

    while (vertices > 0) {

        pointX = font_simplex[character][x];
        pointY = font_simplex[character][x+1];

        if(pointX == -1 && pointY == -1) {
          //If pen up operation, move pen to new position

          penX = font_simplex[character][x+2];
          penY = font_simplex[character][x+3];
          x += 2;
          vertices--;  //Pen up also counts as a vertex
          continue;
        }

        //Get the next position in the array to determine next action
        nextX = font_simplex[character][x+2];
        nextY = font_simplex[character][x+3];

        //If the next action is a pen up operation skip this loop
        if(nextX == -1 && nextY == -1) {
          x+=2;
          continue;
        }

        //If necessary rotate the vertex points around the characters center point
        if(rotation != 0) {

            //First calculate the angle and distance of the first vertex coordinate from the center

            float A = penX;
            float B = penY;
            float C = 0.0;
            float AB = 90.0;
            float AC = 0.0;
            float BC = 0.0;

            calcTriangleAngle_float(&A,&B,&C,&AB,&AC,&BC);

            float length  = C*sizeMX; //Set the length and scale it according to font size
            float angle   = BC+rotation;

            //Now rotate the first vertex coordinate around the center

            A = 0.0;
            B = 0.0;
            C = length;
            AB = 90.0;
            AC = 180.0-AB-angle;
            BC = angle;

            calcTriangleSides_float(&A,&B,&C,&AB,&AC,&BC);

            penXR = round_int(A);
            penYR = round_int(B);

            //Calculate the angle and distance of the second vertex coordinate from the center

            A = nextX;
            B = nextY;
            C = 0.0;
            AB = 90.0;
            AC = 0.0;
            BC = 0.0;

            calcTriangleAngle_float(&A,&B,&C,&AB,&AC,&BC);

            length  = C*sizeMX;  //Set the length and scale it according to font size
            angle   = BC+rotation;

            //Finally; rotate the second vertex coordinate around the center

            A = 0.0;
            B = 0.0;
            C = length;
            AB = 90.0;
            AC = 180.0-AB-angle;
            BC = angle;

            calcTriangleSides_float(&A,&B,&C,&AB,&AC,&BC);

            nextXR = round_int(A);
            nextYR = round_int(B);

        }

        //Draw the vertex
        if(rotation != 0)
          plotLine(cenX+penXR,cenY-penYR,cenX+nextXR,cenY-nextYR,grid);
        else
          plotLine(cenX+(float)penX*sizeMX,cenY-(float)penY*sizeMX,cenX+(float)nextX*sizeMX,cenY-(float)nextY*sizeMX,grid);

        //Set this vertex to complete
        vertices--;

        //Move the pen to it's new position
        penX = nextX;
        penY = nextY;

        x+=2;
    }
}

void drawString(int posX, int posY, int size, int rotation, char text[], int length, int8_t grid[][yres]) {

    if(posX<0 || posY <0 || posX > xres-1 || posY > yres-1)
      return;

    int previousCharWidth = -1;
    int currentCharWidth;

    for (int i=0;i<length;i++) {

        //Convert char to ascii code
        int asciiChar = (int)text[i];

        //Calculate font size multiplier
        float sizeMX = 1.0;
        sizeMX = (float)size / 10.0;

        //Find the current characters width (with font sizing)
        currentCharWidth = font_simplex[asciiChar-32][1] * sizeMX;

        //currentCharWidth = font_simplex[asciiChar-32][1];

        //Check if this is the first character to be drawn
        if(previousCharWidth == -1) {
            previousCharWidth = currentCharWidth;

            drawCharacter(posX,posY,size,rotation,asciiChar,grid);
            continue;
        }

        //Find characters position

        int characterDistance = previousCharWidth /2 + currentCharWidth /2;

        if(rotation == 0)
          posX += characterDistance;
        else { //Rotated

            float A = 0;
            float B = 0;
            float C = characterDistance;
            float AB = 90;
            float AC = 180-AB-rotation;
            float BC = rotation;

            calcTriangleSides_float(&A,&B,&C,&AB,&AC,&BC);

            posX += A;
            posY += B;
        }

        //TODO: character spacing

        drawCharacter(posX,posY,size,rotation,asciiChar,grid);
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

//Plots a circle
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

//Sets the pixel value for a given x & y coordinate
void setPixel(int8_t grid[][yres], int x, int y) {

    if(x<0 || y <0 || x > xres-1 || y > yres-1)
        return;

    //TODO: set pixel colour
    grid[x][y]=1;
}

//Calculate two sides of a right angled traingle given one length and one angle
void calcTriangleSides_float(float * A, float * B, float * C, float * AB, float * AC, float * BC) {
    //A = overstaand, B = aanliggende, C = schuine

    // Sin(BC) = A / C
    float sinBC = sinf(*BC*PI/180.0);
    *A = *C * sinBC ;

    // Cos(BC) = B / C
    float cosBC = cosf((float)*BC*PI/180.0);
    *B = *C * cosBC ;

    //soscastoa
    //http://www.wiskunde.net/sinus#.U9OZQ_l_uxb
    //http://wetenschap.infonu.nl/wiskunde/84556-de-lengte-van-een-zijde-van-een-driehoek-berekenen.html
}

//Calculate two sides of a right angled traingle given one length and one angle
void calcTriangleSides_int(int * A, int * B, int * C, int * AB, int * AC, int * BC) {
    //A = overstaand, B = aanliggende, C = schuine

    // Sin(BC) = A / C
    float sinBC = sinf((float)*BC*PI/180);
    *A = *C * sinBC;

    // Cos(BC) = B / C
    float cosBC = cosf((float)*BC*PI/180);
    *B = *C * cosBC;
}

void calcTriangleAngle_float(float * A, float * B, float * C, float * AB, float * AC, float * BC) {
    //TODO: merge this function with calcTriangleSides_float

    //First calculate the angle of BC

    // Tan(BC) = A / B
    float tanBC = *A / *B;
    *BC = atan(tanBC) * 180.0 / PI;

    //Then calculate the length of C

    // A^2 + B^2 = C^2
    *C = sqrt( pow(*A,2.0) + pow(*B,2.0) );

    *AC = 180.0 - *AB - *BC;
}

int round_int( float r ) {
    return (r > 0.0) ? (r + 0.5) : (r - 0.5);
}
