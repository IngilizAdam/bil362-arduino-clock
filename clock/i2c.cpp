#include "i2c.h"

uint8_t i2cBusy = 0;

void startI2C()
{
  TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT); // Enable I2C & Start Cond. & Interrupt flag
  while(~TWCR & (1<<TWINT)); // wait until interrupt flag high
}

void stopI2C()
{
  TWCR = (1<<TWEN)|(1<<TWSTO)|(1<<TWINT); // Enable I2C & Stop Cond. & Interrupt flag
}

void sendI2C(uint8_t data)
{
  TWDR = data;
  TWCR = (1<<TWEN)|(1<<TWINT);
  while(~TWCR & (1<<TWINT)); // Wait until transmission completed
}

uint8_t receiveI2C(uint8_t ack)
{
  ack &= 0x01;
  uint8_t data;
  TWCR = (1<<TWEN)|(1<<TWINT)|(ack<<TWEA);
  while(~TWCR & (1<<TWINT)); // Wait until transmission completed
  data = TWDR;
  return data;
}

void sendUSART(short data)
{
  uint8_t *digits = (uint8_t*) malloc(4); // 4 digits

  if(data < 0) // negative value
  {
    data *= -1;
    while(~UCSR0A & (1<<UDRE0));
    UDR0 = 0x2D; // minus sign (-) char
  }
  data >>= 4;

  for(uint8_t i=0; i<4; i++)
  {
    *digits = data%10;
    data /= 10;
    digits++;
  }

  for(uint8_t i=0; i<4; i++)
  {
    digits--;
    while(~UCSR0A & (1<<UDRE0));
    UDR0 = *digits + 0x30;
    if(i==1)
    {
      while(~UCSR0A & (1<<UDRE0));
      UDR0 = 0x2E; // dot (.) char
    }
  }

  while(~UCSR0A & (1<<UDRE0));
  UDR0 = 0x0A;  // new line (\n) char

  free(digits); // DON'T FORGET TO FREE!!!
}
