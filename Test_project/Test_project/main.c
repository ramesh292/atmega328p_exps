/*
 * gpio_hal.c
 *
 * Created: 30-06-2023 14:12:43
 *  Author: ramesh
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "gpio_hal.h"
#include "fuction_hal.h"
//#define _BV(x) (1<<x)

int main(void)
{
    /* Replace with your application code */
	
	//DDRB |= _BV(4);
	//DDRB |= _BV(5);  //data directing register
	
	//7 segment code
	init_pin(2,e_output);
	init_pin(3,e_output);
	init_pin(4,e_output);
	init_pin(5,e_output);
	init_pin(6,e_output);
	init_pin(7,e_output);
	init_pin(8,e_output);
	init_pin(9,e_output);
	//keypad
	// c1 c2 c3 c4
	// 10 11 12 13 
	init_pin(10,e_output);
	init_pin(11,e_output);
	init_pin(12,e_output);
	init_pin(13,e_output);
	all_high();
	//keypad_display();
	cal_display();



}




    
		
		//PORTB |= _BV(4);
		//PORTB ^= _BV(5);
		
	
		
		
		
		//7 segment code
	
	/*
		_delay_ms(1000);
		set_pin(12,e_high);
		set_pin(13,e_low);
		
		set_pin(2,e_low);
		set_pin(4,e_low);
		set_pin(6,e_low);
		set_pin(8,e_low);
		set_pin(3,e_high);
		set_pin(5,e_high);
		set_pin(7,e_high);
		set_pin(9,e_high);
		
		
		
		_delay_ms(1000);
		
		set_pin(13,e_high);
		set_pin(12,e_low);
		set_pin(3,e_low);
		set_pin(5,e_low);
		set_pin(7,e_low);
		set_pin(9,e_low);
		set_pin(2,e_high);
		set_pin(4,e_high);
		set_pin(6,e_high);
		set_pin(8,e_high);
		
		*/