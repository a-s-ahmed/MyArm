
#include <Wire.h>
//#include <Adafruit_CircuitPlayground.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const byte address[6] = "00001";

RF24 radio(7, 8); // CE, CSN
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY,accAngleZ, gyroAngleX=0, gyroAngleY=0, gyroAngleZ=0;
float accAngle2X, accAngle2Y,accAngle2Z;
float AccErrorX = 3.4, AccErrorY= 7.94,AccErrorZ=0.03, GyroErrorX= -1.74, GyroErrorY = 2.96, GyroErrorZ = 0.3;
float AccError2X = 3.4, AccError2Y= 7.94;
float elapsedTime, currentTime, previousTime;
//char identifier[2]= "xy";
int c=0;

const int MPU = 0x68; // one one arm

const int MPU2 = 0x69; // one on hand
void setup() {
 
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission
  Serial.begin(19200);
  
  //handboi2
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU2);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true); 
  Serial.begin(19200);
  


  // put your setup code here, to run once:

}

void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value

  accAngleX = (atan(AccY/ sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI); //- AccErrorX; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI); //+ 1.58; //   //accAngleZ = (atan(AccX/ sqrt(pow(AccY, 2) + pow(AccX, 2))) * 180 / PI) + AccErrorZ; 

  Wire.beginTransmission(MPU2);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU2, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value

  accAngle2X = (atan(AccY/ sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI); //+ AccError2X; 
  accAngle2Y = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI); //+ AccError2Y;  

  Serial.print(accAngleX), Serial.print("    /     "), Serial.println(accAngleY);
  Serial.print(accAngle2X), Serial.print("    /     "), Serial.println(accAngle2Y);
  Serial.println("");
  

  

  
}
