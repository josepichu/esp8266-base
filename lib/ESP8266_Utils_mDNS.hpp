#include <ESP8266mDNS.h>

void InitMDNS(String hostname)
{
   if (!MDNS.begin(hostname)) 
   {             
     Serial.println("Error iniciando mDNS");
   } else Serial.println("mDNS iniciado " + String(hostname) + ".local");
}