#include <Arduino.h>

void pwm_init()
{
    DDRD |= (1 << PD4);
    DDRD |= (1 << PD5);

    TCCR1A = 0;
    TCCR1B = 0;

    TCCR1A |= (1 << COM1A1);
    TCCR1A |= (1 << COM1B1);

    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << WGM13);

    TCCR1B |= (1 << CS11);

    ICR1 = 19'999;
}

void setup()
{
    pwm_init();
}

void loop()
{
    OCR1A = 1'000;
    OCR1B = 2'000;
    delay(1000);

    OCR1A = 1'500;
    OCR1B = 1'500;
    delay(1000);

    OCR1A = 2'000;
    OCR1B = 1'000;
    delay(1000);
}
