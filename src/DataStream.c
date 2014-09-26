//Gets the telemetry data from the data stream either self generated or from another source(eg Serial)

#include <stdint.h>

#include "Telemetry.h"

//Device: 	0 = static, centered data
//			1 = serial
//			2 = randomly generated
int dataStreamInitialise(int device) {

    return 0;
}

int rollModifier = 1;
int pitchModifier = 1;

int processStream(struct TelemetryData *data) {
    //TODO: Differentiate between serial and random data

    data->attitude.roll += rollModifier;
    data->attitude.pitch += pitchModifier;

    if(data->attitude.roll > 44)
      rollModifier = -1;
    else if(data->attitude.roll < -44)
      rollModifier = 1;

    if(data->attitude.pitch > 44)
      pitchModifier = -1;
    else if(data->attitude.pitch < -44)
      pitchModifier = 1;

    data->position.latitude++;

    data->position.heading++;
    if(data->position.heading>360)
      data->position.heading = 0;

    return 0;
}
