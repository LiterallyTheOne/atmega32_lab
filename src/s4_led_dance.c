#include <mega32.h>
#include <delay.h>

char x;
char k = 0;

interrupt [EXT_INT1] void haha(void)
{     
     x = 1 - x;
}


interrupt [TIM0_COMP] void timer0_comp_isr(void)
{
    k++;
    k%=8;
    if(k==0){
        PORTB += x;
    } 
}


void main(void)
{

PORTA = 0x00;
DDRA = 0x00;

PORTB = 0x00;
DDRB = 0xFF;

PORTC = 0x00;
DDRC = 0x00;

PORTD = 0x00;
DDRD = 0x00;

GICR |= 1 << INT1;
MCUCR |= (1 << ISC11);
MCUCR |= (1 << ISC10);


TIMSK |= (1 << OCIE0);

TCCR0 |= (1 << WGM01);
TCCR0 |= (1 << CS00);
TCCR0 |= (1 << CS02);

OCR0 = 100;

#asm("sei");

x = 1;

while (1)
      {
      /*
        PORTB += x; 
        
        delay_ms(300);
        */
      }
}
