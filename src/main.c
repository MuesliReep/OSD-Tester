#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Config.h"
#include "Telemetry.h"
#include "output.h"
#include "ArrayHelper.h"
#include "DataStream.h"
#include "OSD.h"



int8_t displayGrid[xres][yres];

int main() {

		//Initialise array
    clearArray(displayGrid,sizeof(displayGrid));

    //Initialise devices
    outputInitialise(1);
    dataStreamInitialise(1);

    //Initialise data
    struct TelemetryData telemetryData;
    zeroData(&telemetryData);


    //Grab latest data & convert it to TelemetryData


    //OSD
		updateOSD(displayGrid, &telemetryData);

		//Display OSD to display device
    outputGridToDisplay(displayGrid);

    //Cleanup
		outputDestroy();

    //Say goodbye
    printf("Have a nice day!\n");

    return 0;
}
