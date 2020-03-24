/************************************************\
*	by threewater<threewater@up-tech.com>	*
*		2004.06.18			*
*						*
\***********************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <fcntl.h>
#include "s3c2410-smog.h"
#include "gpio_test.h"
#include "intruder.h"
#define ADC_DEV  "/dev/adc"
int adc_fd = -1;
void CountPeople();
int init_ADdevice(void)
{
	if((adc_fd=open(ADC_DEV, O_RDWR))<0){
		printf("Error opening %s adc device\n", ADC_DEV);
		return -1;
	}
}

 int GetADresult(int channel)
{
	int PRESCALE=0XFF;
	int data=ADC_WRITE(channel, PRESCALE);
	write(adc_fd, &data, sizeof(data));
	read(adc_fd, &data, sizeof(data));
	return data;
}


/* void* comMonitor(void* data)
{
	getchar();
	stop=1;
	return NULL;
}
*/
void  smog()
{
	int i;
	float d;
	//pthread_t th_com;
	//void * retval;

	//set s3c44b0 AD register and start AD
	if(init_ADdevice()<0)
		exit(0);                                                
	pthread_t th_a;
	pthread_create(&th_a,NULL,(void *)CountPeople,NULL);
	while(1){
		d=0;
		//for(i=0;i<3;i++)
	//	{//d=(float)GetADresult(i);
			d=((float)GetADresult(0)*3.3)/1024.0;
	//	}
			if(d>1)
			{
				gpio(1);smog_value=true;
			}
			sleep(3);
	//		printf("\r");
	}
	/* Wait until producer and consumer finish. */

	
	exit(0);
}
void CountPeople()
{
	int i;
        float d1,d2;
        

	 while(1)
        {
                int a1=0;int a2=0;
                while(a1==0&&a2==0)
                {
                        d1=((float)GetADresult(1)*3.3)/1024.0;
                        d2=((float)GetADresult(2)*3.3)/1024.0;

                        if(d1>2)
                        {
                                while(d2<2)
                                        d2=((float)GetADresult(2)*3.3)/1024.0;
                                a1=1;a2=0;
                        }
                        else
                        {       if(d2>2)
                                {
                                    while(d1<2)
                                         d1=((float)GetADresult(1)*3.3)/1024.0;
                                a1=0;a2=1;
                                }
                                else {a1=0;a2=0;}
			                   }
	                }
                printf("d1=%f   d2= %f   ",d1,d2);

                if(a1==1&&a2==0)
                                count++;
                else            count--;
                if(count<0)     count=0;
                sleep(3);printf("%d",count);    printf("\n");
        //              printf("\r");
        }

}
