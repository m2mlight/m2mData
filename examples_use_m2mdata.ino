/*  Examples of use the m2mData library, when Arduino is connect to Internet, 
    utilizing the following functions:      
    
-    void sendValue(String api_key, float value);  
-    float readValue(String api_key);
-    void sendAlertEmail(String api_key, float value=-1); 
-    void updateParameter(String api_key, float value);
-    float readParameter(String api_key);

    First, register in www.m2mlight.com to obtain api_key identifiers
    
    Email:contact@m2mlight.com
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
String string_value;

// Configure the Ethernet Shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xB4, 0x61 }; // arduino mac address
byte ip[] = { 192, 168, 1, 17 };                     // arduino ip address

void setup() {
  
    Ethernet.begin(mac, ip); // start the ethernet connection
    Serial.begin(9600);      // enable serial data print  
    delay(500);

    // Store a "value" of a sensor which is identified with "api_key"
    value = 40;
    api_key = String("1FEUqLOfi");
    sensor.sendValue(api_key, value);

    // Return the last value of a sensor which is identified with "api_key"
    api_key = String("1FEUqLOfi");
    value = sensor.readValue(api_key);
    Serial.print("readValue value:"); Serial.println(value); 

    // Send an email of an alert which is identified with "api_key". If 
    // "value" is different from -1 then message includes this "value"
    api_key = String("16o0pik3Oa");
    alert.sendAlertEmail(api_key, value=-1); 

    // Update the "value" of a parameter which is identified with "api_key"
    api_key = String("6usiQTcFD");
    string_value = "13";      
    parameter.updateParameter(api_key, string_value);

    // Return the value of a parameter which is identified with "api_key"
    api_key = String("6usiQTcFD");    
    string_value = parameter.readParameter(api_key);
    Serial.print("readParameter value:"); Serial.println(string_value); 

}

void loop() {

}
