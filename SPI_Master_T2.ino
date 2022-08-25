#include <SPI.h>

unsigned long longTimeStart=0;
unsigned long pulseTimeStart=0;
unsigned long longTimeEnd=0;


const long longTime=5000;
const long pulseTime=400;
const long breakTime=2000;

int numPress=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT_PULLUP);
  //SPI.beginTransaction(SPISettings(10000, MSBFIRST, SPI_MODE0));
  Serial.begin(9600);
  digitalWrite(SS, HIGH); 
  SPI.begin();
}

byte transferAndWait (const byte what){
  byte a = SPI.transfer(what);
  delayMicroseconds(20);
  return a;
} // end of transferAndWait

void loop() {
  
  byte a=0,b;
  
  if((millis()-longTimeEnd)>breakTime && digitalRead(2)==LOW && numPress==0){
    longTimeStart = millis();
    pulseTimeStart = millis();
    numPress++;
  }

  if((millis()-longTimeStart)<longTime && digitalRead(2) == LOW && (millis()-pulseTimeStart)>pulseTime){
    numPress++;
    pulseTimeStart = millis();
  }

  if((millis()-longTimeStart)>longTime && numPress!=0){
    digitalWrite(SS, LOW);
    switch(numPress){
      case 1:
        transferAndWait('a');
        break;

      case 2:
        transferAndWait('s');
        break;

      default:
        transferAndWait('m');
        break;
    }
    b = transferAndWait(100);
    a = transferAndWait(0);
    
    digitalWrite(SS, HIGH);

    Serial.println(a, DEC);
    Serial.print("Number of button presses: ");
    Serial.println(numPress, DEC);
    numPress = 0;
  }
}
