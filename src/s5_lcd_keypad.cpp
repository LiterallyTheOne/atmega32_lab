#include <Arduino.h>

#include <lcd_library.h>

int key;

char keys[4][4] = {
    {'1', '2', '3', 'U'},
    {'4', '5', '6', 'D'},
    {'7', '8', '9', 'M'},
    {'N', '0', 'S', 'E'},
};

int key_pressed()
{
    for (int i = 0; i < 4; i++)
    {
        PORTA = ~(1 << (i + 4));
        for (int j = 0; j < 4; j++)
        {
            if (!(PINA & (1 << j)))
            {
                return keys[i][j];
            }
        }
    }
    return 0;
}

void setup()
{
    lcd_init();

    DDRA = 0xF0;
}

void loop()
{
    key = key_pressed();
    if (key)
    {
        lcd_putchar(key);
        while (key_pressed() == key)
        {
        }
        _delay_ms(100);
    }
}
