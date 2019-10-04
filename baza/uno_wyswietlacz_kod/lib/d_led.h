#ifndef D_LED_H_
#define D_LED_H_

#include <avr/io.h>

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

#define COM_A 0     //dla wspolnej anody 1 dla wspolnej katody 0



//numerowanie segmentow od gory i od lewej

#define SEG_A_PIN   1
#define SEG_A_PORT  B
#define SEG_A_ON    PORT(SEG_A_PORT) |=(1<<SEG_A_PIN)
#define SEG_A_OFF   PORT(SEG_A_PORT) &=~(1<<SEG_A_PIN)

#define SEG_B_PIN   0
#define SEG_B_PORT  B
#define SEG_B_ON    PORT(SEG_B_PORT) |=(1<<SEG_B_PIN)
#define SEG_B_OFF   PORT(SEG_B_PORT) &=~(1<<SEG_B_PIN)

#define SEG_C_PIN   2
#define SEG_C_PORT  B
#define SEG_C_ON    PORT(SEG_C_PORT) |=(1<<SEG_C_PIN)
#define SEG_C_OFF   PORT(SEG_C_PORT) &=~(1<<SEG_C_PIN)

#define SEG_D_PIN   1
#define SEG_D_PORT  C
#define SEG_D_ON    PORT(SEG_D_PORT) |=(1<<SEG_D_PIN)
#define SEG_D_OFF   PORT(SEG_D_PORT) &=~(1<<SEG_D_PIN)

#define SEG_E_PIN   5
#define SEG_E_PORT  C
#define SEG_E_ON    PORT(SEG_E_PORT) |=(1<<SEG_E_PIN)
#define SEG_E_OFF   PORT(SEG_E_PORT) &=~(1<<SEG_E_PIN)

#define SEG_F_PIN   2
#define SEG_F_PORT  C
#define SEG_F_ON    PORT(SEG_F_PORT) |=(1<<SEG_F_PIN)
#define SEG_F_OFF   PORT(SEG_F_PORT) &=~(1<<SEG_F_PIN)

#define SEG_G_PIN   4
#define SEG_G_PORT  C
#define SEG_G_ON    PORT(SEG_G_PORT) |=(1<<SEG_G_PIN)
#define SEG_G_OFF   PORT(SEG_G_PORT) &=~(1<<SEG_G_PIN)

#define SEG_H_PIN   3       //kropka
#define SEG_H_PORT  C
#define SEG_H_ON    PORT(SEG_H_PORT) |=(1<<SEG_H_PIN)
#define SEG_H_OFF   PORT(SEG_H_PORT) &=~(1<<SEG_H_PIN)


//piny wspolne numerowane od lewej
#define COM_1_PIN   3
#define COM_1_PORT  B
#define COM_1_ON    PORT(COM_1_PORT) |=(1<<COM_1_PIN)
#define COM_1_OFF   PORT(COM_1_PORT) &=~(1<<COM_1_PIN)

#define COM_2_PIN   6
#define COM_2_PORT  D
#define COM_2_ON    PORT(COM_2_PORT) |=(1<<COM_2_PIN)
#define COM_2_OFF   PORT(COM_2_PORT) &=~(1<<COM_2_PIN)

#define COM_3_PIN   7
#define COM_3_PORT  D
#define COM_3_ON    PORT(COM_3_PORT) |=(1<<COM_3_PIN)
#define COM_3_OFF   PORT(COM_3_PORT) &=~(1<<COM_3_PIN)

#define COM_4_PIN   0
#define COM_4_PORT  C
#define COM_4_ON    PORT(COM_4_PORT) |=(1<<COM_4_PIN)
#define COM_4_OFF   PORT(COM_4_PORT) &=~(1<<COM_4_PIN)

/*****************************************/


extern volatile uint8_t cy1;	//extern- powoduje ze te zmienne beda dostepne we wszystkich modulach
extern volatile uint8_t cy2;	//ktore maja dolaczony plik tej biblioteki
extern volatile uint8_t cy3;
extern volatile uint8_t cy4;

void d_led_init(void);

void display(uint16_t number);
//void display(char c1, char c2, char c3, char c4);

#endif /* D_LED_H_ */
