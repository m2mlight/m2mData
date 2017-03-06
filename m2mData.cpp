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

// sendValue variables:
// - String api_key: sensor identifier
// - float value: sensor value

void m2mData::sendValue(String api_key, float value)
{
  if (m2m_client.connect(m2mserver, 80)>0) {            // connect to server
    m2m_client.print("GET /iot/pg_send_value?api_key="); // send values using GET
    m2m_client.print(api_key);
    m2m_client.print("&");
    m2m_client.print("value=");
    m2m_client.print(value);
    m2m_client.println(" HTTP/1.1");
    m2m_client.println("Host: m2mlight.com");
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

// readValue variables:
// - String api_key: sensor identifier

float m2mData::readValue(String api_key){

  if (m2m_client.connect(m2mserver, 80)) {  // connect to server
    Serial.println("connected");
    m2m_client.print("GET /iot/pg_receive_value_farduino?api_key="); //send api_key value using GET
    m2m_client.print(api_key);
    m2m_client.println(" HTTP/1.1");
    m2m_client.println("Host: m2mlight.com");
    m2m_client.println("User-Agent: Arduino 1.0");
    m2m_client.println();

    String readString;
    boolean startRead = false; 

    while(m2m_client.connected()){
      
       if (m2m_client.available()) {
          char c = m2m_client.read(); // read char by char HTTP request
          if (c == '{' ) {        //'{' initial character
             startRead = true; 
          }else if(startRead){
            if(c != '}'){         //'}' final character            
                readString += c;            
            }else{
              startRead = false;
              m2m_client.stop();
              m2m_client.flush();
              Serial.println("disconnecting.");
              return readString.toFloat();
            }
          }
       }
       delay(30);
    } // End while

  }else{
    Serial.println("not connected");
//    return "Error: not connected"; // 
  }

}


// sendAlertEmail variables:
// - String api_key: alert identifier
// - Float value: sensor value. If value is different from -1 then message includes
//   this value

void m2mData::sendAlertEmail(String api_key, float value)
{
  if (m2m_client.connect(m2mserver, 80)>0) {            // connect to server
    m2m_client.print("GET /iot/pg_send_email?api_key="); // send api_key using GET
    m2m_client.print(api_key);
    if (value != -1){
       m2m_client.print("&value=");
       m2m_client.print(value);
    }   
    m2m_client.println(" HTTP/1.1");
    m2m_client.println("Host: m2mlight.com");
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


// readParameter variables:
// - String api_key: alert identifier

float m2mData::readParameter(String api_key){

  if (m2m_client.connect(m2mserver, 80)) {  // connect to server
    Serial.println("connected");
    m2m_client.print("GET /iot/pg_read_parameter_farduino?api_key="); //send api_key value using GET
    m2m_client.print(api_key);
    m2m_client.println(" HTTP/1.1");
    m2m_client.println("Host: m2mlight.com");
    m2m_client.println("User-Agent: Arduino 1.0");
    m2m_client.println();

    String readString;
    boolean startRead = false;

    while(m2m_client.connected()){
      
       if (m2m_client.available()) {
          char c = m2m_client.read(); // read char by char HTTP request
          if (c == '{' ) {        //'{' initial character
             startRead = true; 
          }else if(startRead){
            if(c != '}'){         //'}' final character            
                readString += c;            
            }else{
              startRead = false;
              m2m_client.stop();
              m2m_client.flush();
              Serial.println("Disconnecting...");
              return readString.toFloat();
            }
          }
       }
       delay(30);
    } // End while

  }else{
    Serial.println("readParameter function not connected");
    return -1;  
  }

}

// updateParameter variables:
// - String api_key: parameter identifier
// - float value: parameter value

void m2mData::updateParameter(String api_key, float value)
{
  if (m2m_client.connect(m2mserver, 80)>0) {            // connect to server
    m2m_client.print("GET /iot/pg_update_parameter?api_key="); // send values using GET
    m2m_client.print(api_key);
    m2m_client.print("&");
    m2m_client.print("value=");
    m2m_client.print(value);
    m2m_client.println(" HTTP/1.1");
    m2m_client.println("Host: m2mlight.com");
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

