#!/usr/bin/python
import json,morseling,sys

from bridge.bridgeclient import BridgeClient

bridge_setter = BridgeClient()

req = morseling.morseling()

# note that raw input uses 'a' and 'b' as delimiters as they fall in normal ascii table
# format is 1b100 (1 reprents a "press" of the key, 100 represnts 100 millisends of a press)
#           0b200 (0 represents a "pause" between presses, 200 represents length of pause)
#           a is the seperator between press/pause and length key pairs

transmission = req.get_transmission()

if(transmission != False):
    # Get the raw message
    raw_message = transmission[0]["message"]["raw"]
    
    # todo: use Bridge to send this
    
    req.receive_transmission(transmission[0]["id"])
    
    bridge_setter.put("play1", raw_message)
