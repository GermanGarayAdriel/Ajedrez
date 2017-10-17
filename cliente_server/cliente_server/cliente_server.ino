#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
WiFiClient client;
WiFiServer server(80);
IPAddress host(192,168,0,1);
IPAddress local(192,168,0,2);
IPAddress local_server(192,168,1,1);
IPAddress subnet(255,255,255,252);
const char* ssid = "Schwartzmann"; 
const char* password = "12345678";
const char* ssid2 = "Garay"; //replace this with your WiFi network name


void setup() {
  delay(1000);
  boolean result = WiFi.softAP(ssid2, password, 3, 0);
  WiFi.softAPConfig(local_server, local_server, subnet);
  Serial.begin(115200);
  Serial.println("Configuring WiFi access point...");
  if(result==true) {
   server.begin();
   Serial.println("Connected To WiFi");
   IPAddress myAddress = WiFi.softAPIP();
   Serial.println(myAddress);
  }
  else{
    Serial.println("Something Went Wrong");
  }
  WiFi.config(local,host,host,subnet);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}
void loop() {
  delay(2500);
  int w = 0;
  if(client.connect(host, 80)){
    client.write("Pichi el que lee");
  }
  WiFiClient client = server.available();
  String request = client.readStringUntil('\n');
  Serial.println("Mensaje");
  Serial.println(request);
  Serial.println("k");
}
