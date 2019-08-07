#include <avr/io.h>
#include "../lib/ultra.h"
#include "../lib/rs232.h"

#define LED_DDR   DDRD
#define LED_PORT  PORTD
#define LED_NR   0

volatile uint16_t timer1 = 0;
int main()
{
  USART_Init(__UBRR);
  ultra_init();

  sei();

  LED_DDR |= (1 << LED_NR); //led
  LED_PORT |= (1 << LED_NR);



/* 
  //timer
  TCCR0A |= (1<<WGM01);           //CTC
  TCCR0B |= (1<<CS01)|(1<<CS00);  //prescaler 64
  TIMSK0 |= (1<<OCIE0A);          //interrupt enable
  OCR0A = 250;                    //interrupt generats every 1ms
*/

  uint16_t tmp_value, tmp_trans;
  while (1)
  {
    LED_PORT ^= (1 << LED_NR);
    _delay_ms(1000);
  /*   
    if( !timer1 )
    {
      tmp_value = measure();

      if( tmp_value<200 && tmp_value>1)
      {
        uart_putc('h');    //beginning of the frame
        
        /*********************  DATA  ***********************
        uart_putc( tmp_value ); //entire value
        /******************************************************
        
        uart_putc('t');  //end of the frame
        
        LED_PORT ^=(1<<LED_NR);
        
        timer1 = 5000;
      }
      else
      {
        timer1 = 100;
      }

    }
    
    
    if( uart_getc() == 1)
    {
      timer1 = 0;
    }


 
*/

  }
}

ISR( TIMER0_COMPA_vect )
{
  if(timer1);
    timer1--;
}