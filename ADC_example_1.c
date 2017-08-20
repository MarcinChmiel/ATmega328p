//Example shows how to measure voltage ( 0 - 1.1V ) and send result via USART to PC.

#include <avr/io.h>
#include <stdio.h>
#define VREF 1.1
#define F_CPU 1000000UL
#include <util/delay.h>
#define UBRR_VALUE 12							//BAUD 4800

void USART_send_byte(char);
float odczyt;
char result[7];

int main()
{
	//USART Configuration
	UBRR0L = UBRR_VALUE;
	UBRR0H = (UBRR_VALUE>>8);
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);				//Transmitter & receiver enabled
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);				//8 data bits
	unsigned i;
	
	//ADC Configuration
	ADMUX |= (1<<REFS1) | (1<<REFS0);				//Set Vref 1.1 V
	ADMUX |= (1<<MUX2) | (1<<MUX0);					//Choose channel ADC5
	ADCSRA |= (1<<ADEN);						//ADC enabledon on 8
	while(1)
	{
		ADCSRA |= (1<<ADSC);					//Start single conversion
		while(ADCSRA & (1<<ADSC));				//Wait for end of conversion
		data = ADC;						//Read from ADC data register
		sprintf(result, "%.2f\r\n", data * VREF / 1024);	//Convert to string

		for(i=0;i<=7;i++)					//Send result via USART
		{
			USART_send_byte(result[i]);
		}
		_delay_ms(1000);
	}
}

void USART_send_byte(char x)
{
	while( !(UCSR0A & (1<<UDRE0)) );				//Wait for empty buffer, UDRE0=1
	UDR0 = x;
}
