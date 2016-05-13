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
char m2mserver[] = "m2mlight.com";
EthernetClient m2m_client;

// sendValue variables
// - String api_key: sensor identifier
// - float value: sensor value

void m2mData::sendValue(String api_key, float value)
{
  if (m2m_client.connect(m2mserver, 80)>0) {            // connect to server
    m2m_client.print("GET /iot/pg_send_value.php?api_key="); // send values using GET
    m2m_client.print(api_key);
    m2m_client.print("&");
    m2m_client.print("value=");
    m2m_client.print(value);
    m2m_client.println(" HTTP/1.0");
    m2m_client.println("User-Agent: Arduino 1.0");
    m2m_client.println();
   Serial.println("Connected");
  } else {
    Serial.println("Not connected");
  }

  int connectLoop = 0;
  int inChar;
  while(m2m_client.connected())
  {
    while(m2m_client.available())
    {
      inChar = m2m_client.read();
      Serial.write(inChar);
      connectLoop = 0;
    }
    delay(1);
    connectLoop++;
    if(connectLoop > 5000)
    {
      Serial.println();
      Serial.println(F("Timeout"));
      m2m_client.stop();
    }
  }
  Serial.println();
  Serial.println(F("disconnecting."));
  m2m_client.stop();

}

// sendAlertEmail variable
// - String api_key: alert identifier

void m2mData::sendAlertEmail(String api_key)
{
  if (m2m_client.connect(m2mserver, 80)>0) {            // connect to server
    m2m_client.print("GET /iot/pg_send_email.php?api_key="); // send api_key using GET
    m2m_client.print(api_key);    
    m2m_client.println(" HTTP/1.0");
    m2m_client.println("User-Agent: Arduino 1.0");
    m2m_client.println();
    Serial.println("Connected");
  } else {
    Serial.println("Not connected");
  }
   Serial.println("Disconnecting...");
   while(m2m_client.connected()) //Waiting until connection finish
   {
     if(m2m_client.available()) Serial.write(m2m_client.read());
   }
   m2m_client.stop(); 


}


