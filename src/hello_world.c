#include <mega32.h>
#include <delay.h>
#include <stdlib.h>
#include <108lcd.h>

void main(void)
{

  while (1)
  {
    lcd_init(16);
    lcd_putsf("  Hello world   ");
  }
}
