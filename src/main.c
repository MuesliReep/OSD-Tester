#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Config.h"
#include "output.h"
#include "ArrayHelper.h"
#include "OSD.h"


int8_t displayGrid[xres][yres];

int main() {
	
    //Initialise array
    clearArray(displayGrid,sizeof(displayGrid));
    
    //Initialise output device
    outputInitialise(1);

    //OSD
	updateOSD(displayGrid);

	//Display OSD to display device    
    outputGridToDisplay(displayGrid);
    
    //Cleanup
	outputDestroy();
    
    //Say goodbye
    printf("Have a nice day!\n");
    
    return 0;
}