#include <Arduino.h>

#define COUNTER1 2000
#define COUNTER2 3000

int k = 0;

int c1 = 0;
int c2 = 0;

int speed1 = 1;
int speed2 = 1;

ISR(TIMER0_COMP_vect)
{
    if (c1 >= (COUNTER1 / speed1))
    {
        PORTB <<= k;
        if (PORTB == 0x00)
        {
            PORTB = 0x01;
        }
        c1 = 0;
    }
    c1++;
}

ISR(TIMER2_COMP_vect)
{
    if (c2 >= (COUNTER2 / speed2))
    {
        PORTA <<= k;
        if (PORTA == 0x00)
        {
            PORTA = 0x01;
        }
        c2 = 0;
    }
    c2++;
}

ISR(INT0_vect)
{
    k = 1 - k;
}

ISR(INT1_vect)
{
    speed1++;
    if (speed1 > 3)
    {
        speed1 = 1;
    }

    speed2++;
    if (speed2 > 3)
    {
        speed2 = 1;
    }
}

void setup()
{

    DDRA = 0xFF;
    PORTA = 0x01;

    DDRB = 0xFF;
    PORTB = 0x01;

    GICR |= (1 << INT0);
    MCUCR |= (1 << ISC00);
    MCUCR |= (1 << ISC01);

    GICR |= (1 << INT1);
    MCUCR |= (1 << ISC10);
    MCUCR |= (1 << ISC11);

    TIMSK |= (1 << OCIE0);
    TCCR0 = (1 << WGM01);
    TCCR0 |= (1 << CS01);
    OCR0 = 100;

    TIMSK |= (1 << OCIE2);
    TCCR2 = (1 << WGM21);
    TCCR2 |= (1 << CS21);
    OCR2 = 100;

    sei();
}

void loop()
{
}
