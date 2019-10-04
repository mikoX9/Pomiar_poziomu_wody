#include <avr/io.h>
#include <avr/interrupt.h>
#include "../lib/d_led.h"

volatile uint8_t cy1;
volatile uint8_t cy2;
volatile uint8_t cy3;
volatile uint8_t cy4;


const uint8_t liczby[11]=                 //zapisywanie do pamieci FLASH, tablica ustalona anod
{
		(1<< 0)+(1<< 1)+(1<< 2)+(1<< 4)+(1<< 5)+(1<< 6),			//0
		(1<< 2)+(1<< 5),											//1
		(1<< 0)+(1<< 2)+(1<< 3)+(1<< 4)+(1<< 6),					//2
		(1<< 0)+(1<< 2)+(1<< 3)+(1<< 5)+(1<< 6),					//3
		(1<< 1)+(1<< 2)+(1<< 3)+(1<< 5),							//4
		(1<< 0)+(1<< 1)+(1<< 3)+(1<< 5)+(1<< 6),					//5
		(1<< 0)+(1<< 1)+(1<< 3)+(1<< 4)+(1<< 5)+(1<< 6),			//6
		(1<< 0)+(1<< 2)+(1<< 5),									//7
		(1<< 0)+(1<< 1)+(1<< 2)+(1<< 3)+(1<< 4)+(1<< 5)+(1<< 6),	//8
		(1<< 0)+(1<< 1)+(1<< 2)+(1<< 3)+(1<< 5)+(1<< 6)				//9
};


void dispaly_off(void)
{
	TIMSK0 &=~ (1<<OCIE0A);

	SEG_A_OFF;
	SEG_B_OFF;
	SEG_C_OFF;
	SEG_D_OFF;
	SEG_E_OFF;
	SEG_F_OFF;
	SEG_G_OFF;

}

void dispaly_on(void)
{
	TIMSK0 |= (1<<OCIE0A);
}

void d_led_init(void)
{
	  DDR(SEG_A_PORT)   |=(1<<SEG_A_PIN);
    DDR(SEG_B_PORT)   |=(1<<SEG_B_PIN);
    DDR(SEG_C_PORT)   |=(1<<SEG_C_PIN);
    DDR(SEG_D_PORT)   |=(1<<SEG_D_PIN);
    DDR(SEG_E_PORT)   |=(1<<SEG_E_PIN);
    DDR(SEG_F_PORT)   |=(1<<SEG_F_PIN);
    DDR(SEG_G_PORT)   |=(1<<SEG_G_PIN);
    DDR(SEG_H_PORT)   |=(1<<SEG_H_PIN);

    DDR(COM_1_PORT)   |=(1<<COM_1_PIN);
    DDR(COM_2_PORT)   |=(1<<COM_2_PIN);
    DDR(COM_4_PORT)   |=(1<<COM_3_PIN);
    DDR(COM_4_PORT)   |=(1<<COM_4_PIN);

	//ustawienia timera

	TCCR0A |=(1<<WGM01);	//tryb ctc
	TCCR0B |= (1<<CS00) | (1<<CS02);	//preskaler 1024
	OCR0A = 38;		//dodatkowy podzia� przez 38
	TIMSK0 |= (1<<OCIE0A);	//zezwolenie na przerwania od porownania z rejestrem OCR0A
}


void display(uint16_t number)
{
    cy1= number/1000;
		cy2= (number%1000)/100;
		cy3= (number%100)/10;
		cy4= number%10;
}





