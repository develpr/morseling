#!/usr/bin/python

import json,morseling,sys,time

from bridge.bridgeclient import BridgeClient

bridge_client = BridgeClient()

req = morseling.morseling()

# note that raw input uses 'a' and 'b' as delimiters as they fall in normal ascii table
# format is 1b100 (1 reprents a "press" of the key, 100 represnts 100 millisends of a press)
#           0b200 (0 represents a "pause" between presses, 200 represents length of pause)
#           a is the seperator between press/pause and length key pairs

def send_messages():
    
    readIndex = 0;
    message = ""
    message_buffer = bridge_client.get("message1" + `readIndex`)
    
    while(len(message_buffer) > 0)
        message = message + message_buffer 
        #send message via morsel api
        bridge_client.put("message1" + `readIndex`, '')
        readIndex++
        message_buffer = bridge_client.get("message1" + `readIndex`)
        
    if(len(message) > 0)
	    req.send_message_with_timings(message)
	    bridge_client.put('message1' + `readIndex`, '')
                        
	        
send_messages()
time.sleep(20)
send_messages()