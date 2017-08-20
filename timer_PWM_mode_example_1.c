//Example shows how to set timer in PWM mode.
//Every time You press microswitch - You increase LED's brighness.
//When LED brightness is max, then You start decrease it's brightness.

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#define LED (1<<PD6)
#define BUTTON (1<<PD0)

int main()
{
	TCCR0A |= (1<<WGM02) | (1<WGM01) | (1<<WGM00);			//Fast PWM mode, Top OCRA register
	TCCR0B |= (1<<CS01);						//Prescaler 8
	TCCR0A |= (1<<COM0A1);						//Non-inverting mode
	OCR0A = 0;
	DDRD |= LED;							//PD6 as output
	unsigned k = 50;

	unsigned last_button_state = 0;
	while(1)
	{
		unsigned button_state = PIND & BUTTON;
		if(button_state != last_button_state)
		{
			_delay_ms(20);
			if(button_state == BUTTON)
			{
				if((OCR0A+k) < 0)
					OCR0A=0;
				if((OCR0A+k) > 255)
					OCR0A=255;
				if(OCR0A <=0 || OCR0A >= 255)
					k *= -1;
				OCR0A+=k;
			}
		}
		last_button_state = button_state;
	}
}
