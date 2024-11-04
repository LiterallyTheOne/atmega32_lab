#include <mega32.h>
#include <delay.h> 
#include <stdlib.h> 
#include <108lcd.h>

#define ROWS 4
#define COLS 4

char keypad[ROWS][COLS] = {
    {'1', '2', '3', 'U'},
    {'4', '5', '6', 'D'},
    {'7', '8', '9', 'M'},
    {'N', '0', 'S', 'E'},

};

char row;
char col;
char key;


char get_key()
{
  
  for(row=0; row < 4; row++){
    PORTA = ~(1 << row + 4);
    
    for(col=0; col < COLS; col++){
        if(!(PINA & (1<< (col)))){ 
            delay_ms(20);
             if(!(PINA & (1<< (col)))){
                return keypad[row][col];
             }
        }
    }
    
  
  }
  
  return 0;
   
}

char get_key_1()
{

    PORTA.4 = 0;
    if(!PINA.0){
        return '1';
    }else{
        return 0;
    }

}

char get_key_row_1()
{

    PORTA.4 = 0;
    
    for(col=0; col< COLS; col++){ 
    
        if(!(PINA & (1<<col))){
            return keypad[0][col];
        }
    
    }
    

    return 0;


}


void main(void)
{
lcd_init(16);

DDRA = 0xF0;
PORTA = 0xFF;

while (1)
      {
      
       key = get_key();
       if(key){
        lcd_gotoxy(0, 0); 
        lcd_putchar(key);
        while(get_key() == key);
        delay_ms(100);
       }
       
       

      
      }
}
