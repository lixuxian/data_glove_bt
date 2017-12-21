#include <wiringSerial.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "bt_recv.h"
using namespace std;

char recv_buf[1024];

char* recv_bt(){
	int fd;
	const char* device = "/dev/rfcomm1";
    if ((fd=serialOpen(device, 1000000)) < 0) {
            printf("serial doesn't open");
            exit(1);
    }
    int n = read(fd, recv_buf, 1024);
    return recv_buf;
}
