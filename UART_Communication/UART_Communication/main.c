// /*
//  * UART_Communication.c
//  *
//  * Created: 17-07-2023 11:34:31
//  * Author : ramesh
//  */ 
 #define F_CPU 16000000UL
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>
 #include <stdint.h>
 #define receivedBufferSize 1000
 #define transmitBufferSize 1000
 uint8_t receivedBuffer[receivedBufferSize];
 uint8_t receivedBufferIndex = 0;
 uint8_t flag = 0;
 uint8_t transmitBuffer[transmitBufferSize];
 uint8_t transmitBufferIndex=0;
 uint8_t time=0;
 
 
 void Timer_Init()
 {
 TCCR0B = (1<<CS02)|(1<<CS00); // prescalar 1024 set , 256 step total, 16MHz tick per second.
 TIMSK0 = (1<<TOIE0); // overflow interrupt enable.
 }
 
 void UART_Init()
 {
 	// set baud rate
 	UBRR0H = (103>>8);
 	UBRR0L = 103;
 	
 	//// enable receiver and transmitter
 	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);
 	//// set frame format: 8 data bits, 1 stop bit, no parity
 	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
 }
 //
 void UART_Transmit(){
 	UDR0 = transmitBuffer[transmitBufferIndex++];
 }
 
 
 void DataProcessFunction(){
 	if( 1==flag && transmitBufferIndex < receivedBufferIndex)
	 {	
 		for(int i=transmitBufferIndex;i<receivedBufferIndex;i++)
 		{
 			transmitBuffer[i]=receivedBuffer[i];
 		}
 		
 		flag = 0;
 		UART_Transmit();
 	} 
	else
		{
		flag = 0;
		}
 }
 
 
 int main(void)
 {
	 cli();
     UART_Init();
	 Timer_Init();
	 sei();
     while (1) 
     {
 		DataProcessFunction();
 	}
 }
 
 
 
 ISR(USART_RX_vect)
 {
 	receivedBuffer[receivedBufferIndex++]=UDR0;
 	time=0;
 	
	 if(receivedBufferIndex==receivedBufferSize)
	 {
		 receivedBufferIndex = 0;
	 }
 }
 
 ISR(USART_TX_vect)
 {
 	
 	if (transmitBufferIndex < receivedBufferIndex)
 	{
 		 //Load the next byte from the transmit buffer into the USART data register (UDR0)
 		UDR0 = transmitBuffer[transmitBufferIndex++];
 	}
 	
 	if(transmitBufferIndex==transmitBufferSize)
 	{
 		transmitBufferIndex = 0;
 	}
 	
 }
 
 
 ISR(TIMER0_OVF_vect)
 {
	 if(time>61)
	 {
		 time=0;
		 flag=1;
	 }
	 time++;
 }
 
 
 
 
 
 
 
 
 


// //uint8_t UART_Receive(){
// ////// wait for data to be received
// ////while(!(UCSR0A & (1<<RXC0)));
// ////
// ////// get and return received data from buffer
// //return UDR0;
// //}
