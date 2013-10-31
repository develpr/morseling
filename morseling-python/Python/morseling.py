import hmac,hashlib,urllib2,json,urllib

class morseling:
    #Your secret key - get this from http://morsel.develpr.com
    key = ""
    #Your user ID, get this from http://morsel.develpr.com also
    id = 0
    #The base URL for Morsel - may change over time
    base_url = "http://morsel.develpr.com"
    #The endpoint for the version of the API we're using
    base_api = "/api/v1/"
    url = ""
    data = ""

    message_times = ""


    def set_url(self, url):
        self.url = url

    def get_url(self):
        return self.url

    def get_transmission(self, simple=True):
        #We're getting transmissions that have been sent to us, and have not yet been marked as received
        self.url = self.base_url + self.base_api + "transmissions?direction=received&received=0"
        self.data = ""

        #generate a hmac signature for the request
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
            
        except Exception, e:
            print "error"
       
    """
    Send a message with a series of times (key presses and pauses)
    """
    def send_message_with_timings(self, times):
        
        self.url = self.base_url + self.base_api + "messages"
        self.data = ""
        
        # Prepare the data
        query_args = { 'raw':times, }
        
        # This urlencodes your data (that's why we need to import urllib at the top)
        self.data = urllib.urlencode(query_args)
        
        signature = self.get_hmac_hash()

        request = urllib2.Request(self.url, self.data)
        request.get_method = lambda: 'POST'
        request.add_header('Auth', str(self.id) + ':' + signature)
        
        try:
            response = urllib2.urlopen(request)
            data = json.load(response)
            print "sent"
            
        except Exception, e:
            print "not sent"
                        
        if len(data) > 0:
            return data
        else:
            return False
            

    """
    Send a message with a text string
    """
    def send_message_with_text(self, text):
        
        self.url = self.base_url + self.base_api + "messages"
        self.data = ""
        
        # Prepare the data
        query_args = { 'text':text, }
        
        # This urlencodes your data (that's why we need to import urllib at the top)
        self.data = urllib.urlencode(query_args)
        
        signature = self.get_hmac_hash()

        request = urllib2.Request(self.url, self.data)
        request.get_method = lambda: 'POST'
        request.add_header('Auth', str(self.id) + ':' + signature)
        
        try:
            response = urllib2.urlopen(request)
            data = json.load(response)
            print "sent"
            
        except Exception, e:
            print "not sent"
                        
        if len(data) > 0:
            return data
        else:
            return False
                        
            

    def get_hmac_hash(self):
        signature = hmac.new(self.key, self.url + self.data, hashlib.md5).hexdigest()
        return signature
