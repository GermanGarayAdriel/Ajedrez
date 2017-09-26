#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
IPAddress local_ip(192,168,0,1);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,252);
const char* ssid = "Schwartzmann"; //replace this with your WiFi network name
const char* password = "12345678"; //replace this with your WiFi network password

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Configuring WiFi access point...");
  boolean result = WiFi.softAP(ssid, password,3,1);//Parametros: Nombre_Red, contraseña, canal de 1 a 13, 1 si escondo la SSID
  if(result==true) {
    WiFi.softAPConfig(local_ip, gateway, subnet);
    IPAddress myIP = WiFi.softAPIP();
    Serial.println("done!");
    Serial.println("");
    Serial.print("WiFi network name: ");
    Serial.println(ssid);
    Serial.print("WiFi network password: ");
    Serial.println(password);
    Serial.print("Host IP Address: ");
    Serial.println(myIP);
    Serial.println("");
  }

  else {
    Serial.println("error! Something went wrong...");
  }
}

void loop() {
  Serial.printf("Number of connected devices (stations) = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}
