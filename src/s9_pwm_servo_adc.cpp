#include <Arduino.h>

#include <util/delay.h>
#include <lcd_library.h>

uint32_t x = 1000;

const int potPin = 0; // Potentiometer connected to Analog pin A0

unsigned long z = 0;

char toshow[16];

void adc_init()
{
    // Set the reference voltage to AVcc
    ADMUX = (1 << REFS0);

    // Enable the ADC and set the prescaler to 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read(uint8_t channel)
{
    // Select the ADC channel with safety mask
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for the conversion to complete
    while (ADCSRA & (1 << ADSC))
        ;

    // Return the ADC value
    return ADC;
}

void pwm_init()
{
    // Set PD5 (OC1A) as output
    DDRD |= (1 << PD5);

    // Configure Timer1 for Fast PWM, Mode 14 (ICR1 as TOP)
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler = 8

    ICR1 = 2'000;
}

void setup()
{
    adc_init();
    pwm_init();
    lcd_init();

    // OCR1A = 1000;
}

void loop()
{
    uint16_t potValue = adc_read(potPin); // Read potentiometer (0-1023)

    z = ((unsigned long)potValue * 1000) / 1023 + 1000;

    OCR1A = z;

    sprintf(toshow, "Pot: %lu", z);

    lcd_gotoxy(0, 0);
    lcd_clear();
    _delay_ms(100);
    lcd_puts(toshow);

    _delay_ms(1000);
}