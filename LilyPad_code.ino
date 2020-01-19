/*
 * Read accelerometer data and recieve extra from the mpu6050. Then transmit to the arm.
 */
#include <Adafruit_CircuitPlayground.h>

float X, Y, Z;
float roll=0, pitch=0, yaw=0;
float AccErrorX = 0.4, AccErrorY= 0.3,AccErrorZ=0.03;
float AccX=0;
float AccY=0;
float AccZ=0;
float accAngleX=0;
float accAngleY=0;
void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  AccX = CircuitPlayground.motionX();
  AccY = CircuitPlayground.motionY();
  AccZ = CircuitPlayground.motionZ();
  accAngleX = (atan(AccY/ sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - AccErrorX; 
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + AccErrorY;
  Serial.println(accAngleY);

  

  delay(1000);
}
