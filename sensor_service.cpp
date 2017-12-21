#include "sensor_service.h"
#include <stdio.h>

SensorSerivce::SensorSerivce(int *channels, int nChannel) 
    : mCurrNanosec(0), mNumberOfChannels(nChannel), mCurrentChannelIndex(0) {
    mChannels = channels;
}

void SensorSerivce::do_service(){
    // add multiAccData, multiGyroData 2017.12.01 by lixuxian
    store_multiple_euler_angles(multiEulerAngles, multiAccData, multiGyroData, multiMagData, mChannels, mNumberOfChannels);
    mListener.onMultiSensorChanged(multiEulerAngles, multiAccData, multiGyroData, multiMagData, mNumberOfChannels);
}

void SensorSerivce::start_service(nsecs_t nanoseconds){

    nsecs_t local_nanosec = 0;

    while(1){
        local_nanosec = systemTime();
        if( local_nanosec - mCurrNanosec >= nanoseconds ){
            do_service();
            mCurrNanosec = local_nanosec;
        }
    }
}
