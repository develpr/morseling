import json,morseling,sys

req = morseling.morseling()

# note that raw input uses 'a' and 'b' as delimiters as they fall in normal ascii table
# format is 1b100 (1 reprents a "press" of the key, 100 represnts 100 millisends of a press)
#           0b200 (0 represents a "pause" between presses, 200 represents length of pause)
#           a is the seperator between press/pause and length key pairs

##SOS
input_timings = str(sys.argv[1])
req.send_message_with_timings(input_timings)

