//Example shows how to use LM35 temperature sensor with ADC

#include <avr/io.h>
#include <stdio.h>
#define F_CPU 1000000UL
#include <util/delay.h>	
#define UBRR_VALUE 12							//BAUD 4800
#define VREF 1.1
void send_char(char);
float check_value(void);
float data;
char result[7];
unsigned i;

int main()
{
	//USART Configuration	
	UCSR0B |= (1<<TXEN0);						//Transmitter enable
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);				//8 data bits
	UBRR0L |= UBRR_VALUE;						//Baud rate
	UBRR0H |= (UBRR_VALUE>>8);
	
	//ADC Configuration
	ADMUX |= (1<<REFS1) | (1<<REFS0);				//VREF 1.1V
	ADMUX |= (1<<MUX2);						//ADC PIN 4
	ADCSRA |= (1<<ADEN);						//ADC enable
	ADCSRA |= (1<<ADPS1) | (1<<ADPS0);				//Prescaler 8 ( 1Mhz / 8 = 125Khz, 50Khz - 200kHz is ok )
	while(1)
	{
		data = check_value();
		sprintf(result, "%.1f\r\n", data*100*VREF/1024);	
		for(i=0; i<7; i++)
		{
			send_char(result[i]);
		}
		_delay_ms(1000);
	}

}

void send_char(char c)
{
	while(!(UCSR0A & (1<<UDRE0)));					//Wait until UDR0 empty
	UDR0 = c;
}

float check_value(void)
{
	ADCSRA |= (1<<ADSC);						//Start conversion
	while(ADCSRA & (1<<ADSC));					//Wait until conversion is finished
	return ADC;
}
