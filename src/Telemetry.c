
#include <stdint.h>
#include <stdlib.h>

#include "Config.h"
#include "Telemetry.h"

void zeroData(struct TelemetryData *telemetryData) {
    //Zero all data structs
	telemetryData->x = 0;

    //Zero attitude data
		telemetryData->attitude.pitch	= 10;
    telemetryData->attitude.roll	= 30;
    telemetryData->attitude.yaw		= 0;

    //Zero Position data
		telemetryData->position.heading		= 0;
		telemetryData->position.latitude 	= 52080414; //52.080414
		telemetryData->position.longitude	= 4324862; //4.324862

		//Zero Battery data
		telemetryData->battery.voltage 	= 127;
		telemetryData->battery.amperage = 40;
}
