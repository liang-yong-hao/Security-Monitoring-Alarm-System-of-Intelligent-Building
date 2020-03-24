#ifndef TCPUTILS_H
#define TCPUTILS_H

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXCONNECT 10
#define SERVEUR_PORT 7070
#define CLIENT_PORT 7071
#define SERVEUR_ADR "192.168.0.179"

int 
open_sock(int port);
int 
open_clientsock(char * address, int port);
int 
read_sock(int sockhandle, unsigned char* buf, int length);
int 
write_sock(int sockhandle, unsigned char* buf, int length);
void 
close_sock(int sockhandle);
int 
reportip( char *src, char *ip, unsigned short *port);
#endif /* TCPUTILS_H*/
