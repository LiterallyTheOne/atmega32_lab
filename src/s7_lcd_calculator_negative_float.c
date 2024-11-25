#include <mega32.h>
#include <108lcd.h>
#include <delay.h>


#define ROWS 4
#define COLS 4

#define XCOLS 16
#define YROWS 2
#define HI 10

char all_data[HI][YROWS][XCOLS];

int x_1 = 2;
int y_1 = 0;
int h_1 = 0;

char keypad[ROWS][COLS] = {
    {'1', '2', '3', 'U'},
    {'4', '5', '6', 'D'},
    {'7', '8', '9', 'M'},
    {'N', '0', 'S', 'E'},

};

char row;
char col;

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

void add_to_all_data(char ch){
    all_data[h_1][y_1][x_1] = ch;
    
    x_1++;
    
    if(x_1 >= XCOLS){
        x_1 = 2;
        y_1++; 
    }
    
    if(y_1 >= YROWS){
        y_1 = 0;
    }

}

void put_all_data_to_lcd(){

    int i;
    int j;
    
    lcd_clear();
    
    for(i = 0; i < YROWS; i++){
        lcd_gotoxy(0, i);
        for(j = 0; j < XCOLS; j++){
            if(all_data[h_1][i][j] == 0){
                  break;
            }
            lcd_putchar(all_data[h_1][i][j]);
            
        }
        if(j != XCOLS){
            break;
        }
    }
    
    x_1 = j;
    y_1 = i;
    

}

float calculate(){
    float number = 0;
    float result = 0;
    int i;
    int j;
    
    char state = '+';
    
    for(i=0; i < YROWS; i++){
        for(j = 0;j < XCOLS; j++){
            if((i==0) && (j < 2)){
                continue;
            }
        
            if((all_data[h_1][i][j] <= '9') && (all_data[h_1][i][j] >= '0')){
                number *= 10;
                number += all_data[h_1][i][j] - '0';
            }else{ 
            
                switch(state){
                    case '+':
                        result += number;
                        break;
                    case '-':
                        result -= number;
                        break;
                    case '*':
                        result *= number;
                        break;
                    case '/':
                        result /= number;
                        break;
                }
                
                number = 0;
                state = all_data[h_1][i][j];
                
            }
        }
    }
    
    return result;


}

void add_float_to_all_data(float s){

    char r[16];
    int i;
    char n1 = 0;
    
    int s1;
    
    s1 = s * 100;
    
    for(i=0; i< 16; i++){
        r[i] = 0;
    }
     
    if(s1 < 0){
        n1 = 1;
        s1 *= -1;
    }
    
    i = 15;
    while(s1 != 0){
        r[i] = (s1 % 10) + '0';
        s1 /= 10;
        i--;
    }
    
    if(n1){
        add_to_all_data('-');
    }
    
    for(;i<16;i++){
        if(r[i]){
            add_to_all_data(r[i]);
        }
        if(i == (16 - 2 -1)){
            add_to_all_data('.');
        }
    
    }

}


void main(void)
{

char key;

int i;
int j;
int k;

float result = 0;



lcd_init(16);

DDRA = 0xF0;
PORTA = 0xFF;

for(k=0;k<HI;k++){

    all_data[k][0][0] = k + '0';
    all_data[k][0][1] = ':';

}
put_all_data_to_lcd();


add_to_all_data('2');
add_to_all_data('2');
add_to_all_data('/');
add_to_all_data('3');
result = calculate();
add_to_all_data('=');
add_float_to_all_data(result);

put_all_data_to_lcd();


while (1)
      {
      key = get_key();
      while(get_key() == key);
      
       if(key){
        
        if(key == 'E'){
            result = calculate();
            add_to_all_data('=');
            add_float_to_all_data(result); 
        }else if(key == 'N'){
            key = 0;
            lcd_gotoxy(x_1, y_1);
            lcd_putchar('N');
            lcd_gotoxy(x_1, y_1);
            
            while(key == 0){
                key = get_key();
            }
            while(get_key() == key);
            
            switch (key) {
                case '1':
                    add_to_all_data('+');
                    break;
                case '2':
                    add_to_all_data('-');
                    break;
                case '3':
                    add_to_all_data('*');
                    break;
                case '4':
                    add_to_all_data('/');
                    break;
                    
                    
            }
            
        } else if (key == 'M') {
        
            for(i = 0; i < YROWS; i++){
                for(j = 2; j < XCOLS; j++){
                    all_data[h_1][i][j] = 0;
                }
            }
            x_1 = 2;
            y_1 = 0;   
        
        } else if(key == 'U') {
            h_1--;
            if(h_1 < 0 ){
                h_1 = 0;
            }
            
            x_1 = 2;
            y_1 = 0;
        
        
        }else if(key == 'D') {
            h_1++;
            if(h_1 >= HI ){
                h_1 = HI -1;
            }
            
            x_1 = 2;
            y_1 = 0;
        
        
        }else{
            add_to_all_data(key);
        }
        
        
        put_all_data_to_lcd();
        
        
        delay_ms(100);
       }
      

      }
}
