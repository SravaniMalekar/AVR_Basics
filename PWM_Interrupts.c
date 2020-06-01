/*
 * PWM_Interrupts.c
 *
 * Created: 01-06-2020 20:42:21
 * Author : Sravani Malekar
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_PORT PORTB
#define LED_DDR DDRB
#define DELAY 3

volatile uint8_t brightnessA;
volatile uint8_t brightnessB;

static inline void inittimer0(void){
	TCCR0B |= (1 << CS01)|(1<< CS00);     //setting prescaler as 64
	TIMSK0 |= (1 << OCIE0A)|(1 << OCIE0B);//setting output compare match interrupts A&B
	TIMSK0 |= (1 << TOIE0);               //setting overflow interrupt
	sei();
}

ISR(TIMER0_COMPA_vect){
	LED_PORT &= 0b11110000;     //clearing lower led bits
}

ISR(TIMER0_COMPB_vect){
	LED_PORT &= 0b00001111;     //clearing upper bits
}

ISR(TIMER0_OVF_vect){
	LED_PORT=0XFF;              //setting all led bits
	OCR0A=brightnessA;          //setting value of output compare A
	OCR0B=brightnessB;          //setting value of output compare B
}
int main(void)
{
    LED_DDR = 0XFF;            //setting led port as output
	uint8_t i; 
	inittimer0();              //initializing timer interrupts
    while (1) 
    {
		for(i=0;i<255;i++){   //varying brightness
			_delay_ms(DELAY); //delay for ISR to execute
			brightnessA=i;    
			brightnessB=255-i;
		}
		for(i=254;i>0;i++){
			_delay_ms(DELAY);
			brightnessA =i;
			brightnessB =255 -i;
		}
		
    }
	return 0;
}
