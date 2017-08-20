//Example shows how to programm microswitch.
//Every time You press microswitch - You switch LED.

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

int main()
{
	DDRD |= (1<<PD0);							//PD0 as output for LED
	unsigned last_button_state = 0;
	while(1)
	{
		unsigned stan_przycisku = PINC & (1<<PC5);			//PC5 as microswitch state
		if(stan_przycisku != last_button_state)
		{
			_delay_ms(20);
			if(stan_przycisku == (1<<PC5))
			PORTD ^= (1<<PD0);
		}
		last_button_state = stan_przycisku;
	}
}
