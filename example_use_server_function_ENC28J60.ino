/*  
    Example of using a server function when Arduino is connected to a ENC28J60 shield      
    Store on m2mlight platform a "value" of a sensor which is identified with "api_key" with pg_send_value function    
    First, register in www.m2mlight.com to obtain api_key sensor identifier
    email: contact@m2mlight.com 
*/


#include <EtherCard.h>

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[700];
unsigned long timer;

const char website[] PROGMEM = "m2mlight.com";
float valor;
void setup () 
{
  Serial.begin(9600);
  Serial.println("Basic Web Client");

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println( "Failed to access Ethernet controller");
    
  // DHCP Setup
  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  

  // DNS Setup
  if (!ether.dnsLookup(website))
    Serial.println("DNS failed");
    
  ether.printIp("SRV: ", ether.hisip);
}

void loop () {
  ether.packetLoop(ether.packetReceive());
  
  if ((millis()-timer)>10000) {
    timer = millis();
    valor = valor + 100;
    Serial.print("Value sent=");
    Serial.println(valor);
    
    char result[15]; // Buffer 
    dtostrf(valor, 1, 4, result);  

    ether.browseUrl(PSTR("/iot/pg_send_value?api_key=Qt8rYCidlB1njcju&value="), result, website, 0);

  }
}
