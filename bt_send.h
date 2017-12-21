#ifndef _BT_SEND_
#define _BT_SEND_

#include "sensors.h"

int send_bt(sensors_event_t *events, int n_channels);
char* data_process(sensors_event_t *events, int n_channels);
#endif
