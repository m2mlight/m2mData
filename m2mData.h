/* m2mData.h - Arduino library for Internet of Things to www.m2mlight.com
   info@m2mlight.com

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/

#ifndef m2mData_h
#define m2mData_h
#include <Arduino.h>

class m2mData
{

  public:

    /********************************************************/
    /* Functions used when arduino is connected to Internet */ 
    
    // Store a "value" of a sensor identified with "api_key"
    void sendValue(char api_key[], float value);  

    // Store coordinates of a sensor identified with "api_key"
    void sendCoordinates(char api_key[], float latitude, float longitude);  

    // Return the last value of a sensor identified with "api_key"
    float readValue(char api_key[]);
    
    // Send an email about an action of an actuator identified with "api_key".
    void sendEmailAction(char api_key[]); 

    // Send an email of an alert identified with "api_key".
    void sendEmailAlert(char api_key[]); 

    // Return the star hour (HH:MM) of an actuator identified with "api_key"
    String readActuatorHour(char api_key[]);

    // Update the start hour "start_hour" of an actuator identified with "api_key"
    void updateActuatorHour(char api_key[], char start_hour[]);


    /************************************************************************/
    /* Functions used when Arduino is connected to a GSM shield like SIM900 */ 
    
    // Store a single "value" of a sensor identified with "api_key"
    void sendValueSIM900(char api_key[], float value);  

    // Store "latitude" and "longitud" of a sensor is identified with "api_key"
    void sendCoordinatesSIM900(char api_key[], float latitude, float longitude); 
   
};
#endif
