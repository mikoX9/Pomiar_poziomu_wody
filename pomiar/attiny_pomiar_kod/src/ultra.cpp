#include "../lib/ultra.h"


volatile uint16_t distance;
volatile uint8_t measure_flag;

void ultra_init()
{
    
   DDRB &=~(1<<PB0);  //ICP1
   //PORTB |=(1<<PB0);

  DDR(TRIG_PORT) |=(1<<TRIG_PIN); //trigger
  PORT(TRIG_PORT) &=~(1<<TRIG_PIN);


  TCCR1B |=(1<<ICES1);  //riseing eage
  //TCCR1B |= (1<<CS12) | (1<<CS10); //preskaler 64
  TCCR1B |= (1<<CS11);        //preskaler 8
  TIMSK |= (1<<ICIE1);             //enable interrupt
}

uint16_t measure()
{
    measure_flag = 0;
     PORTB |=(1<<PB1);
    _delay_us(10);
    PORTB &=~(1<<PB1);
    while( !measure_flag );

    return distance;
}


ISR( TIMER1_CAPT_vect )
{
  static uint16_t start;
  static uint8_t licznik = 1;
  static uint32_t value;

  TCCR1B ^=(1<<ICES1);  //opposite edge

  if(licznik == 1)
  {
    start = ICR1;
    licznik = 2;
  }
  else
  {
    value = ICR1 - start;
    distance = (((value/2)*34)/2000);
    measure_flag = 1;
    PORTB ^=(1<<PD5);
    licznik = 1;
  }
}