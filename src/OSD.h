#ifndef OSD_H_
#define OSD_H_

void updateOSD(int8_t grid[][yres], struct TelemetryData * data);
void drawAttitude(int8_t grid[][yres], struct Attitude * attitude);
void plotLine(int x0, int y0, int x1, int y1,int8_t grid[][yres]);
void setPixel(int8_t grid[][yres],int x, int y);

#endif /* OSD_H_ */