/*
 * TImer_setup.c
 *
 * Created: 14-07-2023 15:32:31
 * Author : ramesh
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
 #include <util/atomic.h>

int main(void)
{
	DDRB |= _BV(5); //LED output
	TCCR0B = (1<<CS02)|(1<<CS00); // prescalar 1024 set , 256 step total, 16MHz tick per second.
	sei();	//global interrupt
	TIMSK0 = (1<<TOIE0); // overflow interrupt enable.
	while(1){
		
	}
}

ISR(TIMER0_OVF_vect){
	static int x=0;
	if(x>61){
		x=0;
		PORTB ^= _BV(5);
	}
	x++;
}

