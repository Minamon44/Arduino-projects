
const int lowerSensorPin = A0;    
const int higherSensorPin = A1;   
const int greenLedPin = 2;        
const int yellowLedPin = 3;      
const int redLedPin = 4;          
const int buzzerPin = 5;          


const int waterThreshold = 100;

void setup() {
  Serial.begin(9600);
  
  
  pinMode(lowerSensorPin, INPUT);
  pinMode(higherSensorPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  digitalWrite(buzzerPin, LOW);
  
  Serial.println("Flood Alarm System initialized");
  Serial.println("--------------------------------------");
  delay(1000);
}

void loop() {
  
  int lowerSensorValue = analogRead(lowerSensorPin);
  int higherSensorValue = analogRead(higherSensorPin);
  
 
  static unsigned long lastSerialOutput = 0;
  if (millis() - lastSerialOutput > 3000) { 
    Serial.println("\n----- WATER LEVEL STATUS -----");
    Serial.print("Lower sensor (A0): ");
    Serial.print(lowerSensorValue);
    Serial.print(" | Higher sensor (A1): ");
    Serial.println(higherSensorValue);
    lastSerialOutput = millis();
  }
  
  
  if (higherSensorValue > waterThreshold) {
    
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    
    if (millis() - lastSerialOutput < 100) {  
      Serial.println("STATUS: HIGH RISK - Red LED & Buzzer ON");
      Serial.println("-----------------------------------");
    }
  }
  
  else if (lowerSensorValue > waterThreshold) {
   
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, LOW);
    
    if (millis() - lastSerialOutput < 100) {  
      Serial.println("STATUS: LOW RISK - Yellow LED ON");
      Serial.println("-----------------------------------");
    }
  }
  
  else {
    
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, LOW);
    
    if (millis() - lastSerialOutput < 100) {  
      Serial.println("STATUS: NORMAL - Green LED ON");
      Serial.println("-----------------------------------");
    }
  }
  
  delay(500);
}