//AIN0	-	positive pin
//AIN1	-	negative pin
//ACO	-	Analog Comparator Output (1 when AIN0 > AIN1)

//AIN1	-	Input voltage from potentiometer

//Turn on LED when AIN0 > AIN1


#include <avr/io.h>

int main()
{
	while(1)
	{
		ACSR |= (1<<ACBG);			//Reference voltage replaces positive input AIN0
		DDRD |= (1<<PD2);			//PD2 as output
		if(ACSR & (1<<ACO))			//AC0 set ?
		{
			PORTD |= (1<<PD2);		//Turn on LED
		}
		else
		PORTD &= ~(1<<PD2);			//Turn off LED
	}
}