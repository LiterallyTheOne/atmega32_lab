#include <Arduino.h>

int numbers[10] = {
    0xC0,
    0xF9,
    0xA4,
    0xB0,
    0x99,
    0x92,
    0x82,
    0xF8,
    0x80,
    0x90};

void setup()
{
    DDRB = 0xFF;

    DDRC = 0xF0;
    PORTC = 0xE0;
}

void loop()
{
    for (int i = 0; i < 10; i++)
    {
        PORTB = numbers[9 - i];
        delay(500);
    }
}