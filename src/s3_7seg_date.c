#include <mega32.h>
#include <delay.h>
 

char numbers[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

void write_number_on_index(int idx, int number){

    PORTC.7 = 1;
    PORTC.6 = 1;
    PORTC.4 = 1;
    PORTC.5 = 1;

    switch(idx){
        case 0:
            PORTC.7 = 0;
            break;
        case 1:
            PORTC.6 = 0;
            break;
        case 2:
            PORTC.5 = 0;
            break;  
        case 3:
            PORTC.4 = 0;
            break;    
    }
    
    if(number < 10 && number > -1){
        PORTB = numbers[number];
    }else{
        PORTB = 0xFF;
    }
    delay_ms(5);

}

void main(void)
{ 
int i;


PORTA=0x00;
DDRA=0x00;
 
PORTB=0x00;
DDRB=0xFF;

PORTC=0x00;
DDRC=0xF0;

PORTD=0x00;
DDRD=0x00;

while (1)
      {
        for(i=0; i < 2000/(5*4); i++){
            write_number_on_index(3, 1);
            write_number_on_index(2, 4);
            write_number_on_index(1, 0);
            write_number_on_index(0, 3);
        }
        
        for(i=0; i < 2000/(5*4); i++){
            write_number_on_index(3, 10);
            write_number_on_index(2, 10);
            write_number_on_index(1, 10);
            write_number_on_index(0, 7);
        }
        
        for(i=0; i < 2000/(5*4); i++){
            write_number_on_index(3, 10);
            write_number_on_index(2, 10);
            write_number_on_index(1, 10);
            write_number_on_index(0, 8);
        }
        
        
      };
}
