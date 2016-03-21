/*  m2mDataSendEmail.ino 
    Example of using the m2mData library
    Send email alert from m2mlight server
    First register in www.m2mlight.com to obtain api_key
    info@m2mlight.com 
*/

#include <Arduino.h>
#include <m2mData.h>
#include <Ethernet.h>
#include <SPI.h>

m2mData sensor;

// Configure the Ethernet Shield
byte mac[] = { 0x90, 0xA2, 0xDD, 0x0D, 0xD4, 0x61 }; // arduino mac address
byte ip[] = { 192, 168, 1, 21 };                     // arduino ip address

void setup() {
  
    Ethernet.begin(mac, ip); // start the ethernet connection
    Serial.begin(9600);      // enable serial data print  
    delay(1000);
    
}

void loop() {

  String api_key = String("1hmzYpSFq");
  
  Serial.print("api_key:"); Serial.println(api_key); 

   // send alert email
   sensor.sendAlertEmail(api_key);
   delay(30000);
   
}
