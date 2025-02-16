#include <Arduino.h>

int numbers[10] = {
    0b00111111, // 0
    0b00110000, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
};

void setup()
{
    DDRB = 0xFF;
    PORTB = 0x00;

    DDRC = 0x10;
    PORTC = 0x00;

    DDRA = 0x01;
    PORTA = 0x00;
}

void loop()
{
    for (int i = 0; i < 10; i++)
    {
        PORTB = numbers[9 - i];
        delay(500);
    }

    PORTA = 0x01;
    delay(500);
    PORTA = 0x00;
}