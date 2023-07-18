/*
 * function.c
 *
 * Created: 03-07-2023 23:26:11
 *  Author: ramesh
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "fuction_hal.h"
#include "gpio_hal.h"

void all_high()
{
	set_pin(2,e_high);
	set_pin(4,e_high);
	set_pin(6,e_high);
	set_pin(8,e_high);
	set_pin(3,e_high);
	set_pin(5,e_high);
	set_pin(7,e_high);
	
}
void all_low()
{
	set_pin(2,e_low);
	set_pin(4,e_low);
	set_pin(6,e_low);
	set_pin(8,e_low);
	set_pin(3,e_low);
	set_pin(5,e_low);
	set_pin(7,e_low);
	
	
}
void display(int x)
{
	if(x==0)
	{
		// 5 low and all high
		all_high();
		set_pin(5,e_low);
		
	}
	
	if(x==1)
	{
		// 2 and 8 high and all low
		all_low();
		set_pin(2,e_high);
		set_pin(8,e_high);
		
	}
	
	if(x==2)
	{
		// 4 8 low and all high
		all_high();
		set_pin(4,e_low);
		set_pin(8,e_low);
	}
	
	if(x==3)
	{
		// 4 6 low and all high
		all_high();
		set_pin(4,e_low);
		set_pin(6,e_low);
	}
	
	if(x==4)
	{
		// 3 6 7 low and all high
		all_high();
		set_pin(3,e_low);
		set_pin(6,e_low);
		set_pin(7,e_low);
	}
	
	if(x==5)
	{
		// 2 and 6 low and all high
		all_high();
		set_pin(2,e_low);
		set_pin(6,e_low);
	}
	
	if(x==6)
	{
		//2 low and all high
		all_high();
		set_pin(2,e_low);
	}
	
	if(x==7)
	{
		// 2 3 8 high and all low
		all_low();
		set_pin(2,e_high);
		set_pin(3,e_high);
		set_pin(8,e_high);
		
	}
	
	if(x==8)
	{
		// all high
		all_high();
	}
	
	if(x==9)
	{
		// 6 low and all high
		all_high();
		set_pin(6,e_low);
	}
	
}

void displaynoWithoutPoint(int x)
{
	
	int k=x;
	int n=0;
	while(k>0)
	{
		k=k/10;
		n++;
	}
	
	int arr[n];
	
	for(int i=n-1;i>=0;i--){
		arr[i]=x%10;
		x=x-arr[i];
		x=x/10;
	}
	
	for(int i=0;i<n;i++){
		display(arr[i]);
		_delay_ms(800);
	}
	all_low();
	
}

void displayno_1toInfinity()
{
	while(1)
	{
		static int x=0;
		display(x);
		_delay_ms(1500);
		x++;
		//if(x==10) x=0;
		displaynoWithoutPoint(x);
		
		
	}
	
}

void keypad_display(){
	static int x=10;
	while(1){
	set_pin(x,e_high);
	for(int i=0;i<4;i++)
	{
		if (PINC & _BV(i)) {
			 if(i<=2 && x-10<=2) display((x-10)*3+1+i);
			 if(x==13) display(0);
		}
	}
	set_pin(x,e_low);
	x++;
	if(x==14) x=10;
	}
}

void cal_display(){
	static int x=10;
	all_low();
	int presentvalue=0;
	int lastvalue=1; // 1 and -1 + and -
	int sign=1;// * / 1 0
	int ans=0;
	while(1){
		set_pin(x,e_high);
		for(int i=0;i<4;i++)
		{
			if (PINC & _BV(i)) {
				if(i<=2 && x-10<=2){
					int k=(x-10)*3+1+i;
					presentvalue=presentvalue*10+k;
				}
				if(i==3){
					if(x==12||x==11){
						
						if(sign == 1) lastvalue*=presentvalue;
						else lastvalue /=presentvalue;
						if(x==12) sign=0;
						else sign=1;
						presentvalue=0;
						
					}else{
							if(sign == 1) lastvalue*=presentvalue;
							else lastvalue /= presentvalue;
							ans+=lastvalue;
							presentvalue=0;
							if(x == 10) lastvalue=-1;
							else lastvalue = 1;
							sign=1;
					}
					
				}
				if(x==13){
					if(i==1){
						presentvalue*=10;
					}
					if(i==2){
						if(sign == 1) lastvalue*=presentvalue;
						else lastvalue /= presentvalue;
						ans+=lastvalue;
						displaynoWithoutPoint(ans);
						presentvalue=0;
						lastvalue=1;
						sign=1;
						ans=0;
					}
				}
				_delay_ms(500);
			}
		}
		set_pin(x,e_low);
		x++;
		if(x==14) x=10;
	}
}



