#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "spcaframe.h"
#include "spcav4l.h"
#include "sht11.h"
#include "utils.h"
#include "tcputils.h"	
#include "version.h"
#include "intruder.h"
#include "irst_test.h"
#include "s3c2410-smog.h"

static int debug = 0;
void grab (void);
void myservice(void *myir);
void service (void *ir);
void sigchld_handler(int s);
struct vdIn videoIn;


int main (int argc, char *argv[])
{

  char *videodevice = NULL;
  int grabmethod = 1;
  int format = VIDEO_PALETTE_JPEG;
  int width = 640;
  int height = 480;
  char *separateur;
  char *sizestring = NULL;
  int i;
  int serv_sock,new_sock,irst_sock;
  int myserv_sock,mynew_sock,myirst_sock;
  pthread_t w1;
  pthread_t myserver_th;
  pthread_t server_th;
  int sin_size;
  int mysin_size;
  unsigned short serverport = 7070;
  unsigned short myserverport = 7171;
  unsigned short myirstport=7072;
  struct sockaddr_in their_addr;
  struct sockaddr_in mytheir_addr;
  struct sockaddr_in irst_addr;
  struct sigaction sa;
  for (i = 1; i < argc; i++)
    {
      /* skip bad arguments */
      if (argv[i] == NULL || *argv[i] == 0 || *argv[i] != '-')
	{
	  continue;
	}
      if (strcmp (argv[i], "-d") == 0)
	{
	  if (i + 1 >= argc)
	    {
	      if(debug) printf ("No parameter specified with -d, aborting.\n");
	      exit (1);
	    }
	  videodevice = strdup (argv[i + 1]);
	}
      if (strcmp (argv[i], "-g") == 0)
	{
	  /* Ask for read instead default  mmap */
	  grabmethod = 0;
	}

	if (strcmp (argv[i], "-s") == 0) {
			if (i + 1 >= argc) {
				if(debug) printf ("No parameter specified with -s, aborting.\n");
				exit (1);
			}

			sizestring = strdup (argv[i + 1]);

			width = strtoul (sizestring, &separateur, 10);
			if (*separateur != 'x') {
				if(debug) printf ("Error in size use -s widthxheight \n");
				exit (1);
			} else {
				++separateur;
				height =
					strtoul (separateur, &separateur, 10);
				if (*separateur != 0)
					if(debug) printf ("hmm.. dont like that!! trying this height \n");
				if(debug) printf (" size width: %d height: %d \n",
					width, height);
			}
	}
	if (strcmp (argv[i], "-w") == 0) {
			if (i + 1 >= argc) {
				if(debug) printf ("No parameter specified with -w, aborting.\n");
				exit (1);
			}
			serverport = (unsigned short) atoi (argv[i + 1]);
			if (serverport < 1024  ){
			if(debug) printf ("Port should be between 1024 to 65536 set default 7070 !.\n");
			serverport = 7070;
			}
	}

      if (strcmp (argv[i], "-h") == 0)
	{
	  printf ("usage: cdse [-h -d -g ] \n");
	  printf ("-h	print this message \n");
	  printf ("-d	/dev/videoX       use videoX device\n");
	  printf ("-g	use read method for grab instead mmap \n");

	  printf ("-s	widthxheight      use specified input size \n");
	  printf ("-w	port      server port \n");

	  exit (0);
	}
    }
   /* main code */
  
  printf(" %s \n",version);
  if (videodevice == NULL || *videodevice == 0)
    {
      videodevice = "/dev/video0";
    }
if(fork()==0)
{
	
  memset (&videoIn, 0, sizeof (struct vdIn));

  if (init_videoIn
        (&videoIn, videodevice, width, height, format,grabmethod) != 0)
     
    if(debug) printf (" damned encore rate !!\n");
 // if(debug) printf("depth %d",videoIn.bppIn);  

  pthread_create (&w1, NULL, (void *) grab, NULL);




 
 
 serv_sock = open_sock(serverport);
 signal(SIGPIPE, SIG_IGN);	/* Ignore sigpipe */

	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);

	sa.sa_flags = SA_RESTART;
	syslog(LOG_ERR,"Dlexserv Listening on Port  %d\n",serverport);
	
        printf("Waiting .... for connection. CTrl_c to stop !!!! \n");

  while (videoIn.signalquit)
    {
     sin_size = sizeof(struct sockaddr_in);
		if ((new_sock = accept(serv_sock, (struct sockaddr *)&their_addr, &sin_size)) == -1)
		{
			continue;
		}

	syslog(LOG_ERR,"Dlex video Got connection from %s\n",inet_ntoa(their_addr.sin_addr));
	printf("Dlex video Got connection from %s\n",inet_ntoa(their_addr.sin_addr));
	pthread_create(&server_th, NULL, (void *)service, &new_sock);
    } 

}
else
{
 myserv_sock=open_sock(myserverport);
 signal(SIGPIPE, SIG_IGN);
      while (1)
    {
     mysin_size = sizeof(struct sockaddr_in);
	 if ((mynew_sock = accept(myserv_sock, (struct sockaddr *)&mytheir_addr, &mysin_size)) == -1)
		{
			continue;
		}
	syslog(LOG_ERR,"Dlex sht Got connection from %s\n",inet_ntoa(mytheir_addr.sin_addr));
	printf("Dlex sht Got connection from %s\n",inet_ntoa(mytheir_addr.sin_addr));


	pthread_create(&myserver_th, NULL, (void *)myservice, &mynew_sock);
    } 
}

  pthread_join (w1, NULL);

  close(serv_sock);
  close(myserv_sock);
  close_v4l (&videoIn);  
