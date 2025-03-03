#include <Arduino.h>

#define D1 11

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

int want_to_show[D1] = {1, 4, 0, 3, -1, 1, 2, -1, 1, 5, -1};

void write_number(int number, int index)
{
    PORTC = 0xFF & ~(1 << (index + 4));
    if (number >= 0)
    {
        PORTB = numbers[number];
    }
    else
    {
        PORTB = 0x00;
    }
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
    for (int i = 0; i < D1; i++)
    {
        for (int k = 0; k < 100; k++)
        {
            for (int j = 0; j < 4; j++)
            {
                write_number(want_to_show[(i + j) % D1], j);
            }
        }
    }
}
