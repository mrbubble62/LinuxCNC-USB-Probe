/*
ESP8266 USB Probe

PINS for ESP8266 D1 Mini
PROBE ACTIVITY LED Red
CONNECTED LED green 

COMMUNICATION 115200 BAUD
single byte OUT on probe contact
Char "1"
Char "0"

*/
#include <Arduino.h>

#define PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))
#define DIRECT_PIN_READ(base, mask)     (((*(base)) & (mask)) ? 1 : 0)
#define PIN_TO_BASEREG(pin)             (portInputRegister(digitalPinToPort(pin)))
#define LEDR  0 // D3 GPIO0 sinks LED current via 330 ohm pullup
#define LEDG  2 // D4 GPIO2 sinks LED current via 220 ohm pullup

const uint8_t interruptPin = 12;  //connected to Opto isolator pin 6 with 200 Ohm pullup
bool contact = false; // control red LED

void ICACHE_RAM_ATTR handleInterrupt() {
  if(DIRECT_PIN_READ(PIN_TO_BASEREG(interruptPin), PIN_TO_BITMASK(interruptPin))){
    Serial.print('1');
    contact=true;
  }
  else{
    Serial.print('0');
    contact=false;
  }
  digitalWrite(LEDR,contact);
}

void setup() {
  pinMode(interruptPin, INPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDR, OUTPUT);
  digitalWrite(LEDG,HIGH);
  digitalWrite(LEDR,digitalRead(interruptPin));
  delay(500);
  Serial.setDebugOutput(false);
  Serial.begin(115200);
  delay(500);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, CHANGE);
}

void loop() 
{ 
  digitalWrite(LEDG,LOW); //LED on 
  delay(15); 
  digitalWrite(LEDG,HIGH); //LED off 
  delay(250);
}
