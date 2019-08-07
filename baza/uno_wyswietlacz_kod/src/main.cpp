#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../lib/rs232.h"
#include "../lib/d_led.h"

#define LED_DDR   DDRB
#define LED_PORT  PORTB
#define LED_NR    5

#define LED_GREEN_DDR   DDRB
#define LED_GREEN_PORT  PORTB
#define LED_GREEN_NR    1
#define GREEN_ON        LED_GREEN_PORT |=(1<<LED_GREEN_NR)
#define GREEN_OFF       LED_GREEN_PORT &=~(1<<LED_GREEN_NR)

#define LED_RED_DDR   DDRB
#define LED_RED_PORT  PORTB
#define LED_RED_NR    2
#define RED_ON        LED_RED_PORT |=(1<<LED_RED_NR)
#define RED_OFF       LED_RED_PORT &=~(1<<LED_RED_NR)

#define LED_ORANGE_DDR   DDRB
#define LED_ORANGE_PORT  PORTB
#define LED_ORANGE_NR    3
#define ORANGE_ON        LED_ORANGE_PORT |=(1<<LED_ORANGE_NR)
#define ORANGE_OFF       LED_ORANGE_PORT &=~(1<<LED_ORANGE_NR)

#define BUTTON_DDR  DDRD
#define BUTTON_PORT PORTD
#define BUTTON_PIN  PIND
#define BUTTON_NR   2         //INT0


void diode_update( uint8_t val);

int main()
{
  USART_Init( __UBRR );
  d_led_init();

  display(1234);
	sei();

  _delay_ms(2000);

  LED_DDR |= (1 << LED_NR); //led
  LED_PORT &=~(1<<LED_NR);

  LED_GREEN_DDR |= (1 << LED_GREEN_NR); 
  LED_RED_DDR |= (1 << LED_RED_NR); 
  LED_ORANGE_DDR |= (1 << LED_ORANGE_NR); 
  
  ORANGE_OFF;
  RED_OFF;
  GREEN_OFF;


  BUTTON_DDR  &=~(1<<BUTTON_NR);
  BUTTON_PORT |= (1<<BUTTON_NR);

  EIMSK |= (1<<INT0);  //external interrupts
  EICRA |= (1<<ISC01);  //falling edge generats interrupt


  unsigned char tmp_char;
  uint8_t value;

  while(1)
  {
    tmp_char = uart_getc();

    if( tmp_char )   //if data has been received
    { 
      //frame must not be interrupted
      if( (tmp_char == 'h') )   //if this is the beginning of the frame
      {
        EIMSK &=~(1<<INT0);   //if frame started don't disturb

        while( !(tmp_char = uart_getc()) );
        
        display(tmp_char);
        diode_update( tmp_char );

        while( !(tmp_char = uart_getc()) );
        if( (tmp_char == 't') ) ;    //if frame have reached to the end

        EIMSK |=(1<<INT0);   //frame ends so ext interrupts are allowed
      }

    }



  } // end of while
}


ISR( 	INT0_vect )
{
  _delay_ms(50);
  if( !(BUTTON_PIN & (1<<BUTTON_NR)) )
  {
    uart_putc( 1 ); //request to refresh measurements
    LED_PORT ^=(1<<LED_NR); 
  }
}



void diode_update( uint8_t val)
{
  if( val < 20 )
  {
    ORANGE_OFF;
    RED_ON;
    GREEN_OFF;
  }
  else if( val< 38)
  {
    ORANGE_ON;
    RED_OFF;
    GREEN_OFF;
  }
  else
  {
    ORANGE_OFF;
    RED_OFF;
    GREEN_ON;
  }
}