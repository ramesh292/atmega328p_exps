/*
 * Test_project.c
 *
 * Created: 28-06-2023 15:21:06
 * Author : Ramesh Vishnoi
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


#define _BV(bit) (1 << (bit))

int main(void)
{
    /* Replace with your application code */
	DDRB = _BV(5);
    while (1) 
    {
		_delay_ms(1000);	
		PORTB |= _BV(5);
		_delay_ms(1000);
		PORTB &= ~_BV(5);		
    }
}

