#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FS.h>

#include "config/wifi.h" 
#include "config/mqtt_broker.h"  
#include "lib/NewPingUltrasonicSensors.hpp"
#include "lib/ESP8266_Utils_WIFI.hpp"
#include "lib/ESP8266_Utils_mDNS.hpp"
#include "lib/MQTT_PubSubClient.hpp"
#include "Server.hpp"

char msg[50];

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
//   if ((char)payload[0] == '1') {
//     digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
//     // but actually the LED is on; this is because
//     // it is acive low on the ESP-01)
//   } else {
//     digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
//   }

}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);// Set time out for 

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // pinMode(LED_BUILTIN, OUTPUT);
  // digitalWrite(LED_BUILTIN, HIGH);
  
  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // WiFI Connection
  ConnectWiFi_STA(true);

  // enable Multicast DNS
  InitMDNS(hostname);

  // init server
  InitServer();

  // init MQTT Broker connection
  client.setServer(broker_hostname, 1893);
  client.setCallback(callback);
 
  if (client.connect("ESP8266_1", "test", "test")) {
   //  client.publish("campervan.io/aguas/limpias","hello world");
    client.subscribe("campervan.io/#");
  }


}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  //  int num = getSensorData();
   int num = getSensorWaterData();
   char cstr[16];
   itoa(num, cstr, 10);

   client.publish("campervan.io/aguas/limpias", cstr);

   delay(2000);


}
