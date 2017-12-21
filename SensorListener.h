#ifndef _SENSOR_LISTENER_H
#define _SENSOR_LISTENER_H

#include <stdio.h>
#include "sensors.h"


class SensorListener{
public:
    void onMultiSensorChanged(sensors_event_t *events, sensors_event_t *accData, sensors_event_t *gyroData, sensors_event_t *magData, int nEvents);
};



#endif