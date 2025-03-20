#include <avr/io.h>
#include <util/delay.h>

#define RS PC3
#define RW PD7
#define EN PD6
#define D4 PB4
#define D5 PB5
#define D6 PB6
#define D7 PB7

#define LCD_WIDTH 16

void lcd_command(unsigned char cmd);

void lcd_putchar(unsigned char data);

void lcd_init();

void lcd_puts(const char *str);

void lcd_gotoxy(unsigned char row, unsigned char col);

void lcd_clear();