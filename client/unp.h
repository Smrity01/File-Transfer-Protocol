//in_port_t (16bits) and in_addr_t (32bits) are defined through typedef & sockaddr_in , in_addr structure
#include<netinet/in.h>
#include<netdb.h>
//file stream functions
#include<stdio.h>
//string conversion functions (atof and atoi) etc.
#include<stdlib.h>
#include<string.h>
//socket functions
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<dirent.h>
#include<fcntl.h> 
#include <sys/stat.h>
#define MAX 200
#define PORT 8040
#define SA struct sockaddr
char buffer[MAX] = "";