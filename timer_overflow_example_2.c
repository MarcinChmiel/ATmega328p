//Example shows how to set timer TC0.
//Timer switch LED state every 0,5s.
//Prescaler 1024 give to us 1Khz frequency.

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned i = 0;

int main()
{
	DDRC |= (1<<PC5);			//PC5 as output
	TCCR0B |= (1<<CS02) | (1<<CS00);	//Prescaler 1024 ( 1Mhz/1024 = 1000Hz )
	TIMSK0 |= (1<<TOIE0);			//Overflow interrupt enabled
	sei();					//Global permission for interrpts
	while(1);
}


ISR(TIMER0_OVF_vect)				//Interrupt function for timer overflow
{
	if(i==2)
	{
		PORTC ^= (1<<PC5);
		i=0;
	}
	i++;

}
