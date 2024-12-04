from websocket_server import WebsocketServer
import json
import numpy as np
from time import sleep
import copy
import pythonosc
from pythonosc.dispatcher import Dispatcher
from pythonosc.osc_server import BlockingOSCUDPServer

from scipy.spatial.transform import Rotation

client_global = None
# Called for every client connecting (after handshake)
def new_client(client, server):
    global client_global 
    print("New client connected and was given id %d" % client['id'])
    client_global = client# server.send_message_to_all("Hey all, a new client has joined us")


# Called for every client disconnecting
def client_left(client, server):
    global client_global
    if client == client_global:
        client_global = None
        
    print("Client(%d) disconnected" % client['id'])


# Called when a client sends a message
def message_received(client, server, message):
	if len(message) > 200:
		message = message[:200]+'..'
	print("Client(%d) said: %s" % (client['id'], message))

def vicon_handler(address, *args):
    # print("\n\n------ Address -----")
    # print(address)
    
    # print("\n\n------ Args -----")
    xyz = args[:3]
    rot_vector = copy.copy((args[3:]))
    
    qx, qy, qz, theta = Rotation.from_matrix(
        [
            [args[3], args[4], args[5]],
            [args[6], args[7], args[8]],
            [args[9], args[10], args[11]]
        ],
    ).as_quat()
    
    # print(roll, pitch, yaw)
    # print("-"*50)
    
    msg = {
        "x": xyz[0] / 10,
        "y": xyz[1] / 10,
        "z": xyz[2] / 10,
        "qx" : -qx,
        "qy": -qy,
        "qz": -qz,
        "theta": theta 
    }
    msg_str = json.dumps(msg)
    
    server.send_message_to_all(msg_str)
    
    

# UE5 <---> Python
PORT=8000
server = WebsocketServer(port = PORT)
server.set_fn_new_client(new_client)
server.set_fn_client_left(client_left)
server.set_fn_message_received(message_received)
server.run_forever(threaded=True)


# VICON <---> Python
disp = Dispatcher()
disp.map("/vicon/seg/Kutija/kutija", vicon_handler )
osc_server = BlockingOSCUDPServer(dispatcher= disp, server_address=('', 7000))
osc_server.serve_forever() # blokirajuca funkcija
