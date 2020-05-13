#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define BUTTON 2
#define LED_PORT PORTB
#define LED1 1
#define LED0 0
#define BUTTON_PORT PORTD

ISR(INT0_vect)
{
	if(!(PIND & (1 << BUTTON))){
		LED_PORT |= (1 << LED1); 
	}
	else{
		LED_PORT &= ~(1 << LED1);
	}
}

void initInterrupt0(void){
	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC00);
	sei();
}

int main(void)
{
    DDRB = 0xFF;
	BUTTON_PORT |= (1 << BUTTON);
	initInterrupt0();
	
    while (1) 
    {
		_delay_ms(200);
		LED_PORT ^= (1 << LED0);
    }
	return 0;
}
