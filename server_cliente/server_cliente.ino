#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
IPAddress local_ip(192,168,0,1);
IPAddress host(192,168,1,1);
IPAddress cliente(192,168,1,2);
IPAddress subnet(255,255,255,252);
const char* ssid = "Schwartzmann"; //replace this with your WiFi network name
const char* password = "12345678"; //replace this with your WiFi network password
const char* ssid2 = "Garay";
WiFiServer server(80);

void setup() {
  delay(1000);
  boolean result = WiFi.softAP(ssid, password,3,0);//Parametros: Nombre_Red, contraseña, canal de 1 a 13, 1 si escondo la SSID
  WiFi.softAPConfig(local_ip, local_ip, subnet);
  Serial.begin(115200);
  Serial.println("Configuring WiFi access point...");
  if(result==true) {
   server.begin();
   Serial.println("Connected To WiFi");
   IPAddress myAddress = WiFi.softAPIP();
   Serial.println(myAddress);
  }
  else {
    Serial.println("error! Something went wrong...");
  }
  WiFi.config(cliente, host, host, subnet);
  WiFi.begin(ssid2, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(2500);
  WiFiClient client = server.available();
  String request = client.readStringUntil('\n');
  Serial.println(request);
  if(client.connect(host, 80)){
    
     client.write("Pichi el que lee 1");
  }
  Serial.println("k");
}
