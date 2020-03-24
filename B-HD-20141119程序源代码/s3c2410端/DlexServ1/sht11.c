#include "sht11.h"

#include"intruder.h"
static char sedvalue[256];
void calc_sht11(float *p_humidity,float *p_temprature)
{
   const float C1=-0.40;//针对于12为测量精度
   const float C2=0.0405;
   const float C3=-0.0000028;
   const float T1=0.01;//相对湿度的温度补偿
   const float T2=0.00008;

   float rh=*p_humidity;
   float t=*p_temprature;
   float rh_lin;
   float rh_true;
   float t_C;

   t_C=t*0.01-40;//温度值（14为测量数据精度时）
   rh_lin=C3*rh*rh+C2*rh+C1;//临时湿度值
   rh_true=(t_C-25)*(T1+T2*rh)+rh_lin;//修正后的湿度值
   if(rh_true>100)rh_true=100;
   if(rh_true<0.1)rh_true=0.1;

   *p_temprature=t_C;
   *p_humidity=rh_true;
}

float calc_dewpoint(float h,float t)//空气的露点值
{
   float k,dew_point;
   k=(log10(h)-2)/0.4343+(17.62*t)/(243.12+t);
   dew_point=243.12*k/(17.62-k);
   return dew_point;
}

char *get_temphumi()
{
	int fd,shtret,i;
    	unsigned int value_t=0;
        unsigned int value_h=0;
        float fvalue_t,fvalue_h;
        float dew_point;
		char *blk=" $ ";
		char str1[50];
		char str2[50];
		char str3[50];
	fd = open("/dev/sht11",0);

	if(fd<0)
	{
		printf("open /dev/sht11 error!\n");
		
	}
 
                fvalue_t=0.0,fvalue_h=0.0;value_t=0;value_h=0;
		ioctl(fd,0);
		shtret=read(fd,&value_t,sizeof(value_t));
                if(shtret<0)
		{
			printf("read err!\n");
			
		}
		
                value_t=value_t&0x3fff;//温度：14位测量数据
                //printf("value_t=%d\n",value_t);
                fvalue_t=(float)value_t;

                ioctl(fd,1);
		shtret=read(fd,&value_h,sizeof(value_h));
               // printf("value_h=%d\n",value_h);
                sleep(1);
		if(shtret<0)
		{
			printf("read err!\n");
			
		}
                value_h=value_h&0xfff;//湿度：12位测量数据
                fvalue_h=(float)value_h;
                calc_sht11(&fvalue_h,&fvalue_t);//将输出转换为物理量
                dew_point=calc_dewpoint(fvalue_h,fvalue_t);//空气的露点值
				sprintf(str1,"%f",fvalue_t);
		sprintf(str2,"%f",fvalue_h);
		sprintf(str3,"%f",dew_point);
		memset(sedvalue,0,sizeof(sedvalue));
		strcpy(sedvalue,str1);
		strcat(sedvalue,blk);
		strcat(sedvalue,str2);
		strcat(sedvalue,blk);
		strcat(sedvalue,str3);
		strcat(sedvalue,blk);
		if(intruder==false){ strcat(sedvalue,"0");}
			else{ strcat(sedvalue,"1");intruder=false;}
		strcat(sedvalue,blk);
		if(smog_value==false){ strcat(sedvalue,"0");}
                        else{ strcat(sedvalue,"1");smog_value=false;}
		char count1[50];
		sprintf(count1,"%d",count);
		strcat(sedvalue,blk);
		strcat(sedvalue,count1);
		
		close(fd);
		return sedvalue;
                //printf("temp:%fc humi:%f dew point:%fc\n",fvalue_t,fvalue_h,dew_point);
}
