#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "intruder.h"

#define IOCTL_LED_ON    0
#define IOCTL_LED_OFF   1
#define IOCTL_BUZZER_OFF  3
#define IOCTL_BUZZER_ON   4

void gpio(int i)
{
    unsigned int led;
    unsigned int puzzer;
    int fd = -1;//printf("get");
	//if(intruder==false) printf("0");
	//else printf("1");
    fd = open("/dev/gpio", 0);  
    if (fd < 0) {
        printf("Can't open /dev/gpio\n");
        close(fd);
    }
   switch(i)
	{
	case 1:printf("on");
	ioctl(fd,IOCTL_LED_ON);ioctl(fd,IOCTL_BUZZER_ON);  // 此时灯亮，且蜂鸣器响
	sleep(1);break;
	defaul:
	printf("no");
	ioctl(fd,IOCTL_LED_OFF);
        ioctl(fd,IOCTL_BUZZER_OFF);
	}
	        ioctl(fd,IOCTL_LED_OFF);
        ioctl(fd,IOCTL_BUZZER_OFF);

    close(fd);
}

