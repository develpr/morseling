import hmac,hashlib,urllib2,json

class morseling:
	base_url = "http://morsel.com"
	base_api = "/api/v1/"
	url = "";
	key = "sf9k03asgasfk02";
	data = "";
	message_times = "";
	
	
	def set_url(self, url):
		self.url = url
	
	def get_url(self):
		return self.url
		
	def get_transmission(self, simple=True):
		self.url = self.base_url + self.base_api + "transmissions?received=0"
		data = self.url
		signature = self.get_hmac_hash()
		
		request = urllib2.Request(self.url)
		request.add_header('Auth', '1:' + signature)
		request.add_header('Cookie', 'XDEBUG_SESSION=PHPSTORM')
		
		try:
			response = urllib2.urlopen(request)
			data = json.load(response)
		except Exception, e:
			data = json.load(e) 
		
		if 0 in data:
			return data
		else:
			return false
		
		
	def get_hmac_hash(self):
		signature = hmac.new(self.key, self.url + self.data, hashlib.md5).hexdigest()
		return signature
	