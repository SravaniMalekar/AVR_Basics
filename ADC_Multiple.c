/*
 * adcmultiple.c
 *
 * Created: 14-05-2020 01:29:44
 * Author : Sravani Malekar
 */ 

#define F_CPU 1600000UL
#include <avr/io.h>
#include <util/delay.h>
#define LED_PORT PORTB
#define RED_LED 1
#define GREEN_LED 0
#define channel1 (1 << MUX0)
#define channel2 (1 << MUX1)

void Init_ADC0(void);
uint16_t readADC(uint8_t channel);
int main(void)
{
	Init_ADC0();
	DDRB |= 0xFF;
	uint16_t ldr1;
	uint16_t ldr2;
	while(1)
	{

		
		ldr1 = readADC(channel1);
		ldr2 = readADC(channel2);
		
		if(ldr1 > ldr2){
			LED_PORT |= (1 << GREEN_LED);
			LED_PORT &= ~(1 << RED_LED);
		}
		else if(ldr1 < ldr2){
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
uint16_t readADC(uint8_t channel){
	
	ADMUX = (11110000 & ADMUX) | channel;
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	return(ADC);
}
