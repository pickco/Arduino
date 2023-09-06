/*
  This example shows how to connect to Cayenne using an ESP32 and send/receive sample data.

  The CayenneMQTT Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

  Steps:
  1. If you have not already installed the ESP32 Board Package install it using the instructions here: https://github.com/espressif/arduino-esp32/blob/master/README.md#installation-instructions.
  2. Select your ESP32 board from the Tools menu.
  3. Set the Cayenne authentication info to match the authentication info from the Dashboard.
  4. Set the network name and password.
  5. Compile and upload the sketch.
  6. A temporary widget will be automatically generated in the Cayenne Dashboard. To make the widget permanent click the plus sign on the widget.
*/

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP32.h>

// WiFi network info.
char ssid[] = "Sembrul";
char wifiPassword[] = "Apahayoo";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "67d03120-367d-11e9-8cb9-732fc93af22b";
char password[] = "0955625d80398b11d3dc2ec0e9048d4fd1e3bfc5";
char clientID[] = "c92adf90-5974-11ea-ba7c-716e7f5ba423";

/*
  DHT SENSOR
*/
//Libraries
#include <DHT.h>;

//Constants
#define DHTPIN  25    // what pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

/*
  BMP180 SENSOR
*/
#include <Arduino.h>
#include <Wire.h>
#include <BMP180I2C.h>
#define I2C_ADDRESS 0x77

//create an BMP180 object using the I2C interface
BMP180I2C bmp180(I2C_ADDRESS);

float t1, t2, p1, h1;

void setup() {
  Serial.begin(115200);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  //wait for serial connection to open (only necessary on some boards)
  while (!Serial);

  Wire.begin();

  //begin() initializes the interface, checks the sensor ID and reads the calibration parameters.
  if (!bmp180.begin())
  {
    Serial.println("begin() failed. check your BMP180 Interface and I2C Address.");
    while (1);
  }

  //reset sensor to default parameters.
  bmp180.resetToDefaults();

  //enable ultra high resolution mode for pressure measurements
  bmp180.setSamplingMode(BMP180MI::MODE_UHR);
  dht.begin();
}

void loop() {
  Cayenne.loop();
  //start a temperature measurement
  if (!bmp180.measureTemperature())
  {
    Serial.println("could not start temperature measurement, is a measurement already running?");
    return;
  }

  //wait for the measurement to finish. proceed as soon as hasValue() returned true.
  do
  {
    delay(100);
  } while (!bmp180.hasValue());

  t1 = bmp180.getTemperature();
  Serial.print("Temperature: ");
  Serial.print(t1);
  Serial.println(" degC");

  //start a pressure measurement. pressure measurements depend on temperature measurement, you should only start a pressure
  //measurement immediately after a temperature measurement.
  if (!bmp180.measurePressure())
  {
    Serial.println("could not start perssure measurement, is a measurement already running?");
    return;
  }

  //wait for the measurement to finish. proceed as soon as hasValue() returned true.
  do
  {
    delay(100);
  } while (!bmp180.hasValue());
  p1 = bmp180.getPressure();
  Serial.print("Pressure: ");
  Serial.print(p1);
  Serial.println(" Pa");

  //  delay(2000);
  //Read data and store it to variables hum and temp
  h1 = dht.readHumidity();
  t2 = dht.readTemperature();
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(h1);
  Serial.print(" %, Temp: ");
  Serial.print(t2);
  Serial.println(" Celsius");

  if (isnan(h1) || isnan(t2))
  {
    Serial.println("Failed to read from DHT sensor!");
  }
  /* delay
    1000 = 1 second
    10000 = 10 second
    100000 = 100 second
  */
    delay(10000); //Delay 1 minute.
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
//CAYENNE_OUT_DEFAULT(0)
//{
//  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
//  Cayenne.virtualWrite(0, millis());
//  // Some examples of other functions you can use to send data.
//  //Cayenne.celsiusWrite(1, 22.0);
//  //Cayenne.luxWrite(2, 700);
//  //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
//}

CAYENNE_OUT(1)
{
  Cayenne.celsiusWrite(1, t1);
}
CAYENNE_OUT(2)
{
  Cayenne.virtualWrite(2, t2);
}
CAYENNE_OUT(3)
{
  Cayenne.virtualWrite(3, h1);
}
CAYENNE_OUT(4)
{
  Cayenne.virtualWrite(4, p1);
}
