//Example shows how to program microswitch.
//Every time You press microswitch - You switch LED mode:
//First mode - LED constantly lit
//Second mode - LED blinks
//PD0 as input from microswitch
//PC5 as output for LED
//This example doesn't use interrupts.



#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#define LED (1<<PC5)
#define BUTTON (1<<PD0)

int main()
{
	unsigned last_button_state = 0;
	unsigned LED_mode = 0;
	unsigned i;
	DDRC |= (1<<PC5);
	while(1)
	{
		unsigned button_state = PIND & BUTTON;
		if(button_state != last_button_state)
		{
			_delay_ms(20);
			if(button_state == BUTTON)
			LED_tryb ^= 1;
		}
		last_button_state = button_state;
		switch(LED_mode & 1)							//LED mode depends on LSB of LED_mode variable
		{
			case 0:		PORTC |= LED;
					break;
			case 1:		
					for(i=1; i<=500; i++)
					{
					if((PIND & BUTTON) != last_button_state)
					break;
					_delay_ms(1);
					}
					PORTC ^= LED;
					break;
		}
	}
}
