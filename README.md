Morseling API Helper
====================

Purpose
-------

This package is made to allow simple communication with the Morsel API.

With it, you can:

1. create a new message
2. get a transmission
3. update a transmission to be read

Additionally, you should be able to easily fork/modify the code to add additional features, as allowed by the [Morsel API](http://morsel.develpr.com/docs).

Use
---

Usage is simple:
	
	//Create an instance of the Morseling API helper
	$morseling = new Develpr\Morseling\Morseling;

(You can find your Morsel id and shared secret at [your Morsel account](http://morsel.develpr.com/account))
	
	//Set your Morsel ID
	$morseling->setId(1);

	//Set you shared secret
	$morsel->setSecret('bluemyself');
	
	//Now we're all set! Let's get the latest transmission
	$transmission = $morsel->getTransmission(false);
	
	if($transmission)
		echo "The latest transmission said " . $transmission->message->text;
	else
		echo "no new transmissions!";
	


Passing in an optional boolean `true` will automatically mark the transmission as received.

	//Now we're all set! Let's get the latest transmission and mark it as received
	$morsel->getTransmission(true);


