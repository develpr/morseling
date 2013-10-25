Morseling - Python
==============

##A simple python script(s) to allow basic communication with morsel.develpr.com.

###Messages vs Transmissions

It's worth noting that Morsel has the concept of a `Message` and `Transmission`. Simply put, Messages are the things that we care about, because a Message contains all of the information about the message itself (key press times, english translation of the message, etc). A Transmission is less interesting because it is just a record of a Message being sent from a particular user, to a different user. The reason we have both Messages and Transmissions is because it's possible (for example) that a Message should be sent to multiple users, so we need a way to keep track of each Transmission that was sent out (even though each Transmission is tied to a single Message). Long story short, this isn't super important, but if you notice the words/Transmission/Message being used in different ways, you know what these things represent.


###Basics

This is a very simple python script that will handle the following tasks:

1. Get the latest Transmission for a given user
2. Optionally mark the latest Transmission as being read

Soon, we will add the ability to

1. Add a new Transmission/Message

###Files

This is a very simple python script/helper/tool. The files included are:

* `MD5_Hash/MD5_Hash.ino` - A simple MD5 hashing library
* `Python/morseling.py` - The useful python script - the real meat of this
* `Python/get_transmission_example.py` - A simple example that retrieves the latest Transmission (and corresponding message!) and marks it as read


###To Use

To run the example script (or to use the morseling.py script directly in your own python scripts), you'll first need:

1. Edit morseling.py to add your `key` (aka secret key), which you can access by logging into http://morsel.develpr.com and going to your account area.
2. Edit the morseling.py file and set the `id` to be your user ID (again, access by visiting your account on http://morsel.develpr.com)
3. Confirm that the `base_url` and `base_api` are correct (they should be out of the box, but if you want to use a different version of the API or want to use an instance of Morsel other then the "official" version)

That's it for setup. All that's left to do is run

`python get_transmission_example.py`

From a command line. This is assuming the files are in the original relative locations (the get_transmission_example.py script will need to use morseling.py, and morseling.py will need to use the MD5_Hash library).

This simple example has very little output, but if you have a message that was sent to you, after running this example you will see that the message should now be marked as "received" in your account.


