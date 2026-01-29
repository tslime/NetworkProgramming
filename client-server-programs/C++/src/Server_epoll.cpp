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
            address->sin_port = htons(PORT_NUM);
            inet_pton(AF_INET,"IP_NUM",&(address->sin_addr));
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

    //Add server file descriptor to watch list of events
    struct epoll_event *server_watcher = (struct epoll_event*)(malloc(sizeof(struct epoll_event)));
    server_watcher->data.fd = server_fd;
    server_watcher->events = EPOLLIN;
    epoll_ctl(fd_manager,EPOLL_CTL_ADD,server_fd,server_watcher);


    struct epoll_event *events = (struct epoll_event*)(malloc(128*sizeof(struct epoll_event)));

    while(true){

        int num_events = epoll_wait(fd_manager,events,128,-1);

        int i = 0;
        while(i < num_events){
            if(events[i].data.fd == server_fd){
                
                client_fd = accept(server_fd,(struct sockaddr*)client_address,client_ipsize);
                if(client_fd == -1){
                    perror("Connection failed \n");
                    exit(1);
                    }
                
                struct epoll_event *new_client = (struct epoll_event*)(malloc(sizeof(struct epoll_event)));
                new_client->data.fd = client_fd;
                new_client->events  = EPOLLIN;
                epoll_ctl(fd_manager,EPOLL_CTL_ADD,client_fd,new_client);

                cout << "client connected.... \n";
                free(new_client);
            }else{
                
                //communication exchange
                *message = "message received \n"; 

                cout << "Client " << events[i].data.fd << " says: " ;
                Msghandler::receive_message(events[i].data.fd,buffer);
                Msghandler::send_message(events[i].data.fd,message);

            }
            i++;
        }

    }

    exit(1);
}
