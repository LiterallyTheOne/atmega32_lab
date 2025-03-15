#include <Arduino.h>

uint8_t a = 0;

int x = 1;

void setup()
{
    DDRB = 0xFF;

    DDRD = 0x00;
    PORTD |= (1 << PD2) | (1 << PD3);

    GICR |= 1 << INT0;
    MCUCR |= 1 << ISC00;
    MCUCR |= 1 << ISC01;

    GICR |= 1 << INT1;
    MCUCR |= 1 << ISC10;
    MCUCR |= 1 << ISC11;

    sei();

    PORTD &= ~(1 << PD2) & ~(1 << PD3);
}

ISR(INT1_vect)
{
    a = 0x00;
}

ISR(INT0_vect)
{
    x = 1 - x;
}

void loop()
{
    PORTB = a;
    a += x;
    delay(100);
}
