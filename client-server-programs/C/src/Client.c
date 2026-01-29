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

#include "Msg_handler.h"

void initSockAdrrConnection(struct sockaddr_in *address){
    address->sin_family = AF_INET;
    address->sin_port = htons(PORT_NUM);
    inet_pton(AF_INET,"IP_NUM",&(address->sin_addr));
}

void main(){

    int client_fd;
    int client_connection_result;
    char *msg = (char*)(malloc(1000*sizeof(char)));
    struct sockaddr_in *server_address = (struct sockaddr_in*)(malloc(sizeof(struct sockaddr_in)));
    initSockAdrrConnection(server_address);



    client_fd = socket(AF_INET,SOCK_STREAM,0);
    if(client_fd == -1){
        perror("Socket creation error \n");
        exit(1);
    }

    client_connection_result = connect(client_fd,(struct sockaddr*)server_address,sizeof(struct sockaddr_in));
    if(client_connection_result == -1){
        perror("Error during connection attempt \n");
        exit(1);
    }else{
        printf("Connection successful...\n \n");
        while(true){
            printf("Type message you want to send: \n");
            fgets(msg,1000,stdin);
            
            send_message(client_fd,msg);
            printf("Server says: ");
            recv_message(client_fd);
        }
        close(client_fd);
    }
}