return 0;
}



void
grab (void)
{
int err = 0;
  for (;;)
    {
      //if(debug) printf("I am the GRABBER !!!!! \n");
      err = v4lGrab(&videoIn);
      if (!videoIn.signalquit || (err < 0)){
      if(debug) printf("GRABBER going out !!!!! \n");
	break;
	}
    }
}

void myservice(void *myir)
{
	int *myid=(int*)myir;
	int myret;
	int mysock;
	char *shtrlt;
	
	pthread_t th_irst,th_smog;
	pthread_create(&th_irst,NULL,(void *)irst,NULL);
	pthread_create(&th_smog,NULL,(void *)smog,NULL);
	mysock=*myid;
	for(;;)
	{
        shtrlt=get_temphumi();
	//printf("asd");
	//sleep(1);
     	//ret = write_sock(sock, (unsigned char *)sht_rlt, strlen(sht_rlt));
     	myret = write_sock(mysock, (unsigned char *)shtrlt, strlen(shtrlt));
	}
	pthread_join(th_irst,NULL);
	pthread_join(th_smog,NULL);
  close_sock(mysock);
  pthread_exit(NULL);
}

void
service (void *ir)
{
  int *id = (int*) ir;
  int frameout = 1;
  struct frame_t *headerframe;
  int ret;
  int sock;
  int ack = 0;
  char *sht_rlt;

 unsigned char wakeup = 0;
 unsigned short bright;
 unsigned short contrast;
  struct client_t message;
  sock = *id;
 // if(debug) printf (" \n I am the server %d \n", *id);
 /* initialize video setting */
 bright = upbright(&videoIn);
 contrast = upcontrast(&videoIn);
 bright = downbright(&videoIn);
 contrast = downcontrast(&videoIn);
  for (;;)
    {   
      memset(&message,0,sizeof(struct client_t));
	 ret = read(sock,(unsigned char*)&message,sizeof(struct client_t));
	 //if(debug) printf("retour %s %d ret\n",message.message,ret);
	 if (ret < 0) {
	 	if(debug) printf(" Client vaporished !! \n");
		break;
	 }
	 if (!ret) break;
	 if(ret && (message.message[0] != 'O')) break;
	 
	 if (message.updobright){
	 	switch (message.updobright){
		case 1: bright = upbright(&videoIn);
		break;
		case 2: bright = downbright(&videoIn);
		break;
		}
		ack = 1;
	 } else if (message.updocontrast){
	 	switch (message.updocontrast){
		case 1: contrast = upcontrast(&videoIn);
		break;
		case 2: contrast = downcontrast(&videoIn);
		break;
		}
		ack = 1;
	} else if (message.sleepon){

		ack = 1;
	 } else ack =0;
       while ((frameout == videoIn.frame_cour) && videoIn.signalquit) usleep(1000);
       if (videoIn.signalquit){
	videoIn.framelock[frameout]++;
     	headerframe = (struct frame_t *) videoIn.ptframe[frameout];
	//headerframe->nbframe = framecount++;
	//if(debug) printf ("reader %d key %s width %d height %d times %dms size %d \n", sock,headerframe->header,
	//headerframe->w,headerframe->h,headerframe->deltatimes,headerframe->size);
	  headerframe->acknowledge = ack;
	  headerframe->bright = bright;
	  headerframe->contrast = contrast;
	  headerframe->wakeup = wakeup;
	 ret = write_sock(sock, (unsigned char *)headerframe, sizeof(struct frame_t)) ;
     	//sht_rlt=get_temphumi();
     	//ret = write_sock(sock, (unsigned char *)sht_rlt, strlen(sht_rlt));
	 
	 if(!wakeup)	
	 ret = write_sock(sock,(unsigned char*)(videoIn.ptframe[frameout]+sizeof(struct frame_t)),headerframe->size);

	 
	// ret = write_sock(sock,(unsigned char*)(videoIn.ptframe[frameout]+sizeof(struct frame_t)),headerframe->size);

	videoIn.framelock[frameout]--;
	frameout = (frameout+1)%4;     
      } else {
       if(debug) printf("reader %d going out \n",*id);
	break;
      }
    }
  close_sock(sock);
  pthread_exit(NULL);
}
void sigchld_handler(int s)
{
	videoIn.signalquit = 0;
}
