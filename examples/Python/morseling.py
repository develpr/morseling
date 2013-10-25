import hmac,hashlib,urllib2,json,urllib

class morseling:
	base_url = "http://morsel.develpr.com"
	base_api = "/api/v1/"
	url = ""
	key = ""
	data = ""
	id = 1
	message_times = ""
	
	
	def set_url(self, url):
		self.url = url
	
	def get_url(self):
		return self.url
		
	def get_transmission(self, simple=True):
		self.url = self.base_url + self.base_api + "transmissions?direction=received&received=0"
		self.data = ""
		
		signature = self.get_hmac_hash()
		
		request = urllib2.Request(self.url)
		request.add_header('Auth', str(self.id) + ':' + signature)
		
		try:
			response = urllib2.urlopen(request)
			data = json.load(response)
		except Exception, e:
			return False
		
		if len(data) > 0:
			return data
		else:
			return False
			
	def receive_transmission(self, transmission_id):

		self.url = self.base_url + self.base_api + "transmissions/" + transmission_id
		print self.url
		# Prepare the data
		query_args = { 'received':'1', }

		# This urlencodes your data (that's why we need to import urllib at the top)
		self.data = urllib.urlencode(query_args)
		
		signature = self.get_hmac_hash()
		
		request = urllib2.Request(self.url, self.data)
		request.get_method = lambda: 'PUT'
		request.add_header('Auth', str(self.id) + ':' + signature)
		
		try:
			response = urllib2.urlopen(request)
			print "ok"
			# data = json.load(response)
		except Exception, e:
			print "error"
			# data = json.load(e) 
		
		
		
	def get_hmac_hash(self):
		signature = hmac.new(self.key, self.url + self.data, hashlib.md5).hexdigest()
		return signature
