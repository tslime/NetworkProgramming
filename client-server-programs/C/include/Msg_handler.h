#ifndef MSG_HANDLER
#define MSG_HANDLER

#include<stdio.h>
#include<malloc.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<stdbool.h>
#include<string.h>
#include<errno.h>

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void recv_message(int fd){

    int bytes_received = 0;
    char *msg = (char*)(malloc(1000*sizeof(char)));
    memset(msg,0,1000);
    char *buffer = (char*)(malloc(1000*sizeof(char)));
    bool b = false;

    while(!b){
        memset(buffer,0,1000);
        bytes_received = recv(fd,buffer,1000,0);

        if(bytes_received == -1){
            if(errno == EAGAIN || errno == EWOULDBLOCK)
            b = true;
            else{
               perror("Error during message reception");
               free(msg);
               free(buffer);
               exit(1);
            }
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
    int total = 0;
    bool b = false;

    while(total < strlen(message)){
      bytes_sent = send(fd,message+total,strlen(message)-total,0); 

      if(bytes_sent == -1){
        perror("Error during message transmission");
        exit(1);
      }
      total += bytes_sent;
    }     
}


#endif