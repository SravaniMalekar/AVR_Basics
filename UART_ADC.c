
#define F_CPU 16000000
#define BAUD 9600
#define BRC ((F_CPU/16/BAUD)-1)

#include <avr/io.h>
#include <util/delay.h>
#define LED_PORT PORTB
#define RED_LED 1
#define GREEN_LED 0

void Init_ADC0(void);
void USART_Init(void);
void transmit_byte(uint8_t data);
void print_byte(uint8_t byte);
int main(void)
{
	USART_Init();
	Init_ADC0();
	uint16_t adcValue;
	uint8_t val;
	DDRB |= 0xFF;
	while(1)
	{

		ADCSRA |= (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
		
		print_byte(ADCH);
		transmit_byte('\n');
	
		
		if(ADCH > 100){
			LED_PORT |= (1 << GREEN_LED);
			LED_PORT &= ~(1 << RED_LED);
		}
		else if(ADCH < 100){
			LED_PORT |= (1 << RED_LED);
			LED_PORT &= ~(1 << GREEN_LED);
		}
		_delay_ms(250);
	}
	return 0;
}
void Init_ADC0(void){
	ADMUX |= (1 << REFS0)|(1 << ADLAR);
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1)|(1<< ADPS2);
}
void USART_Init(void){
	UBRR0H = BRC >> 8;
	UBRR0L = BRC;
	
	UCSR0B =(1 << TXEN0);
	UCSR0C =(1 << UCSZ00)| (1<<UCSZ01);
}
void transmit_byte(uint8_t data){
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}
void print_byte(uint8_t byte){
	transmit_byte('0'+ (byte/100)); /* Hundreds */
	transmit_byte('0'+ ((byte/10) % 10)); /* Tens */
	transmit_byte('0'+ (byte % 10)); /* Ones */
}
