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

    // Store a "value" of a sensor which is identified with "api_key"
    void sendValue(String api_key, float value);  

    // Return the last value of a sensor which is identified with "api_key"
    float readValue(String api_key);
    
    // Send an email of an alert which is identified with "api_key". If 
    // "value" is different from -1 then message includes this "value"
    void sendAlertEmail(String api_key, float value=-1); 

    // Return the value of a parameter which is identified with "api_key"
    float readParameter(String api_key);

    // Update the "value" of a parameter which is identified with "api_key"
    void updateParameter(String api_key, float value);

};
#endif
