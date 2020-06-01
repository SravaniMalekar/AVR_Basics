/*
 * PWM_Timers.c
 *
 * Created: 24-05-2020 02:42:41
 * Author : Sravani Malekar
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "IncFile2.h" //UART Init and print functions

#define LED_DDR1 DDRD  
#define LED_DDR2 DDRB
#define LED1 6
#define LED2 5
#define LED3 3

uint8_t receiveByte(void);
uint8_t getNumber(void);
void INIT_timers(void){
	//TIMER0 A,B
	TCCR0A |=(1 << COM0A1)|(1 << COM0B1);   //Fast PWM Mode for OC0A & OC0B
	TCCR0A |=(1 << WGM01)|(1 << WGM00);     //Fast PWM Waveform generation mode
	TCCR0B |=(1 << CS01);                   //setting prescaler as 8
	TCCR2A |=(1 << COM2A1);                 //Fast PWM Mode for OC2A
	TCCR2A |=(1 << WGM21)|(1 << WGM20);     //Fast PWM Waveform generation mode
	TCCR2B |=(1 << CS21);                   //setting prescaler as 8
	
}

int main(void)
{
    uint8_t brightness;
	INIT_timers();                         //initialising timers
	USART_Init();                          //initialising uart
	serialString("LED DEMO");
	 
	LED_DDR1 |=(1 << LED1);                //setting PORTD OC0A as output
	LED_DDR1 |=(1 << LED2);                //setting PORTD OC0B as output
	LED_DDR2 |=(1 << LED3);                //setting PORTB OC2A as output
	
    while (1) 
    {
		serialString("\r\nEnter (0-255) for duty cycle");
		brightness= getNumber();         //receiving number from serial communication
		
		OCR0A = OCR0B;
		OCR0B = OCR2A;
		OCR2A = brightness;
		
    }
	return 0;
}
uint8_t receiveByte(void){                // function for receiving a byte from serial port
	while(!(UCSR0A & (1 << RXC0 )));
	return UDR0;
}
uint8_t getNumber(void) {
	// Gets a numerical 0-255 from the serial port.
	// Converts from string to number.
	char hundreds = '0';
	char tens = '0';
	char ones = '0';
	char thisChar = '0';
	do {                                                   /* shift over */
		hundreds = tens;
		tens = ones;
		ones = thisChar;
		thisChar = receiveByte();                   /* get a new character */
		                                   /* echo */
		} while (thisChar != '\r');                     /* until type return */
		return (100 * (hundreds - '0') + 10 * (tens - '0') + ones - '0');
	}

	
