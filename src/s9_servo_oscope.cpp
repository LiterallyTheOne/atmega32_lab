#include <Arduino.h>

void pwm_init()
{
    // Set PD5 as output
    DDRD |= (1 << PD5);

    // Make sure that there is no setup other than the one we are going to put
    TCCR1A = 0;
    TCCR1B = 0;

    // non-inverting mode
    TCCR1A |= (1 << COM1A1);

    // Fast PWM mode
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13);

    // Set prescaler to 8
    TCCR1B |= (1 << CS11);

    // Set the frequency to 50Hz
    ICR1 = 19'999;
}

void setup()
{
    pwm_init();
}

void loop()
{
    OCR1A = 1'000;
    delay(1000);

    OCR1A = 1'500;
    delay(1000);

    OCR1A = 2'000;
    delay(1000);
}
