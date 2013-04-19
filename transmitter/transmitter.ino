#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9,10);
int LDR_Pin = A0;

const uint64_t pipes[2] = { 
  0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  printf_begin();

  radio.setRetries(15,15);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);

  radio.startListening();
  radio.stopListening();
}

void loop(void)
{
  char barrierStatus = 'x';
  printf("Now sending %lu...",barrierStatus);

  if (analogRead(LDR_Pin) < 750)  {
    bool ok = radio.write( &barrierStatus, sizeof(char) );

    if (ok)
      printf("ok...");
    else
      printf("failed.\n\r");

    delay(50);
  }
}




