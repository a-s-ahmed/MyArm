
/*
  This script recieves the accelerometer data from the sender transciever and uses the data 
  to write the recieved angles to the 4 different servo's
*/

#include <SPI.h>
#include <RF24.h>
#include <Servo.h>
#include <nRF24L01.h>
Servo base;
Servo arm;
Servo heighto;
Servo claw;
float position_arm=40;
float height_arm=40;
float base_arm=60;
float claw_arm=0;

float arm_max = 110;
float height_max=160;
float arm_min= 10;
float height_min=20;
float base_max=160;
float base_min =0;


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
void setup() {
  arm.attach(4);
//  pinMode(TouchPin,INPUT);// attaches the servo on pin 9 to the servo object
//  pinMode(13,OUTPUT);
//  digitalWrite(13,LOW);
  heighto.attach(9);
  base.attach(5);
  arm.write(position_arm);
  heighto.write(height_arm);
  base.write(base_arm);
  //claw.attach(6);
  
  Serial.begin(19200);
  radio.begin();
  radio.setAutoAck(false);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  delay(10);
    
  if (radio.available()) {
    float vals_received[4];
    radio.read(&vals_received[0], sizeof(vals_received[0]));
   // delay(10);
    radio.read(&vals_received[1], sizeof(vals_received[1]));
    //delay(10);
    radio.read(&vals_received[2],sizeof(vals_received[2]));
    //delay(10);
    radio.read(&vals_received[3],sizeof(vals_received[3]));
    
    if (vals_received[0]<0 && vals_received[0]>(-1000)) {
      //ADO is set to low. swivel base? 
     // Serial.print("X1: ");
      //Serial.println(vals_received[0]+500);
      float delta_X1= ((vals_received[0]+500)/50);
      position_arm = position_arm + delta_X1;
      //Serial.println(delta_X1);
      position_arm = constrain(position_arm, arm_min,arm_max);
      //Serial.println(position_arm);
      arm.write(position_arm);
  
    }
    if (vals_received[1] >0 && vals_received[1] < 600) {
      //ADO is set to low. arm.
      /*
      Serial.print("Y1: ");
      Serial.println(vals_received[1]-500);
      */
      float delta_Y1 = ((vals_received[1]-500)/ 50);
      base_arm+= delta_Y1;
      //Serial.println(base_arm);
      base_arm = constrain(base_arm, base_min,base_max);
     base.write(base_arm);

      
    }

    if (vals_received[2]<(-1000) && vals_received [2]> (-1800)) {
      //AD0 is set High. height.
      /*
      Serial.print("X2: ");
      Serial.println(vals_received[2]+1500);
      */
      float delta_X2= ((vals_received[2]+1500)/25);
      

      //use the servo.write to write to the servos, but use the constraint function before for all if statements. except Y2 cuz we don't need it
      height_arm+=delta_X2;
      height_arm = constrain(height_arm, height_min,height_max);
      Serial.println(height_arm);
      heighto.write(height_arm);

    }

    if ((vals_received[3] > 1000) && (vals_received[3] < 2000)) {
      //ADo is set to High
      /*
      Serial.print("Y2: ");
      Serial.println(vals_received[3]-1500);
      */
    }
    
  }
}
