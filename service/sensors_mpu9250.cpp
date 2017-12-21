/*different chip need to impliments the sensors interface*/
#include "sensors.h"
#include "AHRS.h"
#include "StringOp.h"
#include "bt_recv.h"
#include <stdio.h>
#include <stdlib.h>

AHRS  g_ahrs[N_SENSORS];

status_t store_multiple_euler_angles(sensors_event_t *euler, sensors_event_t *acc, sensors_event_t *gyro, sensors_event_t *mag, int *channels, int n_channels){
    // receive FPGA data by serial bluetooth 2017/12/14 by lixuxian
    // string data = recv_bt();
    string data = "-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513,-0.0302734,0.946289,-0.305176,0,-0.0106526,0.00106526,-0.214234,-0.199178,-0.189513";
    vector<string> v;
    string sep = ",";
    splitString(data, v, sep); // length = 9 * 15
    for (int i=0; i < n_channels; i++){
        acc[i].channel = channels[i];
        acc[i].data[0] = stringToFloat(v[i*9 + 0]);
        acc[i].data[1] = stringToFloat(v[i*9 + 1]);
        acc[i].data[2] = stringToFloat(v[i*9 + 2]);
        acc[i].timestamp = systemTime();
        acc[i].type = SENSOR_TYPE_ACCELEROMETER;

        gyro[i].channel = channels[i];
        gyro[i].data[0] = stringToFloat(v[i*9 + 3]);
        gyro[i].data[1] = stringToFloat(v[i*9 + 4]);
        gyro[i].data[2] = stringToFloat(v[i*9 + 5]);
        gyro[i].timestamp = systemTime();
        gyro[i].type = SENSOR_TYPE_GYROSCOPE;

        mag[i].channel = channels[i];
        mag[i].data[0] = stringToFloat(v[i*9 + 6]);
        mag[i].data[1] = stringToFloat(v[i*9 + 7]);
        mag[i].data[2] = stringToFloat(v[i*9 + 8]);
        mag[i].timestamp = systemTime();
        mag[i].type = SENSOR_TYPE_MAGNETIC_FIELD;

        euler[i].channel = channels[i];
        euler[i].type = SENSOR_TYPE_EULER_ANGLE;
        g_ahrs[channels[i]].MahonyUpdate(acc[i].data, gyro[i].data, mag[i].data, mag[i].timestamp);
        g_ahrs[channels[i]].buildEulerAngles(&(euler[i].data[0]), &(euler[i].data[1]), &(euler[i].data[2]));
    }

    return OK;
}

