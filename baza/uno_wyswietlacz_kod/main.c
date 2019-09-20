#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "lib/rs232.h"
#include "lib/d_led.h"

#define LED_DDR   DDRB      //indicator
#define LED_PORT  PORTB
#define LED_NR    4
#define LED_ON    LED_PORT |=(1<<LED_NR)
#define LED_OFF   LED_PORT &=~(1<<LED_NR)

#define LED_GREEN_DDR   DDRD
#define LED_GREEN_PORT  PORTD
#define LED_GREEN_NR    5
#define GREEN_ON        LED_GREEN_PORT |=(1<<LED_GREEN_NR)
#define GREEN_OFF       LED_GREEN_PORT &=~(1<<LED_GREEN_NR)

#define LED_RED_DDR   DDRD
#define LED_RED_PORT  PORTD
#define LED_RED_NR    4
#define RED_ON        LED_RED_PORT |=(1<<LED_RED_NR)
#define RED_OFF       LED_RED_PORT &=~(1<<LED_RED_NR)

#define LED_ORANGE_DDR   DDRD
#define LED_ORANGE_PORT  PORTD
#define LED_ORANGE_NR    3
#define ORANGE_ON        LED_ORANGE_PORT |=(1<<LED_ORANGE_NR)
#define ORANGE_OFF       LED_ORANGE_PORT &=~(1<<LED_ORANGE_NR)

#define BUTTON_DDR  DDRD
#define BUTTON_PORT PORTD
#define BUTTON_PIN  PIND
#define BUTTON_NR   2         //INT0

/***********************   LIMITS    **************************/
#define RED_LIMIT     25
#define ORAGNE_LIMIT  50

/**************************************************************/


void diode_update( uint8_t val );
void blink_led( int delay);
void led_off(void);
void sleep_mode();
void wakeup_mode();

int main()
{
  LED_DDR |= (1 << LED_NR); //led
  LED_ON;



  USART_Init( __UBRR );
  d_led_init();

  display(0000);
	sei();

  _delay_ms(1000);



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

  sleep_mode();
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

        wakeup_mode();
        _delay_ms(3000);
        sleep_mode();

        EIMSK |= (1<<INT0); //enabling interrupt
      }

    }

  } // end of while

}


ISR( 	INT0_vect )
{
  EIMSK &=~ (1<<INT0);  //disabling interrupt
  _delay_ms(70);
  if( !(BUTTON_PIN & (1<<BUTTON_NR)) )
  {
    uart_putc( 1 ); //request to refresh measurements
    blink_led( 50 );
    _delay_ms(200);
  }
  else
    EIMSK |= (1<<INT0); //enabling interrupt
}

void sleep_mode()
{
  dispaly_off();
  led_off();
}

void wakeup_mode()
{
  dispaly_on();
}

void diode_update( uint8_t val)
{
  if( val < RED_LIMIT )
  {
    ORANGE_OFF;
    RED_ON;
    GREEN_OFF;
  }
  else if( val< ORAGNE_LIMIT)
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

void led_off(void)
{
  ORANGE_OFF;
  GREEN_OFF;
  RED_OFF;
}

void blink_led( int delay)
{
  LED_PORT |=(1<<LED_NR);
  while (0 < delay)
  {
    _delay_ms(1);
    --delay;
  }
  LED_PORT &=~(1<<LED_NR);
}
