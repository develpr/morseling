<?php

namespace Develpr\Morseling;

class Morseling{
	
	protected $baseUri = "http://morsel.develpr.com";
	protected $apiUri = "/api/v1/";
	
	protected $transmissionUri = "transmissions";
	protected $messageUri = "messages";	

	public function hello()
	{
		echo "HI";
	}
	
}