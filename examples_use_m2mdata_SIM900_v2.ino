/*  Examples of use the m2mData library when Arduino is connected to a 
    SMS shield like SIM900, utilizing the following functions:      

    // Store a single "value" of a sensor identified with "api_key"
    void sendValueSIM900(char api_key[], float value);  
   
    // Store "latitude" and "longitud" of a sensor is identified with "api_key"
    void sendCoordinatesSIM900(char api_key[], float latitude, float longitude);

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

char api_key_sensor[] = "1FEUqLOfi";
float value;
float latitude, longitude;

void setup() {
  Serial.begin(19200);
  while(!gprsTest.init()) {
      delay(1000);
      Serial.print("init error\r\n");
  }  
  Serial.println("gprs init success");

  // Store a single "value" of a sensor identified with "api_key"
  value = 40;
  sensor.sendValueSIM900(api_key_sensor, value);

  // Store coordinates of a sensor identified with "api_key"
  latitude = -0.194195;
  longitude = -78.4834;
  sensor.sendCoordinatesSIM900(api_key_sensor, latitude, longitude);  

  
}

void loop() {

}
