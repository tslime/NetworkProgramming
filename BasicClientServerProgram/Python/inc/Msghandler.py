import os
import sys
import socket


class Msghandler:
    
    def __init__(self,k:int):
        self.size = k
        self.buffer = ""

    def send_message(self,s:socket,msg):
        s.sendall(msg.encode())

    def receive_message(self,s:socket):
        m = ""
        b = False
        
        while not b:
            self.buffer = s.recv(self.size)
            m = m + self.buffer.decode()
            if (self.buffer.decode()).endswith("\n"):
                b = True
            else:
                self.buffer = ""

        return m