#include <wiringSerial.h>
#include <unistd.h>
#include <stdlib.h>
#include "bt_recv.h"
using namespace std;

char* recv_bt(){
	int fd;
	char* device = "/dev/rfcomm1";
    if ((fd=serialOpen(device, 1384000)) < 0) {
            printf("serial doesn't open");
            exit(1);
    }

    int buf_size = 1024;
	char recv_buf[buf_size];
    int n = read(fd, recv_buf, buf_size);

    return recv_buf;
}