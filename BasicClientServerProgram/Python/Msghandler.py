import os
import sys
import socket


class Msghandler:
    
    def __init__(s:int):
        self.size = s
        self.buffer = None

    def send_message(s:socket,msg):
        s.sendall(msg.encode())

    def receive_message(s:socket):
        temp = None
        m = None
        b = False
        
        while not b:
            temp = s.recv(self.size)
            m = m + temp
            if temp.endswith("\n"):
                b = True

        return m

"""Testing"""

print("test \n")