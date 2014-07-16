#ifndef GRAPHICS_H_
#define GRAPHICS_H_

void drawLine(int x, int y, int thickness, int angle, int8_t grid[][yres]);
void drawPoint(int x, int y, int thickness,int8_t grid[][yres]);
void plotLine(int x0, int y0, int x1, int y1,int8_t grid[][yres]);
void setPixel(int8_t grid[][yres], int x, int y);

#endif /* GRAPHICS_H_ */