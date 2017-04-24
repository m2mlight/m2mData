/*  Examples of use the m2mData library when Arduino is connected to a 
    SMS shield like SIM900, utilizing the following functions:      

     // Store a "value" of a sensor which is identified with "api_key"
    void sendValueSIM900(String api_key, float value);  
   
    // Send an email of an alert which is identified with "api_key". If 
    // "value" is different from -1 then message includes this "value"
    void sendAlertEmailSIM900(String api_key, float value=-1); 

     // Update the "value" of a parameter which is identified with "api_key"
    void updateParameterSIM900(String api_key, float value);

    First, register in www.m2mlight.com to obtain api_key identifiers

    email: contact@m2mlight.com 
*/

#include <GPRS_Shield_Arduino.h>
#include <Wire.h>
#include <m2mData.h>

#define PIN_TX    7
#define PIN_RX    8
#define BAUDRATE  19200

GPRS gprsTest(PIN_TX,PIN_RX,BAUDRATE);//RX,TX,BaudRate

m2mData sensor;
m2mData alert;
m2mData parameter;
String api_key;
float value;
String string_value;

void setup() {
  Serial.begin(19200);
  while(!gprsTest.init()) {
      delay(1000);
      Serial.print("init error\r\n");
  }  
  Serial.println("gprs init success");

  // Store a "value" of a sensor which is identified with "api_key"
  value = 40;
  api_key = String("155FEUqLOfi");
  sensor.sendValueSIM900(api_key, value);

  // Send an email of an alert which is identified with "api_key". If 
  // "value" is different from -1 then message includes this "value"
  api_key = String("166o0pik3Oa");
  alert.sendAlertEmailSIM900(api_key, value=-1); 

  // Update the "value" of a parameter which is identified with "api_key"
  api_key = String("64usiQTcFD");
  string_value = "55";      
  parameter.updateParameterSIM900(api_key, string_value);
  
}

void loop() {

}
