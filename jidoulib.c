
#include <avr/io.h>

void usartInit()
{
	UBRR0L = 27;
	UBRR0H = 0;
	UCSR0C = (1 << UCSZ01) + (1 << UCSZ00);
	UCSR0B = (1 << RXEN0) + (1 << TXEN0);
}

void usartPut(uint8_t data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

void adConversionInit()
{
	ADMUX = 0b01100000;
	ADCSRA = 0b10000111;
	ADCSRB = 0;
}

static void adConversionSetPin(uint8_t pin)
{
	uint8_t tmp = ADMUX;
	tmp &= 0xF0;
	tmp |= pin;
	ADMUX = tmp;
}

uint8_t adConversionGet(uint8_t pin)
{
	adConversionSetPin(pin);
	
	ADCSRA |= (1 << ADIF) + (1 << ADSC);
	
	while (ADCSRA & (1 << ADIF));
	
	return ADCH;
}




