

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/types.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/time.h>
#include <limits.h>

void exit_fatal(char *messages)
{
	printf("%s \n",messages);
	exit(1);
}

double
ms_time (void)
{
  static struct timeval tod;
  gettimeofday (&tod, NULL);
  return ((double) tod.tv_sec * 1000.0 + (double) tod.tv_usec / 1000.0);

}

int
get_jpegsize (unsigned char *buf, int insize)
{
 int i; 	
 for ( i= 1024 ; i< insize; i++) {
 	if ((buf[i] == 0xFF) && (buf[i+1] == 0xD9)) return i+10;
 }
 return -1;
}
