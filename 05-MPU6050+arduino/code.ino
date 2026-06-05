#include <Wire.h>

const int MPU = 0x68; // I2C address
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY;
float gyroAngleX, gyroAngleY;
float angleX, angleY;
float elapsedTime, currentTime, previousTime;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Wake up MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0x00); // Wake up
  Wire.endTransmission(true);

  // Configure Accelerometer sensitivity (±2g)
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0x00);
  Wire.endTransmission(true);

  // Configure Gyro sensitivity (±250 deg/s)
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0x00);
  Wire.endTransmission(true);

  Serial.println("MPU6050 Ready!");
  previousTime = millis();
}

void loop() {
  // === Read Accelerometer ===
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Starting register for accel data
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);

  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // ±2g
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0;
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0;

  // Calculate angle from accelerometer
  accAngleX = atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI;
  accAngleY = atan(-AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI;

  // === Read Gyroscope ===
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000.0; // seconds
  previousTime = currentTime;

  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Starting register for gyro data
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);

  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // ±250deg/s
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;

  // === Complementary Filter (combines both) ===
  angleX = 0.96 * (angleX + GyroX * elapsedTime) + 0.04 * accAngleX;
  angleY = 0.96 * (angleY + GyroY * elapsedTime) + 0.04 * accAngleY;

  // === Print Results ===
  Serial.print("AngleX: "); Serial.print(angleX);
  Serial.print(" | AngleY: "); Serial.print(angleY);
  Serial.print(" | AccZ: "); Serial.println(AccZ);

  delay(100);
}