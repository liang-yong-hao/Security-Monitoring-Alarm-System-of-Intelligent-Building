#include "tcputils.h"
#include "utils.h"

static void initaddr (struct sockaddr_in *servadrr,char *address,int port);

static void
initaddr (struct sockaddr_in *servadrr,char *address,int port)
{  
int adrsize = 0;
	if(address){
		adrsize = strlen(address);
		if(adrsize < 7 || adrsize > 15)
			exit_fatal("setting wrong address Abort !!");
		servadrr->sin_addr.s_addr = inet_addr(address);
	} else {
		servadrr->sin_addr.s_addr = INADDR_ANY;
	}
		
	servadrr->sin_family = AF_INET;
  	servadrr->sin_port = htons (port);
   	memset (&(servadrr->sin_zero), '\0', 8);
	
}

int
open_sock (int port)
{
  struct sockaddr_in servadr;
  int server_handle;
  int O_on = 1;
/* Create a new socket */
  if ((server_handle = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    exit_fatal ("Error opening socket Abort !");
  if (setsockopt (server_handle, SOL_SOCKET, SO_REUSEADDR,
		  &O_on, sizeof (int)) == -1)
    exit_fatal ("Setting reused address fail Abort !");
/* Now set the server address struct and bind socket to the port*/
  initaddr (&servadr,NULL, port);
  if (bind 
      (server_handle, (struct sockaddr *) &servadr,
       sizeof (struct sockaddr)) == -1)
    exit_fatal ("error bind socket");
/* Listen on the socket */
  if (listen (server_handle, MAXCONNECT) == -1)
    exit_fatal ("Damned errors when listen Abort !");
  return server_handle;
}

int open_clientsock(char * address, int port)
{
  struct sockaddr_in servadr;
  int client_handle;
 
  /* Create a new socket */
  if ((client_handle = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    exit_fatal ("Error opening socket Abort !");
  
/* Now set the server address struct and connect client socket to the port*/
  initaddr (&servadr,address,port);

  if (connect(client_handle,(struct sockaddr *) &servadr,
       sizeof (struct sockaddr)) == -1)
	  exit_fatal ("connect failed Abort !");
  return client_handle;
}

void
close_sock (int sockhandle)
{
  close (sockhandle);
}

int
write_sock (int sockhandle, unsigned char *buf, int length)
{
  int byte_send = -1;
  byte_send = write (sockhandle, buf, length);
  return (length - byte_send);
}

int
read_sock (int sockhandle, unsigned char *buf, int length)
{
  int byte_read = -1;
  unsigned char *ptbuf =buf;
  int mlength = length;
  int i = 0;
  do {
  byte_read = read (sockhandle, ptbuf,mlength);
  if (byte_read > 0){
  	ptbuf = ptbuf+byte_read;
  	mlength = mlength-byte_read;
	//printf("reste to read %d \n",mlength);
  }
  //printf("buffer value 0x%02X 0x%02X \n",buf[0],buf[1]);
	i++;
	//printf("waiting %d \n",i);
	if(i > 10000) return -1;
  } while (mlength > 0);
  return (mlength);
}
int 
reportip( char *src, char *ip, unsigned short *port)
{
	int j,k,done,ipdone,nbpt=0;
	char *AdIpPort= src;
	char *AdIp = ip;
	char Ports[] = "65536";
	j=0;k=0;done=0;ipdone=0;
			while(j < 22){
			switch (AdIpPort[j]){
			case '\0':
				done =1;
				break;
			case '.':
				nbpt++;
				if(nbpt > 3){
				//printf("error fatal \n");
				return -1;
				}
			break;	
			case ':':
				k = 0; ipdone = 1;
				AdIp[j++] ='\0';
			break;
			default:
				
			break;
			}
			if (ipdone)
					Ports[k++]=AdIpPort[j++];
				else
					AdIp[k++]=AdIpPort[j++];
			if(done) break;
			}
			*port = (unsigned short) atoi (Ports);
			//printf ("Ip %s Port %s \n",AdIp,Ports);
			if(*port < 1024) {
			//printf("ERROR Set default port to 7070 \n");
			*port = 7070;
			}
return 0;
}
