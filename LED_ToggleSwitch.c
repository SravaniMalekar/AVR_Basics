#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	uint8_t LEDState = 0;
	uint8_t buttonNew;
	uint8_t buttonOld = 1;
    
	DDRB |= 1<<5;
	DDRB &= ~(1<<0);
	while(1)
    {
       buttonNew = (PINB & (1<<0));
	   if((buttonOld ==0)& (buttonNew==1))
	   {
		   if(LEDState ==0)
		   {
			   PORTB |= 1<<5;
			   LEDState=1;
           }
	       else
		   {
			   PORTB &= ~(1<<5);
			   LEDState=0;
		   }
	   }
	   buttonOld = buttonNew;
	}
}
