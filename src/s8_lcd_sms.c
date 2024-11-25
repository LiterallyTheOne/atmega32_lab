#include <mega32.h>
#include <108lcd.h>
#include <delay.h>

#define ROWS 4
#define COLS 4
#define OPTIONS 5

#define LCDROWS 2
#define LCDCOLS 16

#define HOW_MANY_TIMES 50000


int lcd_x = 0;
int lcd_y = 0;

char keypad[ROWS][COLS][OPTIONS] = {
    {
        {'1',  0,  0,  0,  0},
        {'2',  'a',  'b',  'c',  0},
        {'3',  'd',  'e',  'f',  0},
        {'U',  0,  0,  0,  0}
    },
    {
        {'4',  'g',  'h',  'i',  0},
        {'5',  'j',  'k',  'l',  0},
        {'6',  'm',  'n',  'o',  0},
        {'D',  0,  0,  0,  0}
    },
    {
        {'7',  'p',  'q',  'r',  's'},
        {'8',  't',  'u',  'v',  0},
        {'9',  'w',  'x',  'y',  'z'},
        {'M',  0,  0,  0,  0}
    },
    {
        {'N',  0,  0,  0,  0},
        {'0',  0,  0,  0,  0},
        {'S',  0,  0,  0,  0},
        {'E',  0,  0,  0,  0}
    }
};

char all_data[LCDROWS][LCDCOLS];


void add_to_all_data(char c){
    if(c==0){
        return;
    }
    all_data[lcd_y][lcd_x] = c;
    lcd_x++;
    
    if(lcd_x >= LCDCOLS){
        lcd_x = 0;
        lcd_y++;
    }
    
    if(lcd_y >= LCDROWS){
        lcd_y = 0;
    }

}


void show_all_data(){
    int i;
    int j;
    
    

    for(i = 0; i < LCDROWS; i++){
        lcd_gotoxy(0, i);
        for(j = 0; j< LCDCOLS; j++){
            if(all_data[i][j]){
                lcd_putchar(all_data[i][j]);
            }
        
        }
    
    }


}


int get_key(char *s_keys, int *s_size)
{
    char row;
    char col;
    int i;
  
  for(row=0; row < 4; row++){
    PORTA = ~(1 << row + 4);
    
    for(col=0; col < COLS; col++){
        if(!(PINA & (1<< (col)))){ 
            delay_ms(20);
             if(!(PINA & (1<< (col)))){
                for(i=0; i< OPTIONS; i++){
                    if(!keypad[row][col][i]){
                        break;
                    }
                    s_keys[i] = keypad[row][col][i];
                }
                *s_size = i;
                
                return 1;
             }
        }
    }
  }
  
  return 0;
   
}


void main(void)
{

    char s_keys[OPTIONS];
    int s_size;
    int s_key_counter =0;
    
    char prev_keys[OPTIONS];
    int prev_size;

    int response;
    
    unsigned long r_counter = 0;
    
    int i;

    lcd_init(16);

    PORTA = 0xFF;
    DDRA = 0xF0;


    while (1)
    {
        response = get_key(s_keys, &s_size);
        r_counter++;
        
        if(r_counter >= HOW_MANY_TIMES){
        
            r_counter %= HOW_MANY_TIMES;
            for(i=0;i<OPTIONS;i++){
                prev_keys[i] = 0;
            }
            prev_size = 0;
        
        }
        
        if(response){
            while(1){
                response = get_key((void *)0, (void *)0);
                if(!response){
                    break;
                }
            }
            
            if(prev_keys[0] == s_keys[0]){
                s_key_counter++;
                s_key_counter %= s_size;
                lcd_x--;
            }else{
                s_key_counter = 0;
            }
            
            
            add_to_all_data('s');
            
            show_all_data();
            lcd_gotoxy(1,1);
            for(i=0;i<s_size;i++){
                lcd_putchar(s_keys[i]);
            }
            delay_ms(1000000000);
      
            delay_ms(100);
            
            for(i=0; i < s_size; i++){
                prev_keys[i] = s_keys[i];
            }
            
            prev_size = s_size;
            
        }
      
      
    }
}
