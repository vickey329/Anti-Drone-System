#include <Wire.h>
#include <MPU9250.h>
#include <Adafruit_BMP280.h>

MPU9250 mpu;
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("GY-91 MPU9250 + BMP280");
  Serial.println("Initializing...");
  Serial.println();

  // -----------------------------
  // Initialize MPU9250
  // -----------------------------
  if (!mpu.setup(0x68)) {
    Serial.println("ERROR: MPU9250 not found!");
    Serial.println("Check SDA, SCL, VCC and GND.");
    
    while (1) {
      delay(1000);
    }
  }

  Serial.println("MPU9250 OK");

  // -----------------------------
  // Initialize BMP280
  // -----------------------------
  if (!bmp.begin(0x76)) {

    Serial.println("BMP280 not found at 0x76.");
    Serial.println("Trying 0x77...");

    if (!bmp.begin(0x77)) {
      Serial.println("ERROR: BMP280 not found!");

      while (1) {
        delay(1000);
      }
    }
  }

  Serial.println("BMP280 OK");
  Serial.println();

  // BMP280 settings
  bmp.setSampling(
    Adafruit_BMP280::MODE_NORMAL,
    Adafruit_BMP280::SAMPLING_X2,
    Adafruit_BMP280::SAMPLING_X16,
    Adafruit_BMP280::FILTER_X16,
    Adafruit_BMP280::STANDBY_MS_500
  );

  Serial.println("-----------------------------------------");
  Serial.println("        GY-91 SENSOR DATA");
  Serial.println("-----------------------------------------");

  delay(1000);
}


void loop() {

  // Update MPU9250
  if (mpu.update()) {

    // -----------------------------
    // Accelerometer
    // -----------------------------
    Serial.println("ACCELEROMETER");

    Serial.print("X: ");
    Serial.print(mpu.getAccX());
    Serial.print(" g    ");

    Serial.print("Y: ");
    Serial.print(mpu.getAccY());
    Serial.print(" g    ");

    Serial.print("Z: ");
    Serial.print(mpu.getAccZ());
    Serial.println(" g");

    // -----------------------------
    // Gyroscope
    // -----------------------------
    Serial.println("GYROSCOPE");

    Serial.print("X: ");
    Serial.print(mpu.getGyroX());
    Serial.print(" deg/s    ");

    Serial.print("Y: ");
    Serial.print(mpu.getGyroY());
    Serial.print(" deg/s    ");

    Serial.print("Z: ");
    Serial.print(mpu.getGyroZ());
    Serial.println(" deg/s");

    // -----------------------------
    // Magnetometer
    // -----------------------------
    Serial.println("MAGNETOMETER");

    Serial.print("X: ");
    Serial.print(mpu.getMagX());
    Serial.print(" uT    ");

    Serial.print("Y: ");
    Serial.print(mpu.getMagY());
    Serial.print(" uT    ");

    Serial.print("Z: ");
    Serial.print(mpu.getMagZ());
    Serial.println(" uT");

    // -----------------------------
    // MPU9250 Temperature
    // -----------------------------
    Serial.println("MPU9250 TEMPERATURE");

    Serial.print("Temperature: ");
    Serial.print(mpu.getTemperature());
    Serial.println(" °C");
  }


  // -----------------------------
  // BMP280
  // -----------------------------

  Serial.println("BMP280");

  // Temperature
  Serial.print("Temperature: ");
  Serial.print(bmp.readTemperature());
  Serial.println(" °C");

  // Pressure
  float pressure = bmp.readPressure() / 100.0;

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  // Altitude
  Serial.print("Altitude: ");
  Serial.print(bmp.readAltitude(1013.25));
  Serial.println(" m");

  Serial.println("-----------------------------------------");

  delay(1000);
}
