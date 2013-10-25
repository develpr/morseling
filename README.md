Morseling - Arduino
===========

##A simple Arduino sketch for recording key presses and transmissing them

This is a simple sketch that can be used as the bases for more complex sketches, likely for the purposes of simulating a morse code "key." The sketch is simple, basically listening for a button press, then continueing to listen for additional button presses and recording the length of button presses as well as the length of time between button presses. After a 5 second delay, these button presses are "transmitted" to the serial output.

This will be changed/modified in time to work with the Arduino Yun, and both send and receive transmissions using the Bridge library.