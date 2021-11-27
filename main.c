/*
 * Echo every key press using serial com
 *
 * Created: 11/27/2021 12:06:18 PM
 * Author : All
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#define BAUD 57600 //baud rate
#define UBRR F_CPU/16/BAUD-1 //equation to find the value of UBRR0 register


void USART_init()
{
	UCSR0B |= (1<<RXEN0 | 1<<TXEN0); //enable receiver and transmitter
	UBRR0 = UBRR; //set baud rate
}

void write_char(char c)
{
	while(!(UCSR0A & 1<<UDRE0)); //wait until the data buffer is empty
	UDR0 = c;
}

char read_char()
{
	while(!(UCSR0A & 1<<RXC0)); //wait until all data is received
	return UDR0;
}

int main(void)
{
	USART_init();
    while (1) 
    {
		write_char(read_char());
    }
}

