#include "Msghandler.h"


#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<malloc.h>
#include<unistd.h>
#include<stdbool.h>


#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/epoll.h>


using std::cin;
using std::cout;
using std::end;
using std::string;



class Serverfork{

    public:

        static void initServerSocketAddr(struct sockaddr_in *address){
            address->sin_family = AF_INET;
            address->sin_port = htons(6379);
            inet_pton(AF_INET,"192.168.2.57",&(address->sin_addr));
        }


};

int main(){

    int server_fd;
    int client_fd;
    int pid;
    int bind_server;
    int server_listening;
    int accept_result;
    struct sockaddr_in *server_address = (struct sockaddr_in*)(malloc(sizeof(struct sockaddr_in)));
    struct sockaddr_in *client_address = (struct sockaddr_in*)(malloc(sizeof(struct sockaddr_in)));
    socklen_t *client_ipsize = (socklen_t*)(malloc(sizeof(socklen_t)));
    *client_ipsize = sizeof(struct sockaddr_in);
    string *buffer = new string(1024,'\0');
    string *message = new string(1024,'\0');


    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd == -1){
        perror("Failed to create socket \n");
        exit(1);
    }

    Serverfork::initServerSocketAddr(server_address);
    bind_server = bind(server_fd,(struct sockaddr*)server_address,sizeof(struct sockaddr_in));
    if(bind_server == -1){
        perror("Failed to bind socket to an address \n");
        exit(1);
    }

    server_listening = listen(server_fd,128);
    if(server_listening == -1){
        perror("Server failed to open to listening");
        exit(1);
    }

    
    int fd_manager = epoll_create1(0);


    struct epoll_event *events = (struct epoll_event*)(malloc(128*sizeof(struct epoll_event)));

    while(true){

        client_fd = accept(server_fd,(struct sockaddr*)client_address,client_ipsize);
        if(client_fd == -1){
            perror("Connection failed \n");
            exit(1);
        }

   
            cout << "client connected.... \n";
            *message = "message received \n";
            while(true){    

                cout << "Client " << getpid() << " says: " ;
                Msghandler::receive_message(client_fd,buffer);
                Msghandler::send_message(client_fd,message);
            
            }

            close(client_fd);
            close(server_fd);
           
          
    }

    exit(1);
}
