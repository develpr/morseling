#!/usr/bin/python
import json,morseling,sys,time

from bridge.bridgeclient import BridgeClient

bridge_setter = BridgeClient()

req = morseling.morseling()

BRIDGE_CHARACTER_LIMIT = 250

def get_messages():
    
	transmission = req.get_transmission()

	if(transmission != False):
        # Get the raw message
        raw_message = transmission[0]["message"]["raw"]

        # todo: use Bridge to send this

        req.receive_transmission(transmission[0]["id"])

        # Because of an apparent limit in Arduino's Bridge library when using set/get, we're going to
        # split the message up into 250 character parts
        playIndex = 0

        while(raw_message a len(raw_message) > 0):            
            bridge_setter.put("play1" + `playIndex`, raw_message[0:BRIDGE_CHARACTER_LIMIT])
            bridge_setter.put("replay" + `playIndex`, raw_message[0:BRIDGE_CHARACTER_LIMIT])
            raw_message = raw_message[BRIDGE_CHARACTER_LIMIT:]
    	    

time.sleep(10)
get_messages()
time.sleep(30)
get_messages()
