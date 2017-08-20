//Example shows how to program microswitch.
//Every time You press microswitch - You switch LED mode:
//First mode - LED constantly lit
//Second mode - LED blinks
//PD0 as input from microswitch
//PC5 as output for LED
//This example uses interrupts.




#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#define BUTTON (1<<PD0)
#define LED (1<<PC5)

volatile unsigned i = 0;
unsigned LED_mode = 0;
unsigned last_button_state=0;

int main()
{
	DDRC |= LED;

	TCCR0B |= (1<<CS02) | (1<<CS00);				//Prescaler 1024 ( 1Mhz/1024 = 1000Hz )
	TIMSK0 |= (1<<TOIE0);						//Overflow interrupts enabled
	sei();								//Global permission for interrupts

	while(1)
	{
		unsigned button_state = PIND & BUTTON;
		if(button_state != last_button_state)
		{
			_delay_ms(20);					//Deboucing
			if(button_state == BUTTON)
			{
				LED_mode ^= 1;				//Choose LED mode
			}
		}
		last_button_state = button_state;

	}
}

ISR(TIMER0_OVF_vect)							//Interrupt function for timer overflow
{
	switch(LED_mode & 1)
		{
			case 0: PORTC |= LED;
				break;
			case 1: PORTC ^= LED;
				break;
		}
}