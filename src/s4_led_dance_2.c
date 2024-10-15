#include <mega32.h>
#include <delay.h>

char s1 = 0;
char x;
char k = 0;
char l1 = 0;

interrupt [EXT_INT1] void haha(void)
{     
     s1 = 1 - s1;
}

interrupt [EXT_INT0] void haha_1(void)
{     
     x = 0;
}


interrupt [TIM0_COMP] void timer0_comp_isr(void)
{
    if(!s1)
    {
        k++;
        k%=8;
        if(k==0){
            PORTB = x;
            x = (x << 1) | (x >> (7));
            l1++;
            if(l1 == 8)
            {
                if(x & (1 << 7)){
                    x = 0;
                
                }
                l1 = 0;
                x = x << 1;
                x |= 1;
           
            }
        } 
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

GICR |= 1 << INT0;
MCUCR |= (1 << ISC01);
MCUCR |= (1 << ISC00);


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