ISR(TIMER0_COMPA_vect)
{
    static uint8_t cyfra;
    static uint8_t licznik = 1;


    if(licznik==5)
        licznik=1;

#if COM_A == 1

    if(licznik==1)
    {
        COM_1_ON;
        COM_2_OFF;
        COM_3_OFF;
        COM_4_OFF;

        cyfra = cy1;
    }else
    if(licznik==2)
    {
        COM_1_OFF;
        COM_2_ON;
        COM_3_OFF;
        COM_4_OFF;

        cyfra = cy2;
    }else
    if(licznik==3)
    {
        COM_1_OFF;
        COM_2_OFF;
        COM_3_ON;
        COM_4_OFF;

        cyfra = cy3;
    }else
    if(licznik==4)
    {
        COM_1_OFF;
        COM_2_OFF;
        COM_3_OFF;
        COM_4_ON;

        cyfra = cy4;
    }

//dla wspolnej anody podaje zera na segmenty i jedynki na comy
    switch( cyfra )
    {
        case 0  :
            SEG_A_OFF;
            SEG_B_OFF;
            SEG_C_OFF;
            SEG_D_ON;
            SEG_E_OFF;
            SEG_F_OFF;
            SEG_G_OFF;
            break;
        case 1  :
            SEG_A_ON;
            SEG_B_ON;
            SEG_C_OFF;
            SEG_D_ON;
            SEG_E_ON;
            SEG_F_OFF;
            SEG_G_ON;
            break;
        case 2  :
            SEG_A_OFF;
            SEG_B_ON;
            SEG_C_OFF;
            SEG_D_OFF;
            SEG_E_OFF;
            SEG_F_ON;
            SEG_G_OFF;
            break;
        case 3  :
            SEG_A_OFF;
            SEG_B_ON;
            SEG_C_OFF;
            SEG_D_OFF;
            SEG_E_ON;
            SEG_F_OFF;
            SEG_G_OFF;
            break;
        case 4  :
            SEG_A_ON;
            SEG_B_OFF;
            SEG_C_OFF;
            SEG_D_OFF;
            SEG_E_ON;
            SEG_F_OFF;
            SEG_G_ON;
            break;
        case 5  :
            SEG_A_OFF;
            SEG_B_OFF;
            SEG_C_ON;
            SEG_D_OFF;
            SEG_E_ON;
            SEG_F_OFF;
            SEG_G_OFF;
            break;
        case 6  :
            SEG_A_OFF;
            SEG_B_OFF;
            SEG_C_ON;
            SEG_D_OFF;
            SEG_E_OFF;
            SEG_F_OFF;
            SEG_G_OFF;
            break;
        case 7  :
            SEG_A_OFF;
            SEG_B_ON;
            SEG_C_OFF;
            SEG_D_ON;
            SEG_E_ON;
            SEG_F_OFF;
            SEG_G_ON;
            break;
        case 8  :
            SEG_A_OFF;
            SEG_B_OFF;
            SEG_C_OFF;
            SEG_D_OFF;
            SEG_E_OFF;
            SEG_F_OFF;
            SEG_G_OFF;
            break;
        case 9  :
            SEG_A_OFF;
            SEG_B_OFF;
            SEG_C_OFF;
            SEG_D_OFF;
            SEG_E_ON;
            SEG_F_OFF;
            SEG_G_OFF;
            break;

    }
#else  			//dla wspolnej katody

    if(licznik==1)
    {
      /*  COM_1_OFF; //uruchamiane zerem
        COM_2_ON;
        COM_3_ON;
        COM_4_ON;
*/
				COM_1_ON;		//uruchamiane jedynka, dla tranzysotra npn
				COM_2_OFF;
				COM_3_OFF;
				COM_4_OFF;

				cyfra = cy1;
    }else
    if(licznik==2)
    {
        /*COM_1_ON;
        COM_2_OFF;
        COM_3_ON;
        COM_4_ON;*/

				COM_1_OFF;
        COM_2_ON;
        COM_3_OFF;
        COM_4_OFF;

        cyfra = cy2;
    }else
    if(licznik==3)
    {
      /*  COM_1_ON;
        COM_2_ON;
        COM_3_OFF;
        COM_4_ON;*/
				COM_1_OFF;
	      COM_2_OFF;
	      COM_3_ON;
	      COM_4_OFF;

        cyfra = cy3;
    }else
    if(licznik==4)
    {
      /*  COM_1_ON;
        COM_2_ON;
        COM_3_ON;
        COM_4_OFF;*/

				COM_1_OFF;
        COM_2_OFF;
        COM_3_OFF;
        COM_4_ON;

        cyfra = cy4;
    }


//dla wspolnej katody podaje jedynki na segmenty i zera na comy
    switch( cyfra )
    {
        case 0  :
            SEG_A_ON;
            SEG_B_ON;
            SEG_C_ON;
            SEG_D_OFF;
            SEG_E_ON;
            SEG_F_ON;
            SEG_G_ON;
            break;
        case 1  :
            SEG_A_OFF;
            SEG_B_OFF;
            SEG_C_ON;
            SEG_D_OFF;
            SEG_E_OFF;
            SEG_F_ON;
            SEG_G_OFF;
            break;
        case 2  :
            SEG_A_ON;
            SEG_B_OFF;
            SEG_C_ON;
            SEG_D_ON;
            SEG_E_ON;
            SEG_F_OFF;
            SEG_G_ON;
            break;
        case 3  :
            SEG_A_ON;
            SEG_B_OFF;
            SEG_C_ON;
            SEG_D_ON;
            SEG_E_OFF;
            SEG_F_ON;
            SEG_G_ON;
            break;
        case 4  :
            SEG_A_OFF;
            SEG_B_ON;
            SEG_C_ON;
            SEG_D_ON;
            SEG_E_OFF;
            SEG_F_ON;
            SEG_G_OFF;
            break;
        case 5  :
            SEG_A_ON;
            SEG_B_ON;
            SEG_C_OFF;
            SEG_D_ON;
            SEG_E_OFF;
            SEG_F_ON;
            SEG_G_ON;
            break;
        case 6  :
            SEG_A_ON;
            SEG_B_ON;
            SEG_C_OFF;
            SEG_D_ON;
            SEG_E_ON;
            SEG_F_ON;
            SEG_G_ON;
            break;
        case 7  :
            SEG_A_ON;
            SEG_B_OFF;
            SEG_C_ON;
            SEG_D_OFF;
            SEG_E_OFF;
            SEG_F_ON;
            SEG_G_OFF;
            break;
        case 8  :
            SEG_A_ON;
            SEG_B_ON;
            SEG_C_ON;
            SEG_D_ON;
            SEG_E_ON;
            SEG_F_ON;
            SEG_G_ON;
            break;
        case 9  :
            SEG_A_ON;
            SEG_B_ON;
            SEG_C_ON;
            SEG_D_ON;
            SEG_E_OFF;
            SEG_F_ON;
            SEG_G_ON;
            break;

    }
#endif



    licznik++;


}
