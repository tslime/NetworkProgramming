import os
import sys
import socket
import threading

from inc.Msghandler import Msghandler

SERVER_ADDR = "IP_NUM"
PORT = PORT_NUM
msg = Msghandler(1024)
c_num = 0

def handle_client(soc,c_num):
    while True:
        m = msg.receive_message(fd_client)
        print("client ",c_num," says: ",m,end="\n")
        msg.send_message(fd_client,"Message received \n")
    
    soc.close()




try:
    s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.bind((SERVER_ADDR,PORT))
    s.listen()

    while True:
        fd_client, client_addr = s.accept()
        print("A Client connected....\n")
        c_num  = c_num+1
        t = threading.Thread(target=handle_client,args=(fd_client,c_num))
        t.start()
    
    s.close()

except socket.error as e:
    print("Socket error: ",e,end="\n")
finally:
    s.close()

