#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LCD.h"
#include "keypad.h"
#include "calculator.h"
#include "stack.h"




int dig[50];
int num[20];
int i=0;
double ans = 0;


double n1,n2;
char key,op;

int main(void)
{
Circ_Init(); // Initialize the circuit
LCD_Init(); // initialize LCD controller
while(1)
{
key=get_key();
LCD_Char(key);
dig[i] = atoi(&key);
i = i+1;
switch(key){
case '+' :
opcheck(i);
break;

case '-' :
if(i==1){
	

}

else
opcheck(i);

break;

case '*' :
opcheck(i);
break;

case '/' :
opcheck(i);
break;

case 'c' :
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
i = i-2;
_delay_ms(1000);
key = READ_SWITCHES();
if(key == 'c'){
LCD_Clear();
i = 0;
ans = 0;
k = 0;
break;
}
break;

case '=':
if(l==0)
n2 = gen_num(i);

else
n2 = n2 + gen_dec(i);

switch(op){
case '+' :
add();
break;

case '-' :
sub();
break;

case '*' :
mult();
break;

case '/' :
divide();
break;
}
LCD_Cmd(0xC0);
LCD_Double(ans);
_delay_ms(700);
op = get_key(i);
LCD_Clear();
LCD_Double(ans);
LCD_Char(op);
i = 0;
n1 = ans;
break;

case '.' :
if(k==0){
n1 = gen_num(i);
i=0;
l=1;
}

else{
n2 = gen_num(i);
i=0;
l=1;
}
     

}
_delay_ms(700);

}

}
 


