/*
 * EEPROM.c
 *
 * Created: 19-07-2023 16:20:23
 * Author : ramesh
 */ 

#include <avr/io.h>

void UART_Init()
{
	// set baud rate
	UBRR0H = (103>>8);
	UBRR0L = 103;
	
	//// enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	//// set frame format: 8 data bits, 1 stop bit, no parity
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

uint8_t EEPROM_Read(uint8_t address)
{
	while(EECR & (1<<EEPE)); // wait for completion of previous write.
	
	EEAR = address; // set up address register
	
	EECR |= (1<<EERE); // start eeprom read by writing eere. 
	
	return EEDR;// return data from data register.
}

void EEPROM_Write(uint8_t address,uint8_t data)
{
	while(EECR & (1<<EEPE)); //wait for completion of previous write.
	
	EEAR = address; // address 
	EEDR = data; // data to be write
	
	EECR |= (1<<EEMPE);
	EECR |= (1<<EEPE);// start EEPROM write by setting EEPE.
	
	
}

 void UART_Transmit(uint8_t data)
 {
	 while(!(UCSR0A & (1<<UDRE0)));
	 UDR0 = data;
 }
 
 uint8_t UART_Receive()
 {
 // wait for data to be received
 while(!(UCSR0A & (1<<RXC0)));
 
 // get and return received data from buffer
 return UDR0;
 }
 
 void EEPROM_function(){
	 uint8_t data;
	 data = UART_Receive();
	 uint8_t address = 0x000;
	 EEPROM_Write(address,data);
	 UART_Transmit(EEPROM_Read(address));
 }

int main(void)
{
	UART_Init();
	EEARH |=(1<<EEAR8);
	EEARL |= (1<<EEAR0);
	// EEDR - DATA REGISTER
	
	
    /* Replace with your application code */
    while (1) 
    {
		EEPROM_function();
    }
}

