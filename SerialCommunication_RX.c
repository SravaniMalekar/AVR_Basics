#include <avr/io.h>

#define F_CPU 16000000
#define BAUD 9600
#define BRC  ((F_CPU/16/BAUD)-1)

void USART_Init(void);
int main(void)
{
	uint8_t data;
	USART_Init();
	DDRB |= (1 << 0);
    while(1)
    {
        while(!(UCSR0A & (1 << RXC0 )));
		data = UDR0;
		if(data == '1')
		{
			PORTB |= 1 << 0;
		}
		if(data == '0')
		{
			PORTB &= ~(1 << 0);
		}
	}
}
void USART_Init(void)
{
	UBRR0H = (BRC >> 8);
	UBRR0L =  BRC;
	
	UCSR0B = (1 << RXEN0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
	
}
