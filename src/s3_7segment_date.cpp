#include <Arduino.h>

int numbers[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
};

void write_number(int number, int index)
{
    PORTC = ~(1 << (index + 4));
    PORTB = numbers[number];
    delay(2);
}

void setup()
{
    DDRB = 0xFF;
    DDRC = 0xF0;

    PORTB = 0xFF;
    PORTC = 0x00;
}

void loop()
{
    for (int i = 0; i < 200; i++)
    {
        write_number(1, 0);
        write_number(5, 1);
    }

    for (int i = 0; i < 200; i++)
    {
        write_number(1, 0);
        write_number(2, 1);
    }

    for (int i = 0; i < 100; i++)
    {
        write_number(1, 0);
        write_number(4, 1);
        write_number(0, 2);
        write_number(3, 3);
    }
}
