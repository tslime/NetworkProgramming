import os
import sys
import socket
import select

from inc.Msghandler import Msghandler

HOST = "IP_NUM"
PORT = PORT_NUM
c_num = 0
fd_clients = {}


try:
    server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    server.bind((HOST,PORT))
    server.listen()
    socket_list = [server]

except socket.error as e1:
    print("Socket error: ",e1,end="\n")



while True:
    read_events,write_events,errors = select.select(socket_list,[],[]) 
        
    for s in read_events:
        try:
            if s == server:
                fd_client,c_addr = server.accept()
                print("New client conneced....\n")
                socket_list.append(fd_client)
                c_num = c_num + 1
                fd_clients[fd_client] = c_num
            else:
                msg = Msghandler(1024)
                m = msg.receive_message(s)
                if m == "":
                    socket_list.remove(s)
                    s.close()
                else:
                    print("Client ",fd_clients[s]," says: ",m)
                    msg.send_message(s,"Message received \n")
    
        except socket.error as e2:
            print("Socket error: ",e2,end="\n")
            if s in socket_list:
                socket_list.remove(s)
                s.close()


