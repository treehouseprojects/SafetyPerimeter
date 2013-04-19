#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 

RF24 radio(9,10);
int lights = 3;

const uint64_t pipes[2] = { 
  0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup(void)
{
  Serial.begin(9600);
  printf_begin();

  radio.begin();

  radio.setRetries(15,15);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  
  radio.startListening();
  
  pinMode(lights, OUTPUT);
  digitalWrite(lights, LOW);
}

void loop(void)
{
  if ( radio.available() )
  {
    char data;
    radio.read( &data, sizeof(char) );
    
    if (data == 'x')  {
      digitalWrite(lights, HIGH);
          delay(175);
          digitalWrite(lights, LOW);
          delay(175);
    }

    // Spew it
    printf("Got payload %c...",data);
    
    delay(20);
    
    digitalWrite(lights, LOW);
  }
}


