#include<stdio.h>
#include<malloc.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/epoll.h>


#include "Msg_handler.h"


void initSocketServerAddr(struct sockaddr_in *addr){
    addr->sin_family = AF_INET;
    addr->sin_port = htons(6379);
    inet_pton(AF_INET,"192.168.2.57",&(addr->sin_addr));
}


void main(){

    int server_fd;
    int client_fd;
    int bind_server;
    struct sockaddr_in *server_address = (struct sockaddr_in*)(malloc(sizeof(struct sockaddr_in)));
    struct sockaddr_in *client_address = (struct sockaddr_in*)(malloc(sizeof(struct sockaddr_in)));
    socklen_t *client_ipsize = (socklen_t*)(malloc(sizeof(socklen_t)));
    *client_ipsize = sizeof(struct sockaddr_in);


    //socket creation
    server_fd = socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK,0);
    if(server_fd == -1){
        perror("Socket creation failed \n");
        exit(0);
    }

    //Address structure prepration 
    initSocketServerAddr(server_address);
    //Binding the socket's server to an IP address
    bind_server = bind(server_fd,(struct sockaddr*)server_address,sizeof(struct sockaddr_in));
    if(bind_server == -1){
        perror("Couldn't bind socket to the given IP address \n");
        exit(1);
    }
    
    //Open server for connections
    int server_listen = listen(server_fd,128);
    if(server_listen == -1){
        perror("Couldn't open server for connections \n");
        exit(1);
    }else printf("Server listening at port %d \n",6379);

    //Creation of event structure to handle multiple clients
    int fd_manager = epoll_create1(0);
    struct epoll_event *server_watcher = (struct epoll_event*)(malloc(sizeof(struct epoll_event)));
    server_watcher->data.fd = server_fd;
    server_watcher->events = EPOLLIN;
    epoll_ctl(fd_manager,EPOLL_CTL_ADD,server_fd,server_watcher);

    //Creation of structure to hold events\clients 
    struct epoll_event *events = (struct epoll_event*)(malloc(128*sizeof(struct epoll_event)));

    //Make server accept connections. Here we also pass the structure where the client's IP will be stored
    while(true){

    int num_events = epoll_wait(fd_manager,events,128,-1);

    int i = 0;
    while(i < num_events){

        if(events[i].data.fd == server_fd){

            while( (client_fd = accept(server_fd,(struct sockaddr*)client_address,client_ipsize)) != -1 ){
                struct epoll_event *client_event = (struct epoll_event*)(malloc(sizeof(struct epoll_event)));
                client_event->events = EPOLLIN;
                client_event->data.fd = client_fd;
                epoll_ctl(fd_manager,EPOLL_CTL_ADD,client_fd,client_event);
                free(client_event);
                printf("Client connected \n \n");
            }

        }else{
            //Handle communication exchange
            printf("Client %d says ",events[i].data.fd);
            recv_message(events[i].data.fd);
            send_message(events[i].data.fd,"message received \n");
      }

      i++;
    }    

  }

  free(server_address);
  free(client_address);
  free(client_ipsize);

}

