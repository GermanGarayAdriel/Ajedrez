#include <SoftwareSerial.h>
#include <WiFi.h>
const char* ssid = "G6_9776";
const char* password = "12345678";
 
SoftwareSerial esp8266(3,2); // RX||TX
void setup()
{
  Serial.begin(57600);
  esp8266.begin(57600);
  WiFi.begin(ssid, password);//AT+CWJAP:"SSID","PASSWD"
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
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
