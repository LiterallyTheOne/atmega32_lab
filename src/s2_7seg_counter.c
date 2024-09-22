#include <mega32.h>
#include <delay.h>

char numbers[10] =
    {0xC0,
     0xF9,
     0xA4,
     0xB0,
     0x99,
     0x92,
     0x82,
     0xF8,
     0x80,
     0x90};

void main(void)
{
      char ch;

      PORTA = 0x00;
      DDRA = 0x00;

      PORTB = 0x00;
      DDRB = 0xFF;

      PORTC = 0x00;
      DDRC = 0xF1;

      PORTD = 0x00;
      DDRD = 0x00;

      while (1)
      {
            PORTC .0 = 0;
            for (ch = 0; ch < 10; ch++)
            {
                  PORTB = numbers[9 - ch];
                  delay_ms(100);
            }
            PORTC .0 = 1;
            delay_ms(100);
      };
}
