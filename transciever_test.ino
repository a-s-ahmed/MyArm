#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    int vals_received[2];
    radio.read(&vals_received[0], sizeof(vals_received[0]));
    delay(10);
    radio.read(&vals_received[1], sizeof(vals_received[1]));
    if (vals_received[0]<0) {
      Serial.print("X: ");
      Serial.println(vals_received[0]+500);
    }
    if (vals_received[1] >0) {
      //Serial.print("Y: ");
      //Serial.println(vals_received[1]-500);
      
    }
  }
}
