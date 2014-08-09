
#include <stdint.h>
#include <stdlib.h>

#include "Config.h"
#include "Telemetry.h"

void zeroData(struct TelemetryData *telemetryData) {
    //Zero all data structs
	telemetryData->x = 0;

    //Zero attitude data
		telemetryData->attitude.pitch	= 0;
    telemetryData->attitude.roll	= 45;
    telemetryData->attitude.yaw		= 0;

    //Zero Position data
		telemetryData->position.heading	= 0;

		//Zero Battery data
		telemetryData->battery.voltage 	= 127;
		telemetryData->battery.amperage = 40;
}
