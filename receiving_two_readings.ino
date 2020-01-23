#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
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
  Serial.begin(19200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    int vals_received[4];
    radio.read(&vals_received[0], sizeof(vals_received[0]));
    delay(10);
    radio.read(&vals_received[1], sizeof(vals_received[1]));
    delay(10);
    radio.read(&vals_received[2],sizeof(vals_received[2]));
    delay(10);
    radio.read(&vals_received[3],sizeof(vals_received[3]));
    
    if (vals_received[0]<0 && vals_received[0]>(-1000)) {
      //ADO is set to low.
      Serial.print("X1: ");
      Serial.println(vals_received[0]+500);
      float delta_X1= ((vals_received[0]+500)/200);
      position_arm+= delta_X1;
      
      
    }
    if (vals_received[1] >0 && vals_received[1] < 600) {
      //ADO is set to low.
      Serial.print("Y1: ");
      Serial.println(vals_received[1]-500);
      float delta_Y1 = ((vals_received[1]-500)/ 200);
      base_arm+= delta_Y1;
      
    }

    if (vals_received[2]<(-1000) && vals_received [2]> (-1800)) {
      //AD0 is set High
      Serial.print("X2: ");
      Serial.println(vals_received[2]+1500);
      float delta_X2= ((vals_received[2]+1500)/200);
      height_arm+=delta_X2;

      //use the servo.write to write to the servos, but use the constraint function before for all if statements. except Y2 cuz we don't need it
    }

    if ((vals_received[3] > 1000) && (vals_received[3] < 2000)) {
      //ADo is set to High
      Serial.print("Y2: ");
      Serial.println(vals_received[3]-1500);
    }
  }
}
