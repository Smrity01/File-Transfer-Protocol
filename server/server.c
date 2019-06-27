#include "unp.h"
FILE *fptr;
char choice;

int validateUser(char *username){
    int i;
    for(i = 0; i < noOfUsers; i++){
        if(strcmp(username,userArray[i]) == 0){
            return i;
        }
    }
    return -1;
}
int validatePassword(char *password, int index){
    if (strcmp(password,passwordArray[index]) == 0){
        return 1;
    }
    else{
        return -1;
    }
}
int abortFile(int connfd){
    srand(time(0)); 
    int randomNumber;
    bzero(buffer,sizeof(buffer));
    read(connfd,buffer,MAX);
    randomNumber = rand()%2;
    //printf("%d",randomNumber);
    bzero(buffer,sizeof(buffer));
    if(randomNumber == 0){
        strcpy(buffer,"\nERROR: Can't abort, file transfer in PROCESS...");
        write(connfd,buffer,MAX);
        return 0;    
    } 
    else{
        strcpy(buffer,"Abort");
        write(connfd,buffer,MAX);
        return 1;
    }

}

void storeRequestedFile(int connfd){
    char sourceFile[MAX],targetFile[MAX];
    char path[MAX];
    char ch;
    bzero(buffer,sizeof(buffer));
    read(connfd,buffer,MAX);
    strcpy(sourceFile,buffer);
    strcpy(path , "/home/smrity/Desktop/client/");
    strcat(path,sourceFile);
    bzero(buffer,sizeof(buffer));
    FILE *source, *target;
    source = fopen(path, "r"); 
    if (source == NULL)
    {
        strcpy(buffer,"\n ERROR: This file does not exist........!!!  ");
        write(connfd,buffer,MAX);
        return;
    }
    strcpy(targetFile , "/home/smrity/Desktop/server/");
    strcat(targetFile,sourceFile);
    //printf("%s",targetFile);
    target = fopen(targetFile, "w");
    if (target == NULL)
    {
        fclose(source);
        strcpy(buffer,"\n Sorry! Request unsuccessful    (TRY AGAIN)");
        write(connfd,buffer,MAX);
        return;
    }
    while ((ch = fgetc(source)) != EOF)
        fputc(ch, target);
    strcpy(buffer,"\n Request Successful...!");
    write(connfd,buffer,MAX);
    fclose(source);
    fclose(target);
    return;
}
void sendRequestedFile(int connfd){
    char sourceFile[MAX],targetFile[MAX];
    char path[MAX];
    char ch;
    bzero(buffer,sizeof(buffer));
    read(connfd,buffer,MAX);
    strcpy(sourceFile,buffer);
    strcpy(path , "/home/smrity/Desktop/server/");
    strcat(path,sourceFile);
    bzero(buffer,sizeof(buffer));
    FILE *source, *target;
    source = fopen(path, "r");
     
    if (source == NULL)
    {
        strcpy(buffer,"\n ERROR: This file does not exist........!!!  ");
        write(connfd,buffer,MAX);
        return;
    }
    strcpy(targetFile , "/home/smrity/Desktop/client/");
    strcat(targetFile,sourceFile);
    target = fopen(targetFile, "w");
    if (target == NULL)
    {
        fclose(source);
        strcpy(buffer,"\n Sorry! Request unsuccessful    (TRY AGAIN)");
        write(connfd,buffer,MAX);
        return;
    }
    while ((ch = fgetc(source)) != EOF){
        fputc(ch, target);
    }
    strcpy(buffer,"\n Request Successful...!");
    write(connfd,buffer,MAX);
    fclose(source);
    fclose(target);
    return;
}
void removeDiectory(int connfd){
    char *path = malloc(MAX); 
    bzero(buffer,sizeof(buffer));
    read(connfd,buffer,MAX);
    strcpy(path,buffer);
    int status;
    status = rmdir(path);
    bzero(buffer,sizeof(buffer));
    if(status == 0){
        strcpy(buffer,"\nDelete Successful...!");
    }
    else{
        strcpy(buffer,"\n SORRY! Delete Unsucessful   (TRY AGAIN)");
    }
    write(connfd,buffer,MAX);
    return;
}
void makeDirectory(int connfd){
    char *path = malloc(MAX); 
    bzero(buffer,sizeof(buffer));
    read(connfd,buffer,MAX);
    strcpy(path,buffer);
    int status;
    status = mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    bzero(buffer,sizeof(buffer));
    if(status == 0){
        strcpy(buffer,"\nCommand Sucessful...!");
    }
    else{
        strcpy(buffer,"\nSORRY! Command Unsucessful (TRY AGAIN)");
    }
    write(connfd,buffer,MAX);
    return;
}
void nameCurrentDirectory(int connfd){
    char currentDir[MAX];
    bzero(buffer,sizeof(buffer));
    read(connfd,buffer,MAX);
    bzero(buffer,sizeof(buffer));
    if (getcwd(currentDir, sizeof(currentDir)) == NULL){
      //fprintf(fptr,"%s","\ngetcwd() error");
      strcpy(buffer,"error");
    }
    else{
      //fprintf(fptr,"%s","\ncurrent working directory is: %s\n");
        char *last = strrchr(currentDir, '/');
        if (last != NULL) {
            strcpy(buffer,last+1);
        }
    }

    write(connfd,buffer,MAX);
    return;
}
void changeDirectory(int connfd){
	char *path = malloc(MAX);
	int returnedValue;
	bzero(buffer,sizeof(buffer));
    read(connfd, buffer, sizeof(buffer));// requested PATH....13
	strncpy(path,buffer,MAX);
	returnedValue = chdir(path);
	bzero(buffer,sizeof(buffer));
	if(returnedValue == 0){
		strncpy(buffer,"changed",MAX);
        fprintf(fptr,"%s","\n The directory is changed...\n");
        }
	else{
		strncpy(buffer,"error",MAX);
		fprintf (fptr,"%s","\nError IN changing directory...\n");
	}
    write(connfd, buffer, sizeof(buffer));// get path....14
	return;
}
void list(int connfd){
    DIR *dir;
	struct dirent *ent;
	bzero(buffer,sizeof(buffer));
    read(connfd,buffer,MAX); // read the list request ....11
	bzero(buffer,sizeof(buffer));
    if ((dir = opendir (".")) != NULL) {
 	 /* print all the files and directories within directory */
  		while ((ent = readdir (dir)) != NULL) {
			//printf ("%s\n", ent->d_name);
            strcat(buffer,ent->d_name);
			strcat(buffer,"\n");
  		}
		//strcat(buffer,"null");
		write(connfd,buffer,sizeof(buffer)); // Write ouput of list directory.... 12
  	    bzero(buffer,sizeof(buffer));
		closedir (dir);
		return;
	} 
	else {
  		/* could not open directory */
  		//printf ("could not open directory");
  		bzero(buffer,sizeof(buffer));
		strncpy(buffer,"openerror", MAX);
		write(connfd,buffer,sizeof(buffer));
		bzero(buffer,sizeof(buffer));
		return;
	}
}

