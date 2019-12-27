#!/usr/bin/python
import serial
import hal
import sys
import time


PORT = "/dev/ttyUSB0"
#allow the port to be overridden
if len(sys.argv) > 1:
 PORT = sys.argv[1]

#Establish serial link
ser = serial.Serial(PORT, 115200, timeout=2)

c = hal.component("usbprobe")
c.newpin("probe-in",hal.HAL_BIT,hal.HAL_IN)
c.newpin("probe-in-not",hal.HAL_BIT,hal.HAL_IN)
c.ready()

try:
  while 1:
    time.sleep(.002) 
    #Check to see if we have a message waiting from the Arduino  
    while ser.inWaiting():
      contact = ser.read(1)
      if(contact == '0'):
        c['probe-in'] = 0
        c['probe-in-not'] = 1
      if(contact == '1'):
        c['probe-in'] = 1
        c['probe-in-not'] = 0
      
except (KeyboardInterrupt,):
    raise SystemExit, 0
