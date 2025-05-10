#include <SoftwareSerial.h>
const int trigPin = 9;
const int echoPin = 8;
const int buzzerPin = 7;
SoftwareSerial BTSerial(10, 11);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  long duration;
  float distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  
  BTSerial.print("Distance: ");
  BTSerial.print(distance);
  BTSerial.println(" cm");
  
  if (distance < 10) {
    tone(buzzerPin, 1000);
  } else if (distance < 20) {
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
    delay(100);
  } else if (distance < 30) {
    tone(buzzerPin, 1000);
    delay(300);
    noTone(buzzerPin);
    delay(300);
  } else {
    noTone(buzzerPin);
  }
  
  delay(100);
}
