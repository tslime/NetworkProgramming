import os
import sys
import socket



SERVER_ADDR = "192.168.2.57"
PORT = 6379

try:
    s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.bind((SERVER_ADDR,PORT))
    s.listen()
    fd_client, addr = s.accept()

    print("A Client connected....\n\n")
    while True:
        msg = fd_client.recv(1024)
        print("client says: ",msg.decode(),end="\n")
        fd_client.sendall("Message received \n".encode()) 
    
    s.close()

except socket.error as e:
    print("Socket error: ",e,end="\n")
finally:
    s.close()