void loginMenu(int connfd){
    int abortVar;
    for(int i=0;i<50;i++){
    bzero(buffer,sizeof(buffer));
    read(connfd,buffer,MAX);// READ login MENU request....7
    if(strcmp(buffer,"loginmenu") == 0){
        bzero(buffer,sizeof(buffer));
        strcpy(buffer,"\n\n1) List \n2) Change Directory  \n3) Name of current Directory \n4) Make Directory \n5) Remove Directory \n6) Retrieve File \n7) Store File \n8) Abort\n9) logout \n\n");
        write(connfd,buffer,MAX); // WRITE MENU ON BUFFER....8
        bzero(buffer,sizeof(buffer));
        read(connfd,buffer,MAX);// READ user choice....9
        choice = buffer[0];
        bzero(buffer,sizeof(buffer));
        strcpy(buffer,"end 1");        
        write(connfd,buffer,MAX); // WRITE end....10
        switch(choice){
        case '1':
                list(connfd);
                break;
        case '2':
                changeDirectory(connfd);
                break;
        case '3':
                nameCurrentDirectory(connfd);
                break;
        case '4':
                makeDirectory(connfd);
                break;
        case '5':
                removeDiectory(connfd);
                break;
        case '6':
                sendRequestedFile(connfd);
                break;
        case '7':
                storeRequestedFile(connfd);
                break;
        case '8':
                abortVar = abortFile(connfd);
                break;
        case '9':
                break;
        } 
        if(choice == '9' || abortVar == 1){
            break;
        }
    }
    else{
        fprintf(fptr,"%s", "\nCannot SHOW LOGIN menu...\n");
    }
    }
    
}
int login(int connfd){
    bzero(buffer,sizeof(buffer));
    read(connfd,buffer,MAX);// READ login request....1
    int index;
    if(strcmp(buffer,"login") == 0){
        bzero(buffer,sizeof(buffer));
        strcpy(buffer, "Userid");
        write(connfd,buffer,MAX);// WRITE ask for userid....2
        for(;;){
            bzero(buffer,sizeof(buffer));
            read(connfd,buffer,MAX);// READ the username....3
            index = validateUser(buffer);
            if((index = validateUser(buffer)) >= 0){
                bzero(buffer,sizeof(buffer));
                strcpy(buffer, "331");
                write(connfd,buffer,MAX);// WRITE status of userid....4(if)
                break;
            }
            else{
                fprintf(fptr,"\nINCORRECT USER NAME...");
                bzero(buffer,sizeof(buffer));
                strcpy(buffer, "incorrect");
                write(connfd,buffer,MAX);// WRITE status of userid....4(else)
            }
    }
        for(;;){
            bzero(buffer,sizeof(buffer));
            read(connfd,buffer,MAX);// READ the password....5
            if(validatePassword(buffer,index) > 0){
                bzero(buffer,sizeof(buffer));
                strcpy(buffer, "correct");
                write(connfd,buffer,MAX);// WRITE status of password....6(if)
                break;
            }
            else{
                fprintf(fptr,"\nINCORRECT password...");
                bzero(buffer,sizeof(buffer));
                strcpy(buffer, "incorrect");
                write(connfd,buffer,MAX);// WRITE status of password....6(else)

            }
    }
    return 1;
    }
    else{
        fprintf(fptr,"%s","\n530: CAN'T TAKE LOGIN REQUEST....\n");
        return 0;
    }

}
void serviceRequest(int connfd){
    int status = login(connfd);
    if(status == 1){
        loginMenu(connfd);
    }
}
int main(){
    fptr = fopen("serverlog.txt","w");
    if (fptr == NULL)
    {
    printf("Cannot open file \n");
    }
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;
	sockfd = socket(AF_INET, SOCK_STREAM,0);
    fprintf(fptr,"%s","***********************NEW************************************");
	if (sockfd == -1){
		fprintf(fptr,"%s","\nSOCKfd FAILED...\n");
		exit(0);
	}
	else{
		fprintf(fptr,"%s","\nSuccessful");
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	if((bind(sockfd,(SA*)&servaddr, sizeof(servaddr))) != 0){
		fprintf(fptr,"%s","\nBIND failed...\n");
		exit(0);
	}
	else {
		fprintf(fptr,"%s","\nBIND successful...\n");
	}
    int childpid;
	listen(sockfd,5);
    while(1){
        len = sizeof(cli);
	    connfd = accept(sockfd, (SA*)&cli, &len);
	    if((childpid = fork()) == 0){
			close(sockfd);

        if (connfd < 0) { 
	        fprintf(fptr,"%s","\n Acccept failed...\n"); 
	        exit(0); 
	    } 
    	else{
            fprintf(fptr,"%s","\nServer acccept the client...\n"); 
	    }
        serviceRequest(connfd);
        }
    }
	close(connfd);
    fclose(fptr);
}
