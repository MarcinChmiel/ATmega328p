//Example shows how to programm microswitch.
//Microswitch is pressed - LED turned on
//Microswitch is unpressed - LED turned off

#include <avr/io.h>

int main()
{

	DDRC |= (1<<PC5);					//PC5 as output for LED
	while(1)
	{
		if(PIND & (1<<PD0))				//if microswitch is pressed
		{
			PORTC |= (1<<PC5);			//Turn on LED
		}
		else
		{
			PORTC &= ~(1<<PC5);			//Turn off LED
		}
	}
}
