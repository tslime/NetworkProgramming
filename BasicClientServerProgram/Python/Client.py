import os
import sys
import socket

from inc.Msghandler import Msghandler

HOST_ADDR = "IP_NUM"
PORT = PORT_NUM
c_msg = Msghandler(1024) 

try:
    c = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    c.connect((HOST_ADDR,PORT))

    while True:
        print("Write the message you want to send: ")
        m = input()
        m = m + "\n"
        c_msg.send_message(c,m)
        temp = c_msg.receive_message(c)
        print(temp)
        print()

except socket.error as e:
    print("Socket error: ",e,end="\n")
finally:
    c.close()

