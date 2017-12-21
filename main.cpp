#include "sensor_service.h"

nsecs_t hzToNanosecs(int hz){
    return (nsecs_t)(1.0f / hz * 1000000000);
}

int main(int argc, char const *argv[])
{
    int channels[] ={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    int nChannel = 15;

    SensorSerivce service(channels, nChannel);
    // service.open_device(); // delete 2017.12.21
    service.start_service(hzToNanosecs(100));
    
    return 0;
}
