#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringSerial.h>
#include <string>
#include "bt_send.h"
using namespace std;
// mpu_num-->gear_num: 9-->4, 0-->5, 1-->6, 3-->17, 5-->18, 7-->19
// int mpu_num[6] = {9, 0, 1, 3, 5, 7};
// int gear_num[6] = {4, 5, 6, 17, 18, 19};

// update 2017.12.21
// mpu_num-->gear_num: 14-->4, 0-->5, 3-->6, 6-->17, 9-->18, 12-->19
// int mpu_num[6] = {14, 0, 4, 6, 9, 12}
// int gear_num[6] = {4, 5, 6, 17, 18, 19}

int send_bt(sensors_event_t *events, int n_channels){  
        char* instruction = data_process(events, n_channels);
        printf("instruction: %s\n", instruction);
        int fd;
        if ((fd=serialOpen("/dev/rfcomm0", 115200)) < 0) {
                printf("serial doesn't open");
                return 1;
        }
        serialPrintf(fd, instruction);
        // serialClose(fd);
	return 0;
}

char inst[130];

char* data_process(sensors_event_t *events, int n_channels) {
        // data = "0#1,2,3;1#4,5,6;3#6,3,2;"
        // instruction = "004P1000T300!005P1000T300!"
        string instruction = "";

        int mpu_num[6] = {14, 0, 3, 6, 9, 12};
        int gear_num[6] = {4, 5, 6, 17, 18, 19};
        int rotate_angles[6] = {0, 0, 0, 0, 0, 0};

        sensors_event_t *event;
        sensors_event_t *parent_event;
        int i = 0;
        for(; i < 6; i++) { 
                //* create gears rotate angles *****//
                if (mpu_num[i] == 14) {
                        // pitch           
                        event = events + mpu_num[i];           
                        rotate_angles[i] = event->data[1];
                }
                else {
                        event = events + mpu_num[i];
                        parent_event = events + mpu_num[i+1];
                        rotate_angles[i] = event->data[2] - parent_event->data[2];
                        if (gear_num[i] == 18 || gear_num[i] == 19) { // special, fan le
                                rotate_angles [i] = 180 - rotate_angles[i];
                        }
                }
                //********************//

                //**** create instruction *****//
                if (rotate_angles[i] >=0 && rotate_angles[i] <= 180) {
                        int pwm_ms;
                        if (gear_num[i] == 18 || gear_num[i] == 19) {
                                pwm_ms = int(rotate_angles[i] / 180.0 * 2000) + 100;
                        }
                        else {
                                pwm_ms = int(rotate_angles[i] / 180.0 * 2000) + 500;
                        }

                        char num[3];
                        char pwm[8];    
                        sprintf(pwm, "%d", pwm_ms);
                        string str1;
                        string str2;
                        if (gear_num[i] < 10) {
                                sprintf(num, "%d", gear_num[i]);
                                str1 = num;
                                str2 = pwm;
                                instruction += "#00" + str1 + "P" + str2 + "T100!";
                        }
                        else {
                                sprintf(num, "%d", gear_num[i]);
                                str1 = num;
                                str2 = pwm;
                                instruction += "#0" + str1 + "P" + str2 + "T100!";
                        }
                }
                
        }
        // cout << "instruction:" << instruction << endl;
        strcpy(inst, instruction.c_str());
        return inst;
}
