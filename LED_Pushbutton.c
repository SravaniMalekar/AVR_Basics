#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<5); /*setting pin as output*/
	DDRB &= ~(1<<0);/*setting pin as input*/
    while(1)
    {
		if((PINB & (1<<0))==1)/*reading pin*/
		{
				PORTB &= ~(1<<5);
         
        }
	    else
		{
			PORTB |= 1<<5;
		}
	}
}
