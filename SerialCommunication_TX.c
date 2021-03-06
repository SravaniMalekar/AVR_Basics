#define F_CPU 16000000
#define BAUD  9600
#define BRC   ((F_CPU/16/BAUD)-1)

#include <avr/io.h>
#include <util/delay.h>

void USART_Init(void);
void serialChar(uint8_t c);
void serialString(char *str);

int main(void)
{
	USART_Init();
    while(1)
    {
        serialString("HELLO\n");
    }
}
void USART_Init()
{
	UBRR0L = BRC;
	UBRR0H = (BRC >> 8);
	
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void serialChar(uint8_t c)
{
	while(!(UCSR0A & (1 << UDRE0 )));
	UDR0 = c ;
	
}
void serialString(char *str)
{
	while(*str)
	{
		serialChar(*str++);
	}
	_delay_ms(1000);
}
