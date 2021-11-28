/*
 * Using std I/O using atmega328P
 *
 * Created: 11/27/2021 3:03:30 PM
 *  Author: All
 */ 
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#define F_CPU 16000000
#define BAUD 57600 //baud rate
#define UBRR F_CPU/16/BAUD-1 //equation to find the value of UBRR0 register
#define eprinf(s, ...) printf_P(PSTR(s), ##__VA_ARGS__) //use flash memory to store format strings

static int uart_putchar(char c, FILE *stream);
static int uart_getchar(FILE* stream);

FILE uart_stream = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

static int uart_putchar(char c, FILE *stream)
{
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	return 0;
}

static int uart_getchar(FILE* stream)
{
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}

void init_uart()
{
	UCSR0B |= (1<<RXEN0 | 1<<TXEN0); //enable receiver and transmitter
	UBRR0 = UBRR; //set baud rate
	
	stdout = stdin = &uart_stream;
}
 

int main(void)
{
	init_uart();
	
	eprinf("System Booted, built %s on %s\n", __TIME__, __DATE__);
	
	while(1)
	{
		eprinf("Hello there. What is your name?\n");
		
		char *name = "";
		scanf("%s", name);
		
		eprinf("Alright %s, pick a number?\n", name);
	
		int number;

		if(scanf("%d", &number) == 1){
			eprinf("Ok, %s, did you pick %d?\n", name, number);
		}else {
			eprinf("Look %s - I said a number. Try again .\n", name);
		}
	}
}


