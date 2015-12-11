/* m2mData.cpp - Arduino library for Internet of Things to www.m2mlight.com
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

#include <Arduino.h>
#include <m2mData.h>
#include <Ethernet.h>

// m2mlight.com server
byte server[] = { 88, 198, 207, 77 };              
EthernetClient client;

// sendValue variables
// - String api_key: sensor identifier
// - float value: sensor value

void m2mData::sendValue(String api_key, float value)
{
  if (client.connect(server, 80)>0) {            // connect to server
    client.print("GET /iot/pg_send_value.php?api_key="); // send values using GET
    client.print(api_key);
    client.print("&");
    client.print("value=");
    client.print(value);
    client.println(" HTTP/1.0");
    client.println("User-Agent: Arduino 1.0");
    client.println();
//    Serial.println("Connected");
  } else {
    Serial.println("Not connected");
  }
  if (!client.connected()) {
//    Serial.println("Disconnected!");
  }
  client.stop();
}

// sendAlertEmail variable
// - String api_key: alert identifier

void m2mData::sendAlertEmail(String api_key)
{
  if (client.connect(server, 80)>0) {            // connect to server
    client.print("GET /alert/pg_send_email.php?api_key="); // send api_key using GET
    client.print(api_key);    
    client.println(" HTTP/1.0");
    client.println("User-Agent: Arduino 1.0");
    client.println();
  } else {
    Serial.println("Not connected");
  }
//   Serial.println("Disconnecting...");
   while(client.connected()) //Waiting until connection finish
   {
     if(client.available()) Serial.write(client.read());
   }
   client.stop(); 
}




