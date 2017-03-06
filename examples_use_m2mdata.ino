/*  Examples of use the m2mData library, including the following functions:      
    
-    void sendValue(String api_key, float value);  
-    float readValue(String api_key);
-    void sendAlertEmail(String api_key, float value=-1); 
-    void updateParameter(String api_key, float value);
-    float readParameter(String api_key);

    First register in www.m2mlight.com to obtain api_key identifiers
    info@m2mlight.com 
*/

#include <Arduino.h>
#include <m2mData.h>
#include <Ethernet.h>
#include <SPI.h>

m2mData sensor;
m2mData alert;
m2mData parameter;
String api_key;
float value;

// Configure the Ethernet Shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xB4, 0x61 }; // arduino mac address
byte ip[] = { 192, 168, 1, 17 };                     // arduino ip address

void setup() {
  
    Ethernet.begin(mac, ip); // start the ethernet connection
    Serial.begin(9600);      // enable serial data print  
    delay(500);
    
}

void loop() {

    // Store a "value" of a sensor which is identified with "api_key"
    value = 40;
    api_key = String("155FEUqLOfi");
    sensor.sendValue(api_key, value);

    // Return the last value of a sensor which is identified with "api_key"
    api_key = String("155FEUqLOfi");
    value = sensor.readValue(api_key);
    Serial.print("readValue value:"); Serial.println(value); 

    // Send an email of an alert which is identified with "api_key". If 
    // "value" is different from -1 then message includes this "value"
    api_key = String("166o0pik3Oa");
    alert.sendAlertEmail(api_key, value=-1); 

    // Update the "value" of a parameter which is identified with "api_key"
    api_key = String("64usiQTcFD");
    value = 13;      
    parameter.updateParameter(api_key, value);

    // Return the value of a parameter which is identified with "api_key"
    api_key = String("64usiQTcFD");    
    value = parameter.readParameter(api_key);
    Serial.print("readParameter value:"); Serial.println(value); 

    delay(15000);
   
}
