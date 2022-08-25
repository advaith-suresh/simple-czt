#include<SPI.h>

char buff [50];
int indx = 0;
volatile boolean received;
volatile byte command=0;


ISR (SPI_STC_vect){ // SPI interrupt routine
   byte c = SPDR; // read byte from SPI Data Register
   switch(command){
    case 0:
      command = c;
      SPDR = 0;
      break;
    case 'a':
      SPDR = c + 5;
      break;
    case 's':
      SPDR = c - 5;
      break;
    case 'm':
      SPDR = c * 5;
      break;
    default:
      SPDR = c;
      break;
    }
}

void setup()
{
  Serial.begin(9600);

  pinMode(MISO,OUTPUT);   //Sets MISO as OUTPUT
 // pinMode(SCK,INPUT);
  SPCR |= _BV(SPE);       //Turn on SPI in Slave Mode
  received = false;
  SPI.attachInterrupt();  //Activate SPI Interuupt 
}


void loop()
{ 
  if (digitalRead (SS) == HIGH){
    command = 0;
    //SPDR=0;
  }
    
    
  if(received) {                        
    //SPDR = receivedData;    // send back the received data, this is not necessary, only for demo purpose
    //received = false;
    /*
    if(receivedData == 101){
      SPI.transfer(010);
    }
    */
    //SPDR = 0;
  }
}
