#!/usr/bin/python

import json,morseling,sys

from bridge.bridgeclient import BridgeClient

bridge_client = BridgeClient()

req = morseling.morseling()

# note that raw input uses 'a' and 'b' as delimiters as they fall in normal ascii table
# format is 1b100 (1 reprents a "press" of the key, 100 represnts 100 millisends of a press)
#           0b200 (0 represents a "pause" between presses, 200 represents length of pause)
#           a is the seperator between press/pause and length key pairs


message1 = bridge_client.get("message1")
message2 = bridge_client.get("message2")
message3 = bridge_client.get("message3")

if(message1):
        #send message via morsel api
	req.send_message_with_timings(message1)
	bridge_client.put('message1', '')
                        
if(message2):
	#send message via morsel api
	req.send_message_with_timings(message2)
	bridge_client.put('message2', '')
                                                
                                                
if(message3):
	#send this message too
	req.send_message_with_timings(message3)
	bridge_client.put('message3', '')
