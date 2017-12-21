#include "SensorListener.h"
#include "data_sender.h"
#include "data_dumper.h"
#include "utils/timers.h"
#include "bt_send.h"
#include <stdio.h>
#include <sstream>
#include <string>
#include <string.h>
using namespace std;

char sensor_data_string[1024];

// add accData and gyroData by lixuxian 2017.12.07
char imu_data_string[2048]; 
void SensorListener::onMultiSensorChanged(sensors_event_t *events, sensors_event_t *accData, sensors_event_t *gyroData, sensors_event_t *magData, int nEvents){
    stringstream ss;
    stringstream imu;
    string sensor_data;
    string imu_data;
    sensors_event_t *event; // this is euler angles
    sensors_event_t *acc; // add ccc
    sensors_event_t *gyro; // add gyro
    sensors_event_t *mag; // add mag
    int i = 0;
    for(; i<nEvents; i++){
        event = events+i;
        acc = accData + i;
        gyro = gyroData + i;
        mag = magData + i;
        ss<< event->channel << "#" 
            << event->data[0] << "," << event->data[1] << "," << event->data[2] << ";";
        imu << event->channel << "#"
            << acc->data[0] << "," << acc->data[1] << "," << acc->data[2] << ","
            << gyro->data[0] << "," << gyro->data[1] << "," << gyro->data[2] <<  ","
            << mag->data[0] << "," << mag->data[1] << "," << mag->data[2] << ";";            
    }

    ss >> sensor_data;
    const int len = sensor_data.length();
    strncpy(sensor_data_string, sensor_data.c_str(), len);
    sensor_data_string[len] = '\0';
    send(sensor_data_string);
    // send_bt(events, nEvents);
    dump("data/data_dumper_test.txt", sensor_data_string); //add by lixuxian 2017/06/27

    // dump acc, gyro, mag to imu_data.txt
    imu >> imu_data;
    const int imu_data_len = imu_data.length();
    strncpy(imu_data_string, imu_data.c_str(), imu_data_len);
    imu_data_string[imu_data_len] = '\0';
    dump("data/imu_data.txt", imu_data_string);
} 
