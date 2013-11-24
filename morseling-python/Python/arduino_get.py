#!/usr/bin/python
import json,morseling,sys,time

from bridge.bridgeclient import BridgeClient

bridge_setter = BridgeClient()

req = morseling.morseling()

def get_messages():
	transmission = req.get_transmission()

	if(transmission != False):
	    # Get the raw message
	    raw_message = transmission[0]["message"]["raw"]
	    
	    # todo: use Bridge to send this
	    
	    req.receive_transmission(transmission[0]["id"])
    
	    bridge_setter.put("play1", raw_message)
	    bridge_setter.put("replay", raw_message)
	    
	    

time.sleep(10)
get_messages()
time.sleep(10)
get_messages()
time.sleep(10)
get_messages()
time.sleep(10)
get_messages()
time.sleep(10)
get_messages()
