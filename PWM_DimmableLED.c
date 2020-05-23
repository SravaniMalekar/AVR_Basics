/*
 * PWM.c
 *
 * Created: 24-05-2020 02:07:22
 * Author : Sravani Malekar
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define DELAY 1000                      //microseconds
#define LED_PORT PORTB
#define LED_DDR DDRB

void pwm(uint8_t brightness){
	uint8_t i;
	LED_PORT |= 0xFF;                  //turning on the LEDs
	for (i=0;i<255;i++){
		if(i >= brightness){           
			LED_PORT =0;
		}
		_delay_us(DELAY);	
	}
}

int main(void)
{
	
    uint8_t brightness =0;
	uint8_t direction=1;
	LED_DDR |= 0xFF; 
    while (1) 
    {
		if(brightness==0)
		{
			direction =1;
        }
		if(brightness==255){
			direction =-1;
		}
		brightness +=direction;
		pwm(brightness);
		
   }
   return 0;
}
