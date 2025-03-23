#include <Arduino.h>

void setup()
{
    DDRB = 0xFF;
    PORTB = 0x01;
}

void loop()
{
    PORTB = 0x00;
    delay(500);
    PORTB = 0x01;
    delay(500);
}
