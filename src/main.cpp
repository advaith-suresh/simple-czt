#include <Arduino.h>
#include <SPI.h>

const int chipSelectPin = 10;

int incomingByte = 0; // for incoming serial data

//function to check parity of command
int16_t parity(int16_t x) {
   int16_t y;
   y = x ^ (x >> 1);
   y = y ^ (y >> 2);
   y = y ^ (y >> 4);
   y = y ^ (y >> 8);
   return y & 1;
}

//function to send command to slave
void sendCommand(int16_t command) {
  //Mode 2: Data out on Rising edge, Data read on Falling edge, 
  //clock polarity doesn't matter as we have external clock.
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE2));
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer16((command << 7) | (parity(command) << 6));
  digitalWrite(chipSelectPin, HIGH);
  SPI.endTransaction();
}

void setup() {
  Serial.begin(9600);
  pinMode(chipSelectPin, OUTPUT);
  SPI.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
  }
}