#include<iostream>
#include<string.h>
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
    int bind_server;
    int server_listening;
    int accept_result;
    struct sockaddr_in *server_address = (struct sockaddr_in*)(malloc(sizeof(struct sockaddr_in)));

    cout << "test \n";

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



    exit(1);
}
