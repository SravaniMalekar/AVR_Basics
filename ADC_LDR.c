
#define F_CPU 1600000UL
#include <avr/io.h>
#include <util/delay.h>
#define LED_PORT PORTB
#define RED_LED 1
#define GREEN_LED 0

void Init_ADC0(void);
int main(void)
{
	Init_ADC0();
	uint16_t adcValue;
	DDRB |= 0xFF;
    while(1)
    {

        ADCSRA |= (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
		adcValue = ADC;
		
		if(adcValue > 100){
			LED_PORT |= (1 << GREEN_LED);
			LED_PORT &= ~(1 << RED_LED);
		}
		else if(adcValue < 100){
			LED_PORT |= (1 << RED_LED);
			LED_PORT &= ~(1 << GREEN_LED);
		}
		_delay_ms(250);
    }
	return 0;
}
void Init_ADC0(void){
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1)|(1<< ADPS2);
}
