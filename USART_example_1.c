//Example show how to receive a char and send it back via USART.

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#define UBRR_VALUE 12						//BAUD 4800

void send_char(char);
char receive_char(void);

int main()
{
	UBRR0L = UBRR_VALUE;					//Set BAUD RATE
	UBRR0H = (UBRR_VALUE>>8);
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);			//Transmitter & receiver enabled
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);			//8 data bits
	char c;

	
	while(1)
	{
		c = receive_char();
		send_char(c);
	}
}

void send_char(char x)
{
	while( !(UCSR0A & (1<<UDRE0)) );			//Wait for empty buffer, UDRE0=1
	UDR0 = x;
}

char receive_char(void)
{
	while(!(UCSR0A & (1<<RXC0)));				//Wait for full buffer, RXC0=1
	return UDR0;
}
