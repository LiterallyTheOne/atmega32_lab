#include <Arduino.h>

#define COUNTER_1 500
#define COUNTER_2 100

int ck1 = 0;
int ck2 = 0;

bool x = 1;
bool direction = 0;

uint8_t a = 0;
uint8_t b = 0;

int speed = 1;

ISR(TIMER0_COMP_vect)
{
    ck1++;
    if (ck1 >= (COUNTER_1 / speed))
    {
        ck1 = 0;

        a = direction ? a << x : a >> x;

        if (a == 0)
        {
            a = direction ? 0x80 : 0x01;
            direction = 1 - direction;
        }

        PORTB = a | b;
    }
}

ISR(TIMER2_COMP_vect)
{
    ck2++;
    if (ck2 >= (COUNTER_2 / speed))
    {
        ck2 = 0;

        b <<= x;

        if (b == 0)
        {
            b = 0x01;
        }

        PORTB = a | b;
    }
}

ISR(INT1_vect)
{
    x = 1 - x;
}

ISR(INT0_vect)
{
    speed *= 2;
    if (speed > 7)
    {
        speed = 1;
    }
}

void setup()
{
    DDRB = 0xFF;
    PORTB = 0x00;

    // INT0
    GICR |= (1 << INT0);
    MCUCR |= (1 << ISC00) | (1 << ISC01);

    // INT1
    GICR |= (1 << INT1);
    MCUCR |= (1 << ISC10) | (1 << ISC11);

    // TIMER0
    TIMSK |= (1 << OCIE0);
    TCCR0 |= (1 << WGM01);
    TCCR0 |= (1 << CS01);
    OCR0 = 100;

    // TIMER2
    TIMSK |= (1 << OCIE2);
    TCCR2 |= (1 << WGM21);
    TCCR2 |= (1 << CS21);
    OCR2 = 100;

    PORTD |= (1 << PD2) | (1 << PD3);

    sei();

    PORTD &= ~(1 << PD2) & ~(1 << PD3);
}

void loop()
{
}
