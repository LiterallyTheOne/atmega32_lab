#include <Arduino.h>

#include <lcd_library.h>

int key;

char keys[4][4] = {
    {'1', '2', '3', 'U'},
    {'4', '5', '6', 'D'},
    {'7', '8', '9', 'M'},
    {'N', '0', 'S', 'E'},
};

char key_pressed()
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

char key_pressed_one()
{
    PORTA = ~(1 << PA4);
    if (!(PINA & (1 << PA0)))
    {
        return '1';
    }
    return 0;
}

char key_pressed_one_row()
{
    PORTA = ~(1 << PA4);
    for (int i = 0; i < 4; i++)
    {
        if (!(PINA & (1 << i)))
        {
            return keys[0][i];
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
