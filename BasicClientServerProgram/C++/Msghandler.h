#ifndef MSGHANDLER_H
#define MSGHANDLER_H

#include<iostream>
#include<string>
#include<vector>
#include<malloc.h>
#include<unistd.h>
#include<stdbool.h>
#include<cstring>


#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


using std::cin;
using std::cout;
using std::end;
using std::string;

class Msghandler{
    
    public:

        static void send_message(int fd,string *message){
            
            int total = 0;
            int bytes = 0;
            
            while(total < (*message).length()){
                
                bytes = send(fd,message->c_str(),(*message).length(),0);

                 if(bytes == -1){
                    perror("Error sending message \n");
                    exit(1);
                }

                total+=bytes;
            }

        }

        static void receive_message(int fd,string *buffer){

            int bytes = 0;
            string *s = new string(1024,'\0');
            bool b = false;

            while(!b){
                
                bytes=recv(fd,&(*s)[0],(*s).length(),0);
                if(bytes == -1){
                    perror("Error receiving message \n");
                    exit(1);
                }

                s->resize(bytes);
                *buffer+=*s;

                if(s->back() == '\n')
                b = true;
                else s->assign(1024,'\0');
            }

            cout << *buffer << "\n";
            buffer->assign(1024,'\0');
        }
};

#endif