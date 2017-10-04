# Server Functions and M2mdata Arduino library 

Server functions (http calls) and a M2M Arduino library allow to use M2Mlight platform. First, you need to register the sensor, actuator or alert and obtain the api_key values in m2mlight.com platform.

These server functions and Arduino library can be used to send and receive values between the m2mlight platform and a program in a microcontroller or computer (arduino, raspberry, esp8266, etc.) or in a mobile device (tablet or smartphone).

The communication with the m2mlight platform can be using Ethernet (Arduino Ethernet or ENC28J60 shields) or GSM (SIM900 GSM shield).


# 1. Server Functions

To upload/download data to m2mlight platform using http from a browser or program, you can employ the following server functions:

a) Sensors:

- Name: send_sensor_value

  Description: upload (save) a single sensor "value" of a sensor identified by "api_key"

  Call example: https://m2mlight.com/iot/send_sensor_value?api_key=250hhCIHeO&value=200 
  
  Return: 0 if a value is successfully inserted, -1 for invalid api_key or disable status, -2 if the interval between two values is less than 10 seconds.


- Name: send_sensor_location

  Description: upload (save) a location sensor "latitude" and "longitude of a sensor identified by "api_key"

  Call example: https://m2mlight.com/iot/send_sensor_location?api_key=26hyCIHeO&latitude=-0.158382&longitude=-78.45534
  
  Return: 0 if values are successfully inserted, -1 for invalid api_key or disable status, -2 if the interval between two values is less than 10 seconds.


- Name: read_sensor_value

  Description: return the last stored value of a single sensor identified by "api_key"
  
  Call example: https://m2mlight.com/iot/read_sensor_value?api_key=300uhxXsAH


b) Actuators:

- Name: read_actuator_hour

  Description: return the start hour (HH:MM) of an actuator identified by "api_key"
  
  Call example: http://m2mlight.com/iot/read_actuator_hour?api_key=180SgN4pHk

- Name: update_actuator_hour

  Description: update the start hour "start_hour" of the actuator identified by "api_key"
  
  Call example: http://m2mlight.com/iot/update_actuator_hour?api_key=a6ruhxX&start_hour=10:30
  
  Return: -1 if HH:MM format is not correct


c) Alerts:

- Name: pg_send_email
- Description: send an alert email identified by "api_key" and insert a log. Optional you can
  also send  a "value" 
- Call examples: https://m2mlight.com/iot/pg_send_email?api_key=180Gx5CIHeO 
                 https://m2mlight.com/iot/pg_send_email?api_key=180Gx5CIHeO&value=57


You can use these functions inside an C++ code (Arduino or Esp8266) or Python code (Raspberry).  You can see and example in the file: example_server_functions_with_a_sensor.py. If you are using an Arduino is better to use the M2MData library.


# 2. M2mData Library

The m2mData Arduino Library allows you to store and retrieve data of sensors, alerts and parameters to/from m2mlight.

You have to create a m2mData folder in your Arduino Libraries and download the files: m2mData.h and m2mData.cpp. You can see examples of use in the following files: examples_use_m2mdata.ino and examples_use_m2mdata_SIM900.ino.

A. When arduino is connected to Internet, you have the following functions: 

a) Sensors:

 // Store a "value" of a sensor which is identified with "api_key"
 
  void sendValue(String api_key, float value);  

 // Return the last value of a sensor which is identified with "api_key"
 
 float readValue(String api_key);


b) Alerts:
    
 // Send an email of an alert which is identified with "api_key". If 
 // "value" is different from -1 then message includes this "value"
 
 void sendAlertEmail(String api_key, float value=-1); 


c) Parameters:

 // Return the value of a parameter which is identified with "api_key"
 
 String readParameter(String api_key);

 // Update the "value" of a parameter which is identified with "api_key"
 
 void updateParameter(String api_key, String value);
 


B. When arduino is connected to a GSM shield like SIM900, you have the following functions:

a) Sensors:

// Store a "value" of a sensor which is identified with "api_key"

void sendValueSIM900(String api_key, float value);  

b) Alerts:

// Send an email of an alert which is identified with "api_key". If 
// "value" is different from -1 then message includes this "value"

void sendAlertEmailSIM900(String api_key, float value=-1); 

c) Parameters:

// Update the "value" of a parameter which is identified with "api_key"

void updateParameterSIM900(String api_key, String value);
