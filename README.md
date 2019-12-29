# LinuxCNC-USB-Probe

## CNC Mill USB probe

Inexpensive probe using ESP8266 an opto isolator, small DC-DC power supply and a few resistors.

Arduino should work too just change pins

User space HAL module confirmed fast enough for probing

Tested G38.1 probing on LinuxCNC 2.7.14

Update your mill config .ini file with:
```
[HAL]
 ...
 HALFILE=usbprobe.hal
```
