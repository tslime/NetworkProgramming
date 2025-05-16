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
    server_fd = socket(AF_INET,SOCK_STREAM,0);
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




    //Make server accept connections. Here we also pass the structure where the client's IP will be stored

    while(1){

    client_fd = accept(server_fd,(struct sockaddr*)client_address,client_ipsize);
    if(client_fd == -1){
        perror("Client failed to connect \n");
        exit(1);
    }else{

        int pid = fork();

        if(pid == 0){
        printf("Client conneted \n \n");

        //Handle communication exchange
        char *msg_storage = (char*)(malloc(100000*sizeof(char)));

       while(1){
        memset(msg_storage,0,100000);
        int msg_size = recv(client_fd,msg_storage,sizeof(msg_storage),0);
        if(msg_size == -1){
            perror("error during receiving a message");
            exit(1);
        }else{
            printf("Client says: %s \n",msg_storage);
            send(client_fd,"message received \n",strlen("message received \n"),0);
        }          
      }
      close(client_fd);

     }else close(client_fd);

    }



  }


}