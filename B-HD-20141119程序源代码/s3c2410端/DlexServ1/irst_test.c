#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include"gpio_test.h"
#include"intruder.h"
int irst()
{
    int i;
    int ret;
    int fd;
    int irst_cnt;
    
    fd = open("/dev/irst", 0);  
    if (fd < 0) {
        printf("Can't open /dev/irst\n");
        return -1;
    }

    while (1) {
        ret = read(fd,&irst_cnt, sizeof(irst_cnt));
        if (ret < 0) {
            printf("read err!\n");
		intruder=false;
            continue;
        }
        if (irst_cnt)
	{
            //printf("have signal!\n");
		intruder=true;
		gpio(1);sleep(1);
	}
	else
		intruder=false;
	
    }
   close(fd);
    return 0;
}

