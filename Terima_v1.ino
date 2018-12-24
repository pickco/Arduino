#include <SoftwareSerial.h>
#define RxPin 2
#define TxPin 3
SoftwareSerial radio (RxPin, TxPin);
char datachar;
float numerik;
float longitude, latitude;
int temperature, humidity;
void setup() {
  Serial.begin(9600);
  radio.begin(9600);
  pinMode(RxPin, INPUT);
  pinMode(TxPin, OUTPUT);
}

void loop() {
  if (radio.available() > 0) {
    datachar = radio.read();
  }
  data();

  Serial.print(" LAT  ");
  Serial.println(latitude);
  Serial.print(" LONG ");
  Serial.println(longitude);
  Serial.print(" TEMP ");
  Serial.println(temperature);
  Serial.print(" HUM ");
  Serial.println(humidity);



}
