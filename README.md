# M2mData Library and Server Functions 

First, you have to register the sensor, alert or parameter and obtain the api_key in m2mlight.com platform.


# M2mData Library

The m2mData Arduino Library allows you to store and retrieve data of sensors, alerts and parameters to/from m2mlight.

These are the five functions in the m2mData library, used when arduino is connected to Internet:

a) Sensors

 // Store a "value" of a sensor which is identified with "api_key"
 void sendValue(String api_key, float value);  

 // Return the last value of a sensor which is identified with "api_key"
 float readValue(String api_key);


b) Alerts
    
 // Send an email of an alert which is identified with "api_key". If 
 // "value" is different from -1 then message includes this "value"
 void sendAlertEmail(String api_key, float value=-1); 


c) Parameters

 // Return the value of a parameter which is identified with "api_key"
 float readParameter(String api_key);

 // Update the "value" of a parameter which is identified with "api_key"
 void updateParameter(String api_key, float value);
 
First, you can create a m2mData folder in your Arduino Libraries and download the files: m2mData.h and m2mData.cpp. You can see examples of use in examples_use_m2mdata.ino file.


# Server Functions

Server functions can be used to send and receive values between the m2mlight platform and a program in a microcontroller (arduino, raspberry, etc.) or in a mobile device (tablet or smartphone).

To upload/download data to m2mlight platform using http from a browser or program, you can employ the following server functions:

a) Sensors

- Name: pg_send_value
- Description: upload (save) a sensor "value" of a sensor identified by "api_key"
- Call example: https://m2mlight.com/iot/pg_send_value?api_key=250Gx5CIHeO&value=200 

- Name: pg_receive_value
- Description: return the last stored value of a sensor identified by "api_key". Return 0 otherwise
- Call example: https://m2mlight.com/iot/pg_receive_value?api_key=300uhxXsAH

b) Alerts

- Name: pg_send_email
- Description: send an alert email identified by "api_key" and insert a log. Optional you can
  also send  a "value" 
- Call examples: https://m2mlight.com/iot/pg_send_email?api_key=180Gx5CIHeO 
                 https://m2mlight.com/iot/pg_send_email?api_key=180Gx5CIHeO&value=57


c) Parameters

- Name: pg_read_parameter
- Description: return the value of a parameter identified by "api_key". 
- Call example: https://m2mlight.com/iot/pg_read_parameter?api_key=300Gx5CIHeO 

- Name: pg_update_parameter 
- Description: Update with "value" the parameter identified by "api_key"
- Call example: https://m2mlight.com/iot/pg_update_parameter?api_key=400Gx5CIHeO&value=60


You can use these functions inside an C++ code (Arduino or Esp8266) or Python code (Raspberry).  You can see and example in the file: example_server_functions_with_a_sensor.py. If you are using an Arduino is better to use the M2MData library.

