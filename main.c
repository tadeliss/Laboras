#include "ioavr.h"
#include "inavr.h"
#include <stdio.h>
#include <stdbool.h>

#define F_CPU 16000000L
#define USART_BAUDRATE 9600L
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16))) - 1)
#define CPUfreq_MHz 16
#define blinkDelay 1000

typedef unsigned char uint8_t;
typedef signed long int32_t;

uint8_t u8TempData;

void USART0Init(void)
{
  UBRR0H = (uint8_t)(UBRR_VALUE>>8);
  UBRR0L = (uint8_t)UBRR_VALUE;
  UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
  UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
  }
void USART0SendByte(uint8_t u8Data)
{
  while(!(UCSR0A&(1<<UDRE0))){};
  UDR0 = u8Data;
}
uint8_t USART0ReceiveByte()
{
  while(!(UCSR0A&(1<<RXC0))){};
  return UDR0;
}
void delay_ms(unsigned long time) 
{ 
  long i; 
  for(i = 0; i < time; i++) 
    __delay_cycles(CPUfreq_MHz * 1000); 
}
int main (void)
{
  USART0Init();
  while(1)
  {
 DDRB=0xFF; 
    u8TempData = USART0ReceiveByte();
    
    PORTB = 0x00;
    
    if (u8TempData=='R')
    {
      PORTB = (1<<3); //(PORTB11=1)
    }
    if (u8TempData=='G')
    {
      PORTB = (1<<4); //(PORTB12=1)
    }
    if (u8TempData=='B')
    {
      PORTB = (1<<5); //(PORTB13=1)
    }
  }
}
