#ifndef RS232_H_
#define RS232_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// *** PORT
#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
// *** PIN
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)
// *** DDR
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)

/*****************************************/

#define TRIG_PIN    0
#define TRIG_PORT   B

extern volatile uint16_t distance;

void ultra_init();

uint16_t measure();

#endif
