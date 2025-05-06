#include <Arduino.h>
#include <lcd_library.h>

uint16_t adc0_value = 0;
uint16_t adc1_value = 0;

char adc0_str[4];
char adc1_str[4];

void init_adc()
{
    ADMUX |= (1 << REFS0);

    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t read_adc(uint8_t channel)
{
    ADMUX &= 0xE0;
    ADMUX |= channel;

    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC))
        ;

    return ADC;
}

void setup()
{
    init_adc();

    lcd_init();
}

void loop()
{
    adc0_value = read_adc(0);
    adc1_value = read_adc(1);

    sprintf(adc0_str, "%d", adc0_value);
    sprintf(adc1_str, "%d", adc1_value);

    lcd_clear();
    lcd_gotoxy(0, 0);
    lcd_puts(adc0_str);
    lcd_gotoxy(1, 0);
    lcd_puts(adc1_str);

    delay(500);
}
