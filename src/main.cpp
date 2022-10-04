#include <Arduino.h>

/*using pins 
  10: SS (PB2)
  11: MOSI (PB3) 
  12: MISO (PB4)
  13: CLK (PB5)
  PORTB = BXXCIOSxx
*/

/*
  Tasks:
  1. check for MISO low (i.e. ready) before sending command
  2. Replace manual bit bashing with just enter hex value of command
*/

void ser_no(){
  //Command 9D = 1001 1101

  //bit 0: setting MOSI: 0, SS: 0, CLK: 1 -> 0 (for full clock cycle)
  PORTB = (PORTB | B00100000) & B11110011;
  PORTB = PORTB & B11011111;

  //bit 1 MOSI: 1
  PORTB = PORTB | B00101000;
  PORTB = PORTB & B11011111;

  //bit 2 MOSI: 0
  PORTB = (PORTB | B00100000) & B11110111;
  PORTB = PORTB & B11011111;

  //bit 3 MOSI: 0
  PORTB = (PORTB | B00100000) & B11110111;
  PORTB = PORTB & B11011111;

  //bit 4 MOSI: 1
  PORTB = PORTB | B00101000;
  PORTB = PORTB & B11011111;

  //bit 5 MOSI: 1
  PORTB = PORTB | B00101000;
  PORTB = PORTB & B11011111;

  //bit 6 MOSI: 1
  PORTB = PORTB | B00101000;
  PORTB = PORTB & B11011111;

  //bit 7 MOSI: 0
  PORTB = (PORTB | B00100000) & B11110111;
  PORTB = PORTB & B11011111;

  //bit 8 MOSI: 1
  PORTB = PORTB | B00101000;
  PORTB = PORTB & B11011111;

  //bit 9: MOSI: 0 (Parity)
  PORTB = (PORTB | B00100000) & B11110111;
  PORTB = PORTB & B11011111;

  //final clock high and pulling up chip select
  PORTB = PORTB | B00100100;
}

void setup() {
  DDRB = B11101111; //setting all except PB4 to output
}

void loop() {
  ser_no();
}