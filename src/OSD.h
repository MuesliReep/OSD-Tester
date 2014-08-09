#ifndef OSD_H_
#define OSD_H_

void updateOSD(int8_t grid[][yres], struct TelemetryData * data);
void drawAttitude(int8_t grid[][yres], struct Attitude * attitude);
void drawCompassRadar(int8_t grid[][yres], struct Position * position);
void drawBatteryInfo(int8_t grid[][yres], struct Battery * battery)

#endif /* OSD_H_ */
