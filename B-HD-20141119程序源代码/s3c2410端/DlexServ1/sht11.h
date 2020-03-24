#ifndef SHT11_H
#define SHT11_H

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define TEMP 0
#define HUMI 1

void calc_sht11(float *p_humidity,float *p_temprature);
float calc_dewpoint(float h,float t);//空气的露点值
char *get_temphumi();
#endif /* SHT11_H*/
