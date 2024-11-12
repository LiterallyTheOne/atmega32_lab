#include <mega32.h>
#include <delay.h> 
#include <108lcd.h>

#define ROWS 4
#define COLS 4


#define XCOLS 16
#define YROWS 10


char on_lcd[YROWS][XCOLS];
int x_1 = 2;
int y_1 = 0;


char keypad[ROWS][COLS] = {
    {'1', '2', '3', 'U'},
    {'4', '5', '6', 'D'},
    {'7', '8', '9', 'M'},
    {'N', '0', 'S', 'E'},

};

char row;
char col;
char key;

int i;
int j;

char r1[4] = {'+', '-', '*', '/'};
int rc = 0;

int result = 0;
char operator = '+';
int number = 0;
char result_c[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


int max(int x1, int x2){

    if(x1 > x2){
        return x1;
    }
    else{
        return x2;
    }

}


int min(int x1, int x2){

    if(x1 < x2){
        return x1;
    }
    else{
        return x2;
    }

}


void put_on_lcd()
{
    lcd_clear();
    lcd_gotoxy(0, 0);
    
    if( y_1 == 0){
        i = 0;
    }else{
        i = y_1 -1;
    }
   

  for(; i < y_1 + 1; i++){
    for(j = 0; j < XCOLS; j++){
        if(on_lcd[i][j]){
            lcd_putchar(on_lcd[i][j]);        
        }
          
    }
    lcd_gotoxy(0, 1);
  }

}

void add_to_lcd(char ch){
    on_lcd[y_1][x_1] = ch;
    x_1++;
    
    if(x_1 >= XCOLS){
        x_1 %= XCOLS;
        x_1 += 2;
        y_1++;
        y_1 %= YROWS;
    }

}


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


void process_the_row(){
    operator = '+';
    number = 0;
    
    for(i=0;i<10;i++){
        result_c[i] = 0;
    }

    for(i=2;i<16;i++){
        if((on_lcd[y_1][i] >= '0') && (on_lcd[y_1][i] <= '9')){
            number *=10;
            number += on_lcd[y_1][i] - '0';
        }else if((on_lcd[y_1][i] == '+') || (on_lcd[y_1][i] == '-') || (on_lcd[y_1][i] == '*') || (on_lcd[y_1][i] == '/')){
            if(operator == '+'){
                result += number;
            } else if(operator == '-'){
                result -= number;
            } else if(operator == '*'){
                result *= number;
            } else if(operator == '/'){
                result /= number;
            }
            operator = on_lcd[y_1][i];
            number = 0;
        }else{
            break;
        }
    }
    
    if(operator == '+'){
        result += number;
    } else if(operator == '-'){
        result -= number;
    } else if(operator == '*'){
        result *= number;
    } else if(operator == '/'){
        result /= number;
    }
    
    x_1 = i;
    
    add_to_lcd('=');
    i = 0;
    while(result != 0){
        result_c[i] = '0' + result % 10;
        result /= 10;
        i++;
    }
    
    for(;i>-1;i--){
        add_to_lcd(result_c[i]);
    }


}


void main(void)
{
lcd_init(16);

DDRA = 0xF0;
PORTA = 0xFF;

for(i=0;i<YROWS;i++){
    for(j=0;j<XCOLS;j++){
        on_lcd[i][j] = 0;
    }
}

for(i = 0;i < YROWS; i++){
on_lcd[i][0] = '0' + i;
on_lcd[i][1] = ':';

}

add_to_lcd('1');
add_to_lcd('+');
add_to_lcd('2');
add_to_lcd('=');
add_to_lcd('3');
y_1++;
x_1 = 2;

add_to_lcd('1');
add_to_lcd('2');
add_to_lcd('+');
add_to_lcd('2');
add_to_lcd('4');
add_to_lcd('=');
add_to_lcd('3');
add_to_lcd('6');
y_1++;
x_1 = 2;


 put_on_lcd();

while (1)
      {
      
       key = get_key();
       if(key){
       if((key <='9') && (key >= '0')){ 
            add_to_lcd(key);              
        }
        else if(key == 'U'){
            y_1--;
            x_1 = 2;
            y_1 = max(y_1, 0);
        }else if(key == 'D'){
            y_1++;
            x_1 = 2;
            y_1 = min(y_1, YROWS - 1);
        }else if(key == 'M'){
            x_1 = 2;
            for(j=2;j<XCOLS;j++){
                on_lcd[y_1][j] = 0;
            }
        }else if(key == 'N'){
            add_to_lcd(r1[rc]);
            rc++;
            rc %= 4;
            x_1--;
        }else if(key == 'S'){
         if((on_lcd[y_1][x_1] == '+') || (on_lcd[y_1][x_1] == '-') || (on_lcd[y_1][x_1] == '*') || (on_lcd[y_1][x_1] == '/')){
            x_1++;
            rc = 0;                                                                                                    
         } 
        }else if(key == 'E'){
            process_the_row();
            
        }
        put_on_lcd();
        while(get_key() == key);
        delay_ms(100);
       }
       

      
      }
}
