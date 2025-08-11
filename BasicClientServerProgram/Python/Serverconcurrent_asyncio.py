import os
import sys
import asyncio

from inc.Msghandler import Msghandler
from functools import partial

SERVER_ADDR = "UP_NUM"
PORT = PORT_NUM
c_num = 0

async def handle_client(r,w):
    global c_num
    c_num +=1
    c_id = c_num
    print("client connected....\n")
    
    while True:
        msg = await r.readline()
        print("client ",c_id," says: ",msg.decode())
        w.write("Message received \n".encode())
        await w.drain()
    
    w.close()

async def launch_server():
    server = await asyncio.start_server(handle_client,SERVER_ADDR,PORT)
    await server.serve_forever()
    
    
asyncio.run(launch_server())
