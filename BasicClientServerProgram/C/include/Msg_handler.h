#ifndef MSG_HANDLER
#define MSG_HANDLER

#include<malloc.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<stdbool.h>
#include<string.h>


#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


void recv_message(int fd);
void send_message(int fd,char *message);


#endif