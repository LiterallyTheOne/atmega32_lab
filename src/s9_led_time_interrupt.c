#include <mega32.h>
#include <delay.h>

#define COUNT 1000
#define COUNT_2 2000

char ct0 = 0x01;

char speed = 1;

int x = 1;

int counter = 0;
int direction = 0;

char ct2 = 0x08;
int counter_2 = 0;

interrupt [TIM0_COMP] void t1(void){

    if(counter >= (COUNT/speed)){
        if(direction){
            ct0 <<= x;
        }else{
            ct0 >>= x;
        }
      if(ct0 == 0){
        if(direction){
            ct0 = 0x80;
            
        }else{
            ct0 = 1;
        }
        direction = 1 - direction;
      }
      PORTB = ct2 | ct0;
      counter = 0;
    }
    counter++;

}

interrupt [TIM2_COMP] void t2(void){

    if(counter_2 >= (COUNT_2/speed)){
        ct2 <<= x;
        if(ct2 == 0){
                ct2 = 1;
        }
        PORTB = ct2 | ct0;
        counter_2 = 0;
    }
    counter_2++;
    
}

interrupt [EXT_INT0] void int0(void){
  speed++;
  if(speed > 3){
    speed = 1;
  }  
}


interrupt [EXT_INT1] void int1(void){
  x = 1 - x;  
}


void main(void)
{

PORTB = 0x00;
DDRB = 0xFF;

GICR |= 1 << INT0;

GICR |= 1 << INT1;

TIMSK |= (1 << OCIE0);

TCCR0 |= (1 << WGM01);
TCCR0 |= (1 << CS01);

OCR0 = 100;

TIMSK |= (1 << OCIE2);

TCCR2 |= (1 << WGM21);
TCCR2 |= (1 << CS21);

OCR2 = 100;

#asm("sei")

while (1)
      {
      

      }
}
