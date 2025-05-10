#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const char* ssid = "Security_System";
const char* password = "12345678";

const int trigPin = 4;   
const int echoPin = 5;   
const int ledPin = 14;   

int lastDistance = 0;
bool alertActive = false;
const int MOVEMENT_THRESHOLD = 10; 
const int LED_BLINK_DURATION = 2000;

void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset=\"UTF-8\">";
  html += "<meta http-equiv=\"refresh\" content=\"1\">";  
  html += "<title>نظام الأمان</title></head>";
  html += "<body><h1>نظام مراقبة الحركة</h1>";
  html += "<p>المسافة الحالية: " + String(measureDistance()) + " سم</p>";
  html += "<p>الحالة: " + String(alertActive ? "⚠ إنذار! تم اكتشاف حركة" : "النظام طبيعي") + "</p>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void checkMovement() {
  int currentDistance = measureDistance();
  int distanceChange = abs(currentDistance - lastDistance);
  
  if (distanceChange > MOVEMENT_THRESHOLD) {
    if (!alertActive) {
      triggerAlert();
    }
    alertActive = true;
  } else {
    alertActive = false;
    digitalWrite(ledPin, LOW);
  }

  lastDistance = currentDistance;
}

void triggerAlert() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.begin();

  lastDistance = measureDistance(); 

  Serial.println("System Ready");
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  checkMovement();
  server.handleClient();
  delay(500);
}