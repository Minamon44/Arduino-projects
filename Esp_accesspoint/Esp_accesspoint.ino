#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const char* ssid = "LED_Controller";
const char* password = "12345678";

void handleLEDOn() {
  digitalWrite(D2, HIGH); 
  server.send(200, "text/plain", "LED is ON");
}

void handleLEDOff() {
  digitalWrite(D2, LOW); 
  server.send(200, "text/plain", "LED is OFF");
}

void setup() {
  Serial.begin(115200);
  
  
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW); 
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  server.on("/on", handleLEDOn);
  server.on("/off", handleLEDOff);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}