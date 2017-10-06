/*  Examples of use the m2mData library, when Arduino is connect to Internet, 
    utilizing the following functions:      
    
 // Store a "value" of a sensor identified with "api_key"
    void sendValue(char api_key[], float value);  

    // Store coordinates of a sensor identified with "api_key"
    void sendCoordinates(char api_key[], float latitude, float longitude);  

    // Return the last value of a sensor identified with "api_key"
    float readValue(char api_key[]);

    // Return the star hour (HH:MM) of an actuator identified with "api_key"
    String readActuatorHour(char api_key[]);

    // Update the start hour "start_hour" of an actuator identified with "api_key"
    void updateActuatorHour(char api_key[], char start_hour[]);

    // Send an email about an action of an actuator identified with "api_key".
    void sendEmailAction(char api_key[]); 

    // Send an email of an alert identified with "api_key".
    void sendEmailAlert(char api_key[]); 

    First, register in www.m2mlight.com to obtain api_key identifiers
    
    Email:contact@m2mlight.com
*/

#include <Arduino.h>
#include <m2mData.h>
#include <Ethernet.h>
#include <SPI.h>

m2mData sensor;
m2mData actuator;
m2mData alert;

char api_key_sensor[] = "1FEUqLOfi";
char api_key_actuator[] = "2FEUqLOfi";
char api_key_alert[] = "3FEUqLOfi";
float value;
float latitude, longitude;
String string_value;

// Configure the Ethernet Shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xB4, 0x61 }; // arduino mac address
byte ip[] = { 192, 168, 1, 17 };                     // arduino ip address

void setup() {
  
    Ethernet.begin(mac, ip); // start the ethernet connection
    Serial.begin(9600);      // enable serial data print  
    delay(500);

    // Store a "value" of a sensor identified with "api_key"
    value = 40;
    sensor.sendValue(api_key_sensor, value);

    // Store coordinates of a sensor identified with "api_key"
    latitude = -0.194195;
    longitude = -78.4834;
    sensor.sendCoordinates(api_key_sensor, latitude, longitude);  

    // Get the last value of a sensor identified with "api_key"
    value = sensor.readValue(api_key_sensor);
    Serial.print("value:"); Serial.println(value); 

    // Get the star hour (HH:MM) of an actuator identified with "api_key"
    string_value = actuator.readActuatorHour(api_key_actuator);
    Serial.print("string_value:"); Serial.println(string_value);
    
    // Update the start hour "start_hour" of an actuator identified with "api_key"
    char start_hour[] = "10:15";
    actuator.updateActuatorHour(api_key_actuator, start_hour);    

    // Send an email about an action of an actuator identified with "api_key".
    actuator.sendEmailAction(api_key_actuator); 

    // Send an email of an alert identified with "api_key".
    alert.sendEmailAlert(api_key_alert); 

}

void loop() {

}
