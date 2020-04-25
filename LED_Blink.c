#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= 0XFF;
    while(1)
    {
        PORTB = 0XFF;          
        _delay_ms(1000);                                           /* wait */

        PORTB = 0X00;          /* Turn off all B pins, including LED */
        _delay_ms(1000);                                           /* wait */

    }                                                  /* End event loop */
    return 0;
		  
}
