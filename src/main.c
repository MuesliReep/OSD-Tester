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

		int run = -1;
		while(run == -1) {

	    //Grab latest data & convert it to TelemetryData
			processStream(&telemetryData);

	    //OSD
			updateOSD(displayGrid, &telemetryData);

			//Display OSD to display device
	    run = outputGridToDisplay(displayGrid);

			//Clear the output array
			clearArray(displayGrid,sizeof(displayGrid));
		}

    //Cleanup
		outputDestroy();

    //Say goodbye
    printf("Have a nice day!\n");

    return 0;
}
