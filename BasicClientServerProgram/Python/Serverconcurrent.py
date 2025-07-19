import os
import sys
import asyncio

from inc.Msghandler import Msghandler
from functools import partial

SERVER_ADDR = "192.168.2.57"
PORT = 6379
c_num = 0

async def handle_client(r,w):
    global c_num 
    c_num = c_num + 1
    print("client connected....\n")

    while True:
        msg = await r.readline()
        print("client ",c_num," says: ",msg.decode())
        w.write("Message received \n".encode())
        await w.drain()
    
    w.close()

async def main():
    c_num = 0
    server = await asyncio.start_server(handle_client,SERVER_ADDR,PORT)
    await server.serve_forever()
    
    
asyncio.run(main())
