#!/bin/bash

function checkmessages() {
	
	lockfile -r 0 /tmp/the.lock || echo ""
	
	python morseling-python/Python/get_transmission_example.py
	
	rm -f /tmp/the.lock
	
}


while [ 1 ]; do
	checkmessages
    sleep 15
done


