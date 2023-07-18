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




static uint8_t pin_lookup[][100]=
{
	//no,port,ddrb,pin,mode,state
	{
		0, 4, _BV(0), 0, 0, 0 
	},
	{
		1, 4, _BV(1), 1, 0, 0
	},
	{
		2, 4, _BV(2), 2, 0, 0
	},
	{
		3, 4, _BV(3), 3, 0, 0
	},
	{
		4, 4, _BV(4), 4, 0, 0
	},
	{
		5, 4, _BV(5), 5, 0, 0
	},
	{
		6, 4, _BV(6), 6, 0, 0
	},
	{
		7, 4, _BV(7), 7, 0, 0
	},
	{
		8, 2, _BV(0), 8, 0, 0
	},
	{
		9, 2, _BV(1), 9, 0, 0
	},
	{
		10, 2, _BV(2), 10, 0, 0
	},
	{
		11, 2, _BV(3), 11, 0, 0
	},
	{
		12, 2, _BV(4), 12, 0, 0
	},
	{
		13, 2, _BV(5), 13, 0, 0
	},
	{
		14, 3, _BV(0), 14, 0, 0
	},
	{
		15, 3, _BV(1), 15, 0, 0
	},
	{
		16, 3, _BV(2), 16, 0, 0
	},
	{
		17, 3, _BV(3), 17, 0, 0
	},
};


void init_pin(uint8_t pin, pin_mode_t mode)
{
	//find DDRx, set mode
	int n = sizeof(pin_lookup)/sizeof(pin_lookup[0]);
	for(int i=0;i<n;i++)
	{
		if(pin_lookup[i][3]==pin)
		{
			if(mode == e_input && pin_lookup[i][4]!=0){
				if(pin_lookup[i][1]==2) DDRB ^=pin_lookup[i][2];
				if(pin_lookup[i][1]==3) DDRC ^=pin_lookup[i][2];
				if(pin_lookup[i][1]==4) DDRD ^=pin_lookup[i][2];
				//DDRB ^= pin_lookup[i][2];
				pin_lookup[i][4]=0;
			} 
			if(mode== e_output && pin_lookup[i][4]!=1)
			{
				if(pin_lookup[i][1]==2) DDRB |=pin_lookup[i][2];
				if(pin_lookup[i][1]==3) DDRC |=pin_lookup[i][2];
				if(pin_lookup[i][1]==4) DDRD |=pin_lookup[i][2];
				//DDRB |= pin_lookup[i][2];
				pin_lookup[i][4]=1;
			}
			return;	 
		}
	}
}

void set_pin(uint8_t pin, pin_state_t state)
{
	//find PORTx, set state
	int n = sizeof(pin_lookup)/sizeof(pin_lookup[0]);
	for(int i=0;i<n;i++)
	{
		if(pin_lookup[i][3]==pin)
		{
			if(state == e_low && pin_lookup[i][5]!=0){
				if(pin_lookup[i][1]==2) PORTB ^=pin_lookup[i][2];
				if(pin_lookup[i][1]==3) PORTC ^=pin_lookup[i][2];
				if(pin_lookup[i][1]==4) PORTD ^=pin_lookup[i][2];
				//pin_lookup[i][1] ^= pin_lookup[i][2];
				pin_lookup[i][5]=0;
			}
			if(state == e_high && pin_lookup[i][5]!=1)
			{
				if(pin_lookup[i][1]==2) PORTB |=pin_lookup[i][2];
				if(pin_lookup[i][1]==3) PORTC |=pin_lookup[i][2];
				if(pin_lookup[i][1]==4) PORTD |=pin_lookup[i][2];
				//pin_lookup[i][1] |= pin_lookup[i][2];
				pin_lookup[i][5]=1;
			}
			return;
		}
	}
}

pin_state_t get_pin(uint8_t pin)
{
	//find PINx, return state
	int n = sizeof(pin_lookup)/sizeof(pin_lookup[0]);
	for(int i=0;i<n;i++)
	{
		
		if(pin_lookup[i][3]==pin)
		{
			if(pin_lookup[i][1]==2) {
				int y=pin_lookup[i][2];
				if(PORTB & y) return e_high;
				else return e_low;
			}
			if(pin_lookup[i][1]==3) {
				int y=pin_lookup[i][2];
				if(PORTC & y) return e_high;
				else return e_low;
			}
			if(pin_lookup[i][1]==4) {
				int y=pin_lookup[i][2];
				if(PORTD & y) return e_high;
				else return e_low;
			}
		}
	}
	
	return e_low;
}