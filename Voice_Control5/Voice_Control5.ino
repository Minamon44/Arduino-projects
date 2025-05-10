#include <Ethernet.h>

#include <SoftwareSerial.h>

const int RX_PIN = 8;
const int TX_PIN = 9;
const int OUTPUT_PIN = 10;

SoftwareSerial mySerial(RX_PIN, TX_PIN);

String voice;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {
  if (mySerial.available() > 0) {
    voice = "";
    delay(2);
    voice = mySerial.readString();
    delay(2);
    Serial.print("Received from SoftwareSerial: ");
    Serial.println(voice);

    if (voice == "turn on") {
      digitalWrite(OUTPUT_PIN, HIGH);
    } else if (voice == "turn off") {
      digitalWrite(OUTPUT_PIN, LOW);
    }
  }
}
