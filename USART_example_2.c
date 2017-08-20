//Example shows how to receive a char and send it back via USART using interrupts.

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#define UBRR_VALUE 12				//Value for F_CPU 1MHZ & BAUD 4800
void usart_init(void);
volatile char c = '\0';


int main()
{
	usart_init();
	sei();					//Global permission for interrupts
	while(1)
	{
	}
}


void usart_init()
{
	UBRR0L |= UBRR_VALUE;			//Usart Baud Rate Register
	UBRR0H |= (UBRR_VALUE>>8);
	UCSR0B |= (1<<TXEN0) | (1<<RXEN0);	//Transmitter & Receiver enable
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);	//8 data bits
	UCSR0B |= (1<<UDRIE0);			//Usart data register empty interrupt enable
	UCSR0B |= (1<<RXCIE0);			//RX Complete interrupt enable
}

ISR(USART_UDRE_vect)				//Interrupt function for transmission
{
	if(c != '\0')
	{
		UDR0 = c;
		c = '\0';
	}
}						

ISR(USART_RX_vect)				//Interrupt function for receiving
{
	c = UDR0;
}