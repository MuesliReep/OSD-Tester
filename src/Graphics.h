#ifndef GRAPHICS_H_
#define GRAPHICS_H_

void initialiseGraphics();
void drawLine(int x, int y, int thickness, int angle, int length, int8_t grid[][yres]);
void drawPoint(int x, int y, int thickness,int8_t grid[][yres]);
void drawCharacter(int x, int y, int size, int character, int8_t grid[][yres]);
void drawString(int posX, int posY, int size, char text[], int length, int8_t grid[][yres]);
void plotLine(int x0, int y0, int x1, int y1,int8_t grid[][yres]);
void plotCircle(int xm, int ym, int r,int8_t grid[][yres]);
void setPixel(int8_t grid[][yres], int x, int y);
void calcTriangleSides(int * A, int * B, int * C, int * AB, int * AC, int * BC);

#endif /* GRAPHICS_H_ */
