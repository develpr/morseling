import json,morseling

req = morseling.morseling()
transmission = req.get_transmission(True)

if(transmission != False):
	req.receive_transmission(transmission[0]["id"])


