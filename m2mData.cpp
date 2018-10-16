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
#include <PubSubClient.h>

// m2mlight.com server
char m2mserver[] = "m2mlight.com";
EthernetClient m2m_client;

// MQTT protocol
char mqtt_server[] = "m2mlight.com";
PubSubClient m2m_ps_client(m2m_client);

/********************************************************/
/* Functions used when arduino is connected to Internet */ 

// sendValue variables:
// - char api_key[]: sensor identifier
// - float value: sensor value

void m2mData::sendValue(char api_key[], float value)
{
  if (m2m_client.connect(m2mserver, 80)>0) {            // connect to server
    m2m_client.print(F("GET /iot/send_sensor_value?api_key=")); // send values using GET
    m2m_client.print(api_key);
    m2m_client.print(F("&value="));
    m2m_client.print(value);
    m2m_client.println(F(" HTTP/1.1"));
    m2m_client.print(F("Host: "));
    m2m_client.println(m2mserver);
    m2m_client.println("Connection: close");  //close 1.1 persistent connection  
    m2m_client.println(F("User-Agent: Arduino 1.0"));
    m2m_client.println();
   Serial.println(F("Connected"));
  } else {
    Serial.println(F("Not connected"));
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

// sendCoordinates variables:
// - char api_key[]: sensor identifier
// - float latitude: latitude value
// - float longitude: longitud value

void m2mData::sendCoordinates(char api_key[], float latitude, float longitude)
{

  if (m2m_client.connect(m2mserver, 80)>0) {            // connect to server
    m2m_client.print(F("GET /iot/send_sensor_location?api_key=")); // send values using GET
    m2m_client.print(api_key);
    m2m_client.print(F("&latitude="));
    m2m_client.print(latitude);
    m2m_client.print(F("&longitude="));
    m2m_client.print(longitude);
    m2m_client.println(F(" HTTP/1.1"));
    m2m_client.print(F("Host: "));
    m2m_client.println(m2mserver);
    m2m_client.println("Connection: close");  //close 1.1 persistent connection  
    m2m_client.println(F("User-Agent: Arduino 1.0"));
    m2m_client.println();
   Serial.println(F("Connected"));
  } else {
    Serial.println(("Not connected"));
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
// - Char api_key[]: sensor identifier

float m2mData::readValue(char api_key[]){

  if (m2m_client.connect(m2mserver, 80)) {  // connect to server
    Serial.println(F("connected"));
    m2m_client.print(F("GET /iot/read_sensor_value_farduino?api_key=")); //send api_key value using GET
    m2m_client.print(api_key);
    m2m_client.println(F(" HTTP/1.1"));
    m2m_client.print(F("Host: "));
    m2m_client.println(m2mserver);
    m2m_client.println(F("User-Agent: Arduino 1.0"));
    m2m_client.println();

    String readString; readString.reserve(20);
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
              Serial.println(F("disconnecting."));
              return readString.toFloat();
            }
          }
       }
       delay(30);
    } // End while

  }else{
    Serial.println(F("not connected")); 
  }

}

// sendEmailAction variables:
// - char api_key[]: actuator identifier

void m2mData::sendEmailAction(char api_key[])
{
  if (m2m_client.connect(m2mserver, 80)>0) {            // connect to server
    m2m_client.print(F("GET /iot/send_email_action?api_key=")); // send api_key using GET
    m2m_client.print(api_key);
    m2m_client.println(F(" HTTP/1.1"));
    m2m_client.print(F("Host: "));
    m2m_client.println(m2mserver);
    m2m_client.println("Connection: close");  //close 1.1 persistent connection  
    m2m_client.println(F("User-Agent: Arduino 1.0"));
    m2m_client.println();
    Serial.println(F("Connected"));
  } else {
    Serial.println(F("Not connected"));
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

// sendEmailAlert variables:
// - char api_key[]: alert identifier
// - Float value: sensor value.

void m2mData::sendEmailAlert(char api_key[])
{
  if (m2m_client.connect(m2mserver, 80)>0) {            // connect to server
    m2m_client.print(F("GET /iot/send_email_alert?api_key=")); // send api_key using GET
    m2m_client.print(api_key);
    m2m_client.println(F(" HTTP/1.1"));
    m2m_client.print(F("Host: "));
    m2m_client.println(m2mserver);
    m2m_client.println("Connection: close");  //close 1.1 persistent connection  
    m2m_client.println(F("User-Agent: Arduino 1.0"));
    m2m_client.println();
    Serial.println(F("Connected"));
  } else {
    Serial.println(F("Not connected"));
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

// readActuatorHour variables:
// - char api_key[]: actuator identifier

String m2mData::readActuatorHour(char api_key[]){

  if (m2m_client.connect(m2mserver, 80)) {  // connect to server
    Serial.println(F("connected"));
    m2m_client.print(F("GET /iot/read_actuator_hour_farduino?api_key=")); //send api_key value using GET
    m2m_client.print(api_key);
    m2m_client.println(F(" HTTP/1.1"));
    m2m_client.print(F("Host: "));
    m2m_client.println(m2mserver);
    m2m_client.println(F("User-Agent: Arduino 1.0"));
    m2m_client.println();

    String readString;readString.reserve(10);
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
              Serial.println(F("Disconnecting..."));
              return readString;
            }
          }
       }
       delay(30);
    } // End while

  }else{
    Serial.println(F("readActuatorHour function not connected"));
    return "-1";  
  }

}


// updateActuatorHour variables:
// - char api_key[]: actuator identifier
// - char start_hour[]: start_hour value (HH:MM)

void m2mData::updateActuatorHour(char api_key[], char start_hour[])
{
  if (m2m_client.connect(m2mserver, 80)>0) {            // connect to server
    m2m_client.print(F("GET /iot/update_actuator_hour?api_key=")); // send values using GET
    m2m_client.print(api_key);
    m2m_client.print(F("&start_hour="));
    m2m_client.print(start_hour);
    m2m_client.println(F(" HTTP/1.1"));
    m2m_client.print(F("Host: "));
    m2m_client.println(m2mserver);
    m2m_client.println("Connection: close");  //close 1.1 persistent connection  
    m2m_client.println(F("User-Agent: Arduino 1.0"));
    m2m_client.println();
   Serial.println(F("Connected"));
  } else {
    Serial.println(F("Not connected"));
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


// Store a "value" of a sensor identified with "api_key" using MQTT

void m2mData::sendValueMqtt(char api_key[], float value)
{
   m2m_ps_client.setServer(mqtt_server, 1883);
   if (!m2m_ps_client.connected()) {
       // Loop until we're reconnected
      while (!m2m_ps_client.connected()) {
         Serial.print("Attempting MQTT connection...");
         // Attempt to connect
         if (m2m_ps_client.connect("arduinoClient")) {
            Serial.println("connected");
         } else {
            Serial.print("failed, rc=");
            Serial.print(m2m_ps_client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
         }
      }
   }
   m2m_ps_client.publish(api_key, String(value).c_str());
} 

