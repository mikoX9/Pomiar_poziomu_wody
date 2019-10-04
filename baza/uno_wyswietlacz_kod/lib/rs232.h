#ifndef MKUART_H_
#define MKUART_H_


#define UART_BAUD 9600		// tu definiujemy interesuj¹c¹ nas prêdkoœæ
#define __UBRR ((F_CPU+UART_BAUD*8UL) / (16UL*UART_BAUD)-1) // obliczamy UBRR dla U2X=0



#define UART_RX_BUF_SIZE 32 // definiujemy bufor o rozmiarze 32 bajtów
// definiujemy maskê dla naszego bufora
#define UART_RX_BUF_MASK ( UART_RX_BUF_SIZE - 1)

#define UART_TX_BUF_SIZE 16 // definiujemy bufor o rozmiarze 16 bajtów
// definiujemy maskê dla naszego bufora
#define UART_TX_BUF_MASK ( UART_TX_BUF_SIZE - 1)



// deklaracje funkcji publicznych

void USART_Init( uint16_t baud );

char uart_getc(void);
void uart_putc( char data );
void uart_puts(char *s);

void uart_puts_Trans(char *s);

void uart_putint(int value, int radix);


void USART_Transmit( unsigned char data );
unsigned char USART_Receive(void);




#endif /* MKUART_H_ */
