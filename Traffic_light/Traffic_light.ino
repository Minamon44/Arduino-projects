const int redPin = 2;
const int yellowPin = 3;
const int greenPin = 4;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
}

void loop() {
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  delay(5000);
  
  for (int i = 0; i < 4; i++) {
    digitalWrite(redPin, LOW);
    delay(250);
    digitalWrite(redPin, HIGH);
    delay(250);
  }
  digitalWrite(redPin, LOW);
  
  digitalWrite(yellowPin, HIGH);
  delay(5000);
  
  for (int i = 0; i < 4; i++) {
    digitalWrite(yellowPin, LOW);
    delay(250);
    digitalWrite(yellowPin, HIGH);
    delay(250);
  }
  digitalWrite(yellowPin, LOW);
  
  digitalWrite(greenPin, HIGH);
  delay(5000);
  
  for (int i = 0; i < 4; i++) {
    digitalWrite(greenPin, LOW);
    delay(250);
    digitalWrite(greenPin, HIGH);
    delay(250);
  }
  digitalWrite(greenPin, LOW);
}