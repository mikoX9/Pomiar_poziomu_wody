#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "../lib/rs232.h"

// definiujemy w koñcu nasz bufor UART_RxBuf
volatile char UART_RxBuf[UART_RX_BUF_SIZE];
// definiujemy indeksy okreœlaj¹ce iloœæ danych w buforze
volatile uint8_t UART_RxHead; // indeks oznaczaj¹cy „g³owê wê¿a”
volatile uint8_t UART_RxTail; // indeks oznaczaj¹cy „ogon wê¿a”


// definiujemy w koñcu nasz bufor UART_RxBuf
volatile char UART_TxBuf[UART_TX_BUF_SIZE];
// definiujemy indeksy okreœlaj¹ce iloœæ danych w buforze
volatile uint8_t UART_TxHead; // indeks oznaczaj¹cy „g³owê wê¿a”
volatile uint8_t UART_TxTail; // indeks oznaczaj¹cy „ogon wê¿a”


void USART_Init( uint16_t baud ) {


	//speed of
	UBRR0H = (uint8_t)(baud>>8);
	UBRR0L = (uint8_t)baud;

	//Eneabling reciver, transmitter, and interrupt
	UCSR0B = (1<<RXEN0)|(1<<TXEN0) |(1<<RXCIE0);

	//Set frame format: 8data, 1stop bit
	//UCSR0C = (3<<UCSZ00);
	UCSR0C = (1<<USBS0)|(3<<UCSZ00); //2 stop bits

}



////////////////////////////////////////////

//transmiting that required waiting in main loop
void USART_Transmit( unsigned char data )
{

//Wait for empty transmit buffer

while( !( UCSR0A & (1<<UDRE0)) );

// Put data into buffer, sends the data
UDR0 = data;

}


unsigned char USART_Receive(void)
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}


/////////////////////////////////////////////

//dodaje dane do bufora cyklicznego
void uart_putc( char data ) {
	uint8_t tmp_head;

    tmp_head  = (UART_TxHead + 1) & UART_TX_BUF_MASK;

          // pêtla oczekuje je¿eli brak miejsca w buforze cyklicznym na kolejne znaki
    while ( tmp_head == UART_TxTail ){}

    UART_TxBuf[tmp_head] = data;
    UART_TxHead = tmp_head;

    // inicjalizujemy przerwanie wystêpuj¹ce, gdy bufor jest pusty, dziêki
    // czemu w dalszej czêœci wysy³aniem danych zajmie siê ju¿ procedura
    // obs³ugi przerwania
    UCSR0B |= (1<<UDRIE0);
}


//wysyla string
void uart_puts(char *s)
{
  register char c;
  while ((c = *s++)) uart_putc(c);			// dopóki nie napotkasz 0 wysy³aj znak
}

void uart_puts_Trans(char *s)
{
  register char c;
  while ((c = *s++)) USART_Transmit(c);			// dopóki nie napotkasz 0 wysy³aj znak
}


//wysyla int
void uart_putint(int value, int radix)
{
	char string[17];			// bufor na wynik funkcji itoa
	itoa(value, string, radix);		// konwersja value na ASCII
	uart_puts(string);			// wyœlij string na port szeregowy
}



// definiujemy procedure obslugi przerwania nadawczego, pobierajac dane z bufora cyklicznego
ISR( USART_UDRE_vect)  {
    // sprawdzamy czy indeksy sa rózne
    if ( UART_TxHead != UART_TxTail ) {
    	// obliczamy i zapamiêtujemy nowy indeks ogona wê¿a (mo¿e siê zrównaæ z g³ow¹)
    	UART_TxTail = (UART_TxTail + 1) & UART_TX_BUF_MASK;
    	// zwracamy bajt pobrany z bufora  jako rezultat funkcji
    	UDR0 = UART_TxBuf[UART_TxTail];
    } else {
	// zerujemy flagê przerwania wystêpuj¹cego gdy bufor pusty
	UCSR0B &= ~(1<<UDRIE0);
    }
}



////////////////////////////////////////////////////


// definiujemy funkcjê pobieraj¹c¹ jeden bajt z bufora cyklicznego
char uart_getc(void) {
    // sprawdzamy czy indeksy s¹ równe
    if ( UART_RxHead == UART_RxTail ) return 0;

    // obliczamy i zapamiêtujemy nowy indeks „ogona wê¿a” (mo¿e siê zrównaæ z g³ow¹)
    UART_RxTail = (UART_RxTail + 1) & UART_RX_BUF_MASK;
    // zwracamy bajt pobrany z bufora  jako rezultat funkcji
    return UART_RxBuf[UART_RxTail];
}

// definiujemy procedurê obs³ugi przerwania odbiorczego, zapisuj¹c¹ dane do bufora cyklicznego
ISR( USART_RX_vect ) {
    uint8_t tmp_head;
    char data;

    data = UDR0; //pobieramy natychmiast bajt danych z bufora sprzêtowego

    // obliczamy nowy indeks „g³owy wê¿a”
    tmp_head = ( UART_RxHead + 1) & UART_RX_BUF_MASK;

    // sprawdzamy, czy w¹¿ nie zacznie zjadaæ w³asnego ogona
    if ( tmp_head == UART_RxTail ) {
    	// tutaj mo¿emy w jakiœ wygodny dla nas sposób obs³u¿yæ  b³¹d spowodowany
    	// prób¹ nadpisania danych w buforze, mog³oby dojœæ do sytuacji gdzie
    	// nasz w¹¿ zacz¹³by zjadaæ w³asny ogon
    } else {
				UART_RxHead = tmp_head; 		// zapamiêtujemy nowy indeks
				UART_RxBuf[tmp_head] = data; 	// wpisujemy odebrany bajt do bufora
    }
}
