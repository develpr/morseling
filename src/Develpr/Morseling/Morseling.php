<?php

namespace Develpr\Morseling;


/**
 *	Author: Kevin Mitchell <kevin@develpr.com>
 */
class Morseling{
	
	protected $baseUri = "http://morsel.develpr.com";
	protected $apiUri = "/api/v1/";
	
	protected $transmissionUri = "transmissions";
	protected $messageUri = "messages";	
	protected $secret = '';
	protected $id = 0;
	protected $httpStatus = 0;
	
	protected $result = null;
	
	public function getResult()
	{
		return $this->result;
	}
	
	/**
	*	Get the latest oldest transmission that has not been marked received
	*	
	*	@param boolean $markReceived should the transmission automatically be marked as received
	*/
	public function getTransmission($markReceived = false)
	{
		$uri = $this->baseUri . $this->apiUri . 'transmissions?direction=received&received=0';

		$this->result = json_decode($this->get($uri));	
	
		if(sizeof($this->result) < 1)
			return false;
		else
		{			
			$this->result = $this->result[0];
			if($markReceived)
				$this->markTransmissionReceived($this->result->id);
			
			return $this->result;		
		}
	}
	
	public function markTransmissionReceived($transmissionId)
	{
		$uri = $this->baseUri . $this->apiUri . 'transmissions/' . $transmissionId;
		
		$data = array(
			'received' => 1
		);
		
		$result = $this->put($uri, $data);
		
		
		
	}
	
	public function createMessage($times)
	{
//		http_build_query
	}
	
	public function generateSignature($uri, array $data)
	{
		$data = http_build_query($data);

		$computedSignature = hash_hmac('md5', $uri . $data, $this->secret);
		return $computedSignature;
	}
	
	public function get($uri)
	{
		$signature = $this->generateSignature($uri, array());

		$ch = curl_init(); 
		curl_setopt($ch, CURLOPT_URL, $uri); 
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1); 
		curl_setopt($ch, CURLOPT_HTTPHEADER, array(
		    'Auth: ' . $this->id . ':' . $signature
	    ));
	
		$output = curl_exec($ch); 
		$this->httpStatus = curl_getinfo($ch, CURLINFO_HTTP_CODE);

		curl_close($ch);
		
		return $output;
	}
	
	public function post($uri, array $data)
	{
		$signature = $this->generateSignature($uri, $data);

		$ch = curl_init(); 
		curl_setopt($ch, CURLOPT_URL, $uri); 
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1); 
		curl_setopt($ch, CURLOPT_HTTPHEADER, array(
		    'Auth: ' . $this->id . ':' . $signature
	    ));
		curl_setopt($ch,CURLOPT_POST, count($data));
		curl_setopt($ch,CURLOPT_POSTFIELDS, http_build_query($data));

		$output = curl_exec($ch); 
		$this->httpStatus = curl_getinfo($ch, CURLINFO_HTTP_CODE);
		
		curl_close($ch);
		
	}
	
	public function put($uri, array $data)
	{
		$signature = $this->generateSignature($uri, $data);

		$ch = curl_init(); 
		curl_setopt($ch, CURLOPT_URL, $uri); 
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1); 
		curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
		curl_setopt($ch, CURLOPT_HTTPHEADER, array(
		    'Auth: ' . $this->id . ':' . $signature
	    ));
		curl_setopt($ch,CURLOPT_POST, count($data));
		curl_setopt($ch,CURLOPT_POSTFIELDS, http_build_query($data));

		$output = curl_exec($ch); 
		$this->httpStatus = curl_getinfo($ch, CURLINFO_HTTP_CODE);
		
		curl_close($ch);
		
		
	}

	public function setId($id)
	{
		$this->id = $id;
	}
	
	public function getId()
	{
		return $this->id;
	}
	
	public function setSecret($secret)
	{
		$this->secret = $secret;
	}
	
	public function getSecret()
	{
		return $this->secret;
	}
	
}
