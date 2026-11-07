import os
import sys

os.environ["MAVLINK20"] = "1"

from pymavlink import mavutil
import time


master = mavutil.mavlink_connection("COM11", baud=115200)

print("Waiting for heartbeat")
master.wait_heartbeat()
print("Connected")

target_system = master.target_system
target_component = master.target_component

while True:
    master.mav.command_int_send(
        target_system,        
        target_component,     
        0,
        7001,          # PUT THE COMMAND ID HERE
        0,0,0,0,0,0,0,0,0 # We could use these params to either have the current and temp on the same command or to even select which sensor we want
    )
    msg = master.recv_match(blocking=True)
    if msg is not None and msg.get_type() == "STATUSTEXT":
        print(msg.get_type(), msg.text)

    master.mav.command_int_send(
        target_system,        
        target_component,     
        0,
        7002,          
        0,0,0,0,0,0,0,0,0 
    )
    msg = master.recv_match(blocking=True)
    if msg is not None and msg.get_type() == "STATUSTEXT":
        print(msg.get_type(), msg.text)
 