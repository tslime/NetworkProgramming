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

    int fd_server;
    int fd_client;
    int bind_server;
    int server_listening;
    int accept_result;
    struct sockaddr_in *server_address = (struct sockaddr_in*)(malloc(sizeof(struct sockaddr_in)));
    struct sockaddr_in *client_address = (struct sockaddr_in*)(malloc(sizeof(struct sockaddr_in)));
    socklen_t *client_ipsize = (socklen_t*)(malloc(sizeof(socklen_t)));
    *client_ipsize = sizeof(struct sockaddr_in);


    fd_server = socket(AF_INET,SOCK_STREAM,0);
    if(fd_server == -1){
        perror("Failed to create socket \n");
        exit(1);
    }

    Serverfork::initServerSocketAddr(server_address);
    bind_server = bind(fd_server,(struct sockaddr*)server_address,sizeof(struct sockaddr_in));
    if(bind_server == -1){
        perror("Failed to bind socket to an address \n");
        exit(1);
    }

    server_listening = listen(fd_server,128);
    if(server_listening == -1){
        perror("Server failed to open to listening");
        exit(1);
    }

    char *buffer = (char*)(malloc(100*sizeof(string)));
    string *message = (string*)(malloc(100*sizeof(string)));

    while(true){
            fd_client = accept(fd_server,(struct sockaddr*)client_address,client_ipsize);
            if(fd_client == -1){
                perror("Connection failed \n");
                exit(1);
            }


            cout << "client connected.... \n";
            while(true){    
                recv(fd_client,buffer,sizeof(buffer),0);
                cout << "Client says: "<< buffer << " \n";
                send(fd_client,"message received \n",strlen("message received \n"),0);
            }

            close(fd_server);
            close(fd_client);
    }

    

    exit(1);
}
