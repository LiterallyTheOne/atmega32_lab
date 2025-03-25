#include <Arduino.h>

uint16_t adc0_value;

void adc_init()
{
    // Set reference voltage to AVCC
    ADMUX |= (1 << REFS0);

    // Enable ADC
    ADCSRA |= (1 << ADEN);

    // Set prescaler to 128
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
}

uint16_t adc_read(uint8_t channel)
{
    // Set the channel
    ADMUX &= 0xF0;
    ADMUX |= channel;

    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for the conversion to finish
    while (ADCSRA & (1 << ADSC))
        ;

    // Retrun the value
    return ADC;
}

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
    adc_init();
}

void loop()
{
    adc0_value = adc_read(0);

    adc0_value = map(adc0_value, 0, 1023, 1'000, 2'000);

    OCR1A = adc0_value;
    delay(100);
}
