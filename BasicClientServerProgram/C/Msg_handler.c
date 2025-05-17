#include<stdio.h>
#include<malloc.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<stdbool.h>
#include<string.h>


#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void recv_message(int fd){

    int bytes_received = 0;
    char *msg = (char*)(malloc(sizeof(char)));
    char *buffer = (char*)(malloc(1000*sizeof(char)));
    bool b = false;

    while(!b){
        memset(buffer,0,1000);
        bytes_received = recv(fd,buffer,1000,0);

        if(bytes_received == -1){
            perror("Error during message reception");
            exit(1);
            }else{   
                buffer[bytes_received] = '\0';
                if(buffer[strlen(buffer)-1] == '\n')
                b = true;

                strcat(msg,buffer);
            }
    }
   
    printf("%s \n",msg);
}


void send_message(int fd,char *message){

    int bytes_sent = 0;
    bool b = false;

    while(bytes_sent < strlen(message)){
      bytes_sent = send(fd,message,strlen(message),0); 

      if(bytes_sent == -1){
        perror("Error during message transmission");
        exit(1);
      }
    }     
}
