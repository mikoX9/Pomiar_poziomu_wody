#include <avr/io.h>
#include <util/delay.h>
#include "lib/ultra.h"
#include "lib/rs232.h"


#define NOM 3 //number of measurements in one serie
#define DBM 100 //delay beetwen measurements  !!!! >12 !!!!

#define LED_DDR   DDRD
#define LED_PORT  PORTD
#define LED_NR    5
#define LED_ON    LED_PORT |= (1 << LED_NR);
#define LED_OFF   LED_PORT &=~ (1 << LED_NR);

volatile uint16_t timer1 = 0;

void blikn_led(int delay);
void send_measure( uint8_t value);
uint8_t execute_measurement();

int main()
{
  USART_Init(__UBRR);
  ultra_init();

  sei();

  LED_DDR |= (1 << LED_NR); //led
  LED_ON;


  //timer
  TCCR0A |= (1<<WGM01);           //CTC
  TCCR0B |= (1<<CS01)|(1<<CS00);  //prescaler 64
  TIMSK |= (1<<OCIE0A);          //interrupt enable
  OCR0A = 250;                    //interrupt generats every 1ms


  //uint16_t tmp_value, tmp_trans;


  while (1)
  {
    /*
    if( !timer1 )
    {



      tmp_value = measure();
      LED_ON;
      _delay_ms(12);
      LED_OFF;

      if( tmp_value<200 && tmp_value>1)
      {
        uart_putc('h');    //beginning of the frame

        //*********************  DATA  ***********************
        uart_putc( tmp_value ); //entire value
        //******************************************************

        uart_putc('t');  //end of the frame

        //LED_PORT ^=(1<<LED_NR);

        timer1 = 3000;
      }
      else
      {
        timer1 = 100;
      }

    }
*/

    if( uart_getc() == 1)   //request for send a measurement
    {
      send_measure( execute_measurement() );
    }
  } //end of while

}

uint8_t execute_measurement()
{
  static uint16_t measure_table[NOM];

  static uint16_t tmp_value;
  static uint16_t sum_value;

  sum_value = 0;
  for(int i=0; i<NOM; i++)
  {
    do
    {
      tmp_value = measure();
      blikn_led(12);
      _delay_ms(DBM - 12);

    }
    while( !(tmp_value > 0 || tmp_value < 200));

    sum_value += tmp_value;
  }


  return (sum_value / NOM);
}


void send_measure( uint8_t value)
{
  uart_putc('h');    //beginning of the frame
  //*********************  DATA  ***********************
  uart_putc( value ); //entire value
  //******************************************************
  uart_putc('t');  //end of the frame
}

void blikn_led(int delay)
{
  LED_ON;
  while (0 < delay)
  {
    _delay_ms(1);
    --delay;
  }
  LED_OFF;
}

ISR( TIMER0_COMPA_vect )
{
  if(timer1);
    timer1--;
}
