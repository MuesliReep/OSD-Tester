#ifndef OUTPUT_H_
#define OUTPUT_H_

int outputGridToDisplay(int8_t grid[][yres]);
int outputInitialise(int device);
int outputDestroy();

int outputToWindow(int8_t grid[][yres]);
void outputToConsole(int8_t grid[][yres]);

#endif /* OUTPUT_H_ */
