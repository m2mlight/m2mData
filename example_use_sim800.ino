/*  Example of use the SIM800L GSM/GPRS chip to connect to m2mlight. 
    It uses the send_sensor_value server function to upload a value to DB
    First, register in www.m2mlight.com to obtain api_key identifier
    email: contact@m2mlight.com 
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10);            // RX, TX Pins
String apn = "xxxx.xxxx.xxx";               //APN service provider
String url = "http://m2mlight.com/iot/send_sensor_value?api_key=pDvZ2njcj8&value=44"; //example 

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  delay(10000);
}

void loop() { // run over and over

  gsm_sendhttp(); //Start the GSM-Module and start the transmisson
  delay(60000); //Wait one minute

}

void gsm_sendhttp() {

  mySerial.println("AT");
  runsl();//Print GSM Status on the Serial Output;
  delay(4000);
  mySerial.println("AT+SAPBR=3,1,Contype,GPRS");
  runsl();
  delay(100);
  mySerial.println("AT+SAPBR=3,1,APN," + apn);
  runsl();
  delay(100);
  mySerial.println("AT+SAPBR=2,1");
  runsl();
  delay(2000);
  mySerial.println("AT+HTTPINIT");
  runsl();
  delay(100);
  mySerial.println("AT+HTTPPARA=URL," + url);
  runsl();
  delay(100);
  mySerial.println("AT+HTTPACTION=0");
  runsl();
  delay(5000);
  mySerial.println("AT+HTTPTERM");
  runsl();
}

//Print GSM Status
void runsl() {
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }

}







