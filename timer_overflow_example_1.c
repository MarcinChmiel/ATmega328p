//Example shows how to set timer TC0.
//Timer TC0 counts from 0 to 255 and then switch LED state.
//Prescaler 1024 give to us 1Khz frequency.

#include <avr/io.h>
#include <avr/interrupt.h>

int main()
{
	DDRC |= (1<<PC5);			//PC5 as output
	TCCR0B |= (1<<CS02) | (1<<CS00);	//Prescaler 1024 ( 1Mhz/1024 = 1000Hz )
	TIMSK0 |= (1<<TOIE0);			//Overflow interrupt enabled
	sei();					//Global permission for interrupts
	while(1);
}


ISR(TIMER0_OVF_vect)				//Interrupt function for timer overflow
{
	PORTC ^= (1<<PC5);
}
