//Example shows how to measure voltage ( 0 - 5V ) and send result via USART to PC.

#include <avr/io.h>
#include <stdio.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#define UBRR_VALUE 12						//BAUD 4800
#define VREF 5
void send_char(char);
float check_value(void);
float data;
char result[7];
unsigned i;

int main()
{
	//USART Configuration	
	UCSR0B |= (1<<TXEN0);					//Transmitter enabled
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);			//8 data bits
	UBRR0L |= UBRR_VALUE;
	UBRR0H |= (UBRR_VALUE>>8);

	//ADC Configuration
	ADMUX |= (1<<REFS0);					//AVcc - Reference Voltage Selected
	ADMUX |= (1<<MUX2) | (1<<MUX0);				//ADC channel 5
	ADCSRA |= (1<<ADEN);					//ADC enabled
	ADCSRA |= (1<<ADPS1) | (1<<ADPS0);			//Prescaler 8 -> 1Mhz/8 = 125Khz ( 50 - 200kHz is ok )
	
	while(1)
	{
		data = check_value();				//Read from ADC data register
		sprintf(result, "%.2f\r\n", data*VREF/1024);	//Convert result to string
		for(i=0;i<7;i++)				//Send result via USART
		{
			send_char(result[i]);
		}
		_delay_ms(1000);
	}
}

void send_char(char c)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = c;
}

float check_value(void)
{
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return ADC;
}
