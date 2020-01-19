/* Sweep
  Uses an acceleromet to approximate your hands motion and a touch sensor to measure when youve closed your hand!
*/
 
#include <Servo.h>
#include <Wire.h>
int new_arm_position=0;
int new_position_base=0;
int new_claw_position=0;
 
const int TouchPin=7;
 
int counter=0;
 
const int MPU = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
int position_arm=40;
int height_arm=40;
int base_arm=60;
int claw_arm=0;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;
 
 
Servo arm;
Servo extend; // create servo object to control a servo
int arm_max = 110;
int height_max=160;
int arm_min= 10;
int height_min=20;
int base_max=160;
int base_min =0;
Servo base;
Servo claw;
// twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position
 
void setup() {
  arm.attach(9);
  pinMode(TouchPin,INPUT);// attaches the servo on pin 9 to the servo object
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  extend.attach(4);
  base.attach(5);
  arm.write(position_arm);
  extend.write(height_arm);
  base.write(base_arm);
  claw.attach(6);
  Serial.begin(19200);
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission
  /*
    // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
    Wire.beginTransmission(MPU);
    Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
    Wire.write(0x10);                  //Set the register bits as 00010000 (+/- 8g full scale range)
    Wire.endTransmission(true);
    // Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)
    Wire.beginTransmission(MPU);
    Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
    Wire.write(0x10);                   // Set the register bits as 00010000 (1000deg/s full scale)
    Wire.endTransmission(true);
    delay(20);
  */
  // Call this function if you need to get the IMU error values for your module
  //calculate_IMU_error();
  delay(20);
 
}
 
void loop() {
  if (digitalRead(TouchPin)==HIGH && counter==0) {
    counter++;
    for( int i=0; i<30; i++) {
      claw.write(i);
      delay(200);
    }
    
  }
  Serial.println(counter);
  // === Read acceleromter data === //
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
  // Calculating Roll and Pitch from the accelerometer data
  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58; // AccErrorY ~(-1.58)
  // === Read gyroscope data === //
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
  // Correct the outputs with the calculated error values
  GyroX = GyroX + 0.56; // GyroErrorX ~(-0.56)
  GyroY = GyroY - 2; // GyroErrorY ~(2)
  GyroZ = GyroZ + 0.79; // GyroErrorZ ~ (-0.8)
  // Currently the raw values are in degrees per seconds, deg/s, so we need to multiply by sendonds (s) to get the angle in degrees
  // Print the values on the serial monitor
  accAngleX = -round((accAngleX / 300) * 15);
  accAngleY = round((accAngleY / 300) * 15);
  Serial.print(accAngleX), Serial.print("  /  "), Serial.println(accAngleY);
 
  position_arm+=accAngleX;
  
  if((position_arm)>=110) {
    (position_arm)=110;
  }
 
  if (position_arm < 11) {
    position_arm=10;
  }
 
   base_arm +=accAngleY;
 
  if (base_arm>=160) {
    base_arm = 160;
  
  }
 
  if (base_arm < 1) {
    base_arm =0;
  }
 
  
  arm.write(position_arm);
  base.write(base_arm);
 
  
  while (accAngleX >= 3) {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
    AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
    AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
    accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58;
    accAngleX = -round((accAngleX / 200) * 15);
    c++;
    delay(10);
    while (c >= 300) {
      c = 300;
      if (digitalRead(TouchPin)==HIGH && counter==0) {
        counter++;
        for( int i=0; i<30; i++) {
          claw.write(i);
          delay(200);
        }
      }
      if (digitalRead(HIGH) && counter>0) {
        for (int i=30; i>=0; i--) {
          claw.write(i);
          delay(200);
          counter=0;
      digitalWrite(13,HIGH);
      Wire.beginTransmission(MPU);
      Wire.write(0x3B);
      Wire.endTransmission(false);
      Wire.requestFrom(MPU, 6, true);
      AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
      AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
      AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
      accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58;
      accAngleX = round((accAngleX / 280) * 15);
      Serial.println(accAngleX);
      height_arm+=accAngleX;
 
      if (height_arm >= 100) {
        height_arm=100;
      }
 
      if (height_arm <=20) {
        height_arm=20;
      }
      if(
      Serial.println(height_arm);
      extend.write(height_arm);
      //controlling servos
      while (accAngleX >= 2 && c >= 300) {
        Wire.beginTransmission(MPU);
        Wire.write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU, 6, true);
        AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
        AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
        AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
        accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58;
        accAngleX = round((accAngleX / 350) * 15);
        c++;
        Serial.println(c);
        if (c >= 800) {
          c = 0;
          digitalWrite(13,LOW);
        }
 
      }
 
    }
 
  }
  c = 0;
  if (digitalRead(HIGH) && counter>0) {
    for (int i=30; i>=0; i--) {
      claw.write(i);
      delay(200);
      counter=0;
    }
  }
 
}
// waits 15ms for the servo to reach the position
