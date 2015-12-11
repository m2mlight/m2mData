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

    // Store a value identified with api_key
    void sendValue(String api_key, float value);  
    
    // Send an alert email identified with api_key
    void sendAlertEmail(String api_key); 

};
#endif
