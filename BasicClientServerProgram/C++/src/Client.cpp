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


using std::cin;
using std::cout;
using std::end;


class Client{

    public:
            static void initClientSocketAddr(struct sockaddr_in *address){
                address->sin_family = AF_INET;
                address->sin_port = htons(PORT_NUM);
                inet_pton(AF_INET,"IP_NUM",&(address->sin_addr));
            }

};


int main(){


 
    int client_fd;
    int connection_result;
    struct sockaddr_in *client_address = (struct sockaddr_in*)(malloc(sizeof(struct sockaddr_in)));
    Client::initClientSocketAddr(client_address);

    client_fd = socket(AF_INET,SOCK_STREAM,0);
    if(client_fd == -1){
        perror("Error creating socket \n");
        exit(1);
    }


    connection_result = connect(client_fd,(struct sockaddr*)client_address,sizeof(struct sockaddr_in));
    if(connection_result == -1){
        perror("Error connecting \n");
        exit(1);
    }

    cout << "Connection successful... \n";  
    string *msg = new string(1024,'\0');
    string *buff = new string(1024,'\0');

    while(true){
        cout << "Write the message you would like to send \n";
        getline(cin,*msg);
        *msg+='\n';

        Msghandler::send_message(client_fd,msg);
        cout << "Server says: ";
        Msghandler::receive_message(client_fd,buff);

    }

    close(client_fd);
}