#include "lcd_library.h"

unsigned char cursor_pos = 0; // Track cursor position

void lcd_command(unsigned char cmd)
{
    PORTB = (PORTB & 0x0F) | (cmd & 0xF0); // Send higher nibble
    PORTC &= ~(1 << RS);                   // RS = 0 for command
    PORTD &= ~(1 << RW);                   // RW = 0 for write
    PORTD |= (1 << EN);                    // EN = 1
    _delay_us(1);
    PORTD &= ~(1 << EN); // EN = 0

    _delay_us(200);

    PORTB = (PORTB & 0x0F) | ((cmd << 4) & 0xF0); // Send lower nibble
    PORTD |= (1 << EN);
    _delay_us(1);
    PORTD &= ~(1 << EN);

    _delay_ms(2);
}

void lcd_putchar(unsigned char data)
{
    if (cursor_pos == LCD_WIDTH)
    {
        lcd_gotoxy(1, 0);
        cursor_pos = LCD_WIDTH + 1;
    }
    else if (cursor_pos == (LCD_WIDTH * 2))
    {
        lcd_gotoxy(0, 0);
        cursor_pos = 0;
    }

    PORTB = (PORTB & 0x0F) | (data & 0xF0); // Send higher nibble
    PORTC |= (1 << RS);                     // RS = 1 for data
    PORTD &= ~(1 << RW);                    // RW = 0 for write
    PORTD |= (1 << EN);                     // EN = 1
    _delay_us(1);
    PORTD &= ~(1 << EN); // EN = 0

    _delay_us(200);

    PORTB = (PORTB & 0x0F) | ((data << 4) & 0xF0); // Send lower nibble
    PORTD |= (1 << EN);
    _delay_us(1);
    PORTD &= ~(1 << EN);

    _delay_ms(2);
    cursor_pos++;
}

void lcd_init()
{
    DDRB |= (1 << D4) | (1 << D5) | (1 << D6) | (1 << D7); // Data pins as output
    DDRC |= (1 << RS);                                     // RS as output
    DDRD |= (1 << RW) | (1 << EN);                         // RW and EN as output

    _delay_ms(15); // Wait for LCD to power up

    lcd_command(0x02); // Initialize in 4-bit mode
    lcd_command(0x28); // 2-line, 5x7 matrix
    lcd_command(0x0C); // Display on, cursor off
    lcd_command(0x06); // Auto increment cursor
    lcd_command(0x01); // Clear display
    _delay_ms(2);
}

void lcd_puts(const char *str)
{
    while (*str)
    {
        lcd_putchar(*str);
        str++;
    }
}

void lcd_gotoxy(unsigned char row, unsigned char col)
{
    unsigned char pos;
    if (row == 0)
        pos = 0x80 + col;
    else
        pos = 0xC0 + col;
    lcd_command(pos);
    cursor_pos = col * (row + 1);
}

void lcd_clear()
{
    lcd_command(0x01); // Clear display command
    _delay_ms(2);
    cursor_pos = 0;
}