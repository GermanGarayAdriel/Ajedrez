#include <SoftwareSerial.h>
 
SoftwareSerial esp8266(3,2); // RX||TX
void setup()
{
  Serial.begin(57600);
  esp8266.begin(57600);
  Wifi.config("192.168.0.2","192.168.0.1","192.168.0.1","255.255.255.252")
}
 void loop()
{
  if(esp8266.available()){
    char c = esp8266.read();
    Serial.print(c);
  }
   
  if(Serial.available()){
    char c = Serial.read();
    esp8266.print(c);
  }
  
}
