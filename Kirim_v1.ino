#include <SoftwareSerial.h>
#define RxPin 2
#define TxPin 3
SoftwareSerial radio (RxPin, TxPin);
void setup() {
  Serial.begin(9600);
  radio.begin(9600);
}

void loop() {
  radio.print("A");
}
