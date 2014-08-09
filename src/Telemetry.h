#ifndef TELEMETRY_H_
#define TELEMETRY_H_


struct Attitude {
    int16_t pitch;
    int16_t roll;
    int16_t yaw;
};

struct Position {
  int16_t heading;

};

struct Battery {
    uint8_t voltage;
    uint8_t amperage;
};

struct TelemetryData {
    struct Attitude attitude;
    struct Position position;
    struct Battery battery;
    int x;
};

void zeroData(struct TelemetryData *telemetryData);


#endif /* TELEMETRY_H_ */
