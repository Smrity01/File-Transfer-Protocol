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
#include <sys/sendfile.h>
#include <sys/stat.h>
#include<time.h>
#define MAX 200
#define PORT 8040
#define SA struct sockaddr
#define noOfUsers 6
#define limitUsername 20
#define limitpassword 8
char buffer[MAX] = "";
char userArray[noOfUsers][limitUsername] = {"smrity","vipin","deepti","nisha","priyanka","manisha"};
char passwordArray[noOfUsers][limitpassword] = {"123","456","987","789","654","321"};
