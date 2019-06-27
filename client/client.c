#include "unp.h"

int statusAbortFile(int sockfd){
    bzero(buffer,sizeof(buffer));
    strcpy(buffer ,"abort");
    write(sockfd,buffer,MAX);
    bzero(buffer,sizeof(buffer));
    read(sockfd,buffer,MAX);
    printf("%s",buffer);
    if(strcmp(buffer,"Abort") == 0){
        printf("\n");
        printf("%s",buffer);
        printf("\n");
        return 1;
    }
    else{
        printf("%s",buffer);
        return 0;
    }
}
void storeFile(int sockfd){
    char sourceFile[MAX];
    printf("Enter file name you want to store:\t");
    scanf("%[^\n]%*c", sourceFile);
    bzero(buffer,sizeof(buffer));
    strcpy(buffer ,sourceFile);
    write(sockfd,buffer,MAX);
    bzero(buffer,sizeof(buffer));
    read(sockfd,buffer,MAX);
    printf("%s",buffer);
    return;
}
void retrieveFile(int sockfd){
    char sourceFile[MAX];
    printf("\nEnter the file name you want to retrieve:\t");
    scanf("%[^\n]%*c", sourceFile);
    bzero(buffer,sizeof(buffer));
    strcpy(buffer,sourceFile);
    write(sockfd,buffer,MAX);
    bzero(buffer,sizeof(buffer));
    read(sockfd,buffer,MAX);
    printf("%s",buffer);
    return;
}
void statusRemoveDirectory(int sockfd){
    char *path = malloc(MAX);
    printf("\nEnter the path name with the Directory name:\t");
    scanf("%[^\n]%*c", path);
    bzero(buffer,sizeof(buffer));
    strcpy(buffer,path);
    write(sockfd,buffer,MAX);
    bzero(buffer,sizeof(buffer));
    read(sockfd,buffer,MAX);
    printf("%s",buffer);
    return;
}
void statusMakeDir(int sockfd){
    char *path = malloc(MAX);
    printf("\nEnter the path with Directory name:\t");
    scanf("%[^\n]%*c", path);
    bzero(buffer,sizeof(buffer));
    strcpy(buffer,path);
    write(sockfd,buffer,MAX);
    bzero(buffer,sizeof(buffer));
    read(sockfd,buffer,MAX);
    printf("%s",buffer);
    return;
}
void statusNameCurrentDirectory(int sockfd){
    bzero(buffer,sizeof(buffer));
    strcpy(buffer,"Name directory");
    write(sockfd,buffer,MAX);
    bzero(buffer,sizeof(buffer));
    read(sockfd,buffer,MAX);
    printf("\nCurrent Directory: ");
    printf("%s",buffer);
    return;
}
void statusChangeDirectory(int sockfd){
    char *path = malloc(MAX);
	printf("\nEnter the Path:\t");
    scanf("%[^\n]%*c", path);
    bzero(buffer, sizeof(buffer));
	strncpy(buffer,path,MAX);
	write(sockfd, buffer, strlen(buffer));// WRITE requested path ---->13
	bzero(buffer, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));// READ reqested path RESPONSE.....-> 14
	if (strcmp(buffer, "error") == 0){
		printf("\nERROR : Directory cannot be changed.\n");
		return;
	}
	else{
    	printf("\nDirectory is changed.");
    }
	
	return;
}
void statusList(int sockfd){
	bzero(buffer, sizeof(buffer));
	strncpy(buffer,"list", MAX);
	write(sockfd, buffer, strlen(buffer));// write  request 'list' directory ....11
    bzero(buffer, sizeof(buffer));
	read(sockfd, buffer, sizeof(buffer));// Read list..... 11
	if (strcmp(buffer, "openerror") == 0){
		printf("\nERROR : Directory cannot be listed.\n");
		return;
	}
    printf("\n\n    FILES IN CURRENT DIRECTORY   \n");
	printf("%s",buffer);
    printf("\n\n");
	return;
}
void loginMenu(int sockfd){
    int abortVar;
    for(int i=0;i<50;i++){
    bzero(buffer,sizeof(buffer));
    strcpy(buffer,"loginmenu");
    //printf("\nwrite 7");
    write(sockfd,buffer,MAX);// WRITE request for login MENU....7
    bzero(buffer,sizeof(buffer));
    //printf("\nread 8");
    read(sockfd,buffer,MAX);// READ asked for Menu...8
    printf("\n--------------------------------------------------");
    printf("\n                     MENU                       ");
    printf("\n--------------------------------------------------");
    printf("%s",buffer);
    bzero(buffer,sizeof(buffer));
    char choice;
    printf("\nChoose Your Option (Enter number):\t");
    scanf("%c%*c",&choice);
    buffer[0] = choice;
    //printf("\nwrite 9");
    write(sockfd,buffer,MAX);// WRITE user choice in login MENU....9
    bzero(buffer,sizeof(buffer));
    //printf("\nreAD 10");
    read(sockfd,buffer,MAX);// READ asked for Menu...10          
    switch(choice){
        case '1':
                statusList(sockfd);
                break;
        case '2':
                statusChangeDirectory(sockfd);
                break;
        case '3':
                statusNameCurrentDirectory(sockfd);
                break;
        case '4':
                statusMakeDir(sockfd);
                break;
        case '5':
                statusRemoveDirectory(sockfd);
                break;
        case '6':
                retrieveFile(sockfd);
                break;
        case '7':
                storeFile(sockfd);
                break;
        case '8':
                abortVar = statusAbortFile(sockfd);
                break;
        case '9':
                break;
    }
    if(choice == '9' || abortVar == 1){
        printf("\nGood Bye! Have a nice day.\n\n");
        break;
    }
}
}
int requestLogin(int sockfd){
    bzero(buffer,sizeof(buffer));
    strcpy(buffer,"login");
    write(sockfd,buffer,MAX);// WRITE request for login....1
    bzero(buffer,sizeof(buffer));
    read(sockfd,buffer,MAX);// READ asked for user id...2
    //printf("%s",buffer);
    if(strcmp(buffer,"Userid") == 0){
        char username[MAX] = "";
        for(;;){
            printf("\nEnter username:\t ");
            scanf("%[^\n]%*c" , username);
            bzero(buffer,sizeof(buffer));
            strcpy(buffer,username);
            write(sockfd,buffer,MAX);// WRITE user id....3
            bzero(buffer,sizeof(buffer));
            read(sockfd,buffer,MAX);// READ the status of entered userid...4
            if(strcmp(buffer, "331") == 0){
			    //printf("\n*******You're logged-in********\n");
			    break;
		    }
		    printf("\nIncorrect!!!\n**Re-Enter Your Username**");
        }
        char password[MAX] = "";
        for(;;){
            printf("\nEnter password:\t ");
            scanf("%[^\n]%*c" , password);
            bzero(buffer,sizeof(buffer));
            strcpy(buffer,password);
            write(sockfd,buffer,MAX);// WRITE password....5
            bzero(buffer,sizeof(buffer));
            read(sockfd,buffer,MAX);// READ the status of entered password...6
            if(strcmp(buffer, "correct") == 0){
			    printf("\n***********    FILE TRANSFER PROTOCOL   ********\n");
                break;
		    }
		    printf("\nIncorrect!!!\n**Re-Enter Your Password**");
        }
    return 1;
    }
    else{
        printf("\n530: LOGIN NOT POSSIBLE");
        return 0;
    }
}
int main(){
	int sockfd,connfd;
	struct sockaddr_in servaddr,cli;
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if (sockfd == -1){
		printf("\nsocket failed....\n");
		exit(0);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
    if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("\nSORRY...! Connection with the server failed...\n"); 
        exit(0); 
    }
    int status;
	status = requestLogin(sockfd);
    if(status == 1){
        loginMenu(sockfd);
    }
	close(sockfd);
	return 0;
}
