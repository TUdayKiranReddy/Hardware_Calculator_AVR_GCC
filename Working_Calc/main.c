#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"
#include "Keypad.h"
#include <math.h>

char get_key (void);
char READ_SWITCHES(void);
void Circ_Init(void);
double gen_num();
double gen_dec();
void opcheck();
void opcalc();
void add();
void sub();
void mult();
void divide();
void raise();
void calc_clear();
int dig[50];
int i=0;//count for digits
double ans = 0;
int k = 0;//count for operation
int l = 0;//count for decimal point
int w = 0;//count for negative numbers
double n1,n2;
char key,op,e;
int main(void)
{
Circ_Init(); // Initialize the circuit
LCD_Init(); // initialize LCD controller
while(1)
{
start:
key=get_key();
LCD_Char(key);
dig[i] = atoi(&key);
i = i+1;
switch(key){
case '+' :
opcheck();
break;

case '-' :
if(i==1){
LCD_Cmd(0x10);
LCD_Char('(');
LCD_Char('-');
w=1;
i=0;
}

else
opcheck();

break;

case '*' :
opcheck();
break;

case '/' :
opcheck();
break;

case 'b' :
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
i = i-2;

if(i==1&&l==1)
l=0;

if(i==1&&w==1){
w=0;
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
}
break;

case 'c':
calc_clear();
break;


case '=':
if(w==1){
LCD_Cmd(0x10);
LCD_Char(')');
LCD_Char(key);
}
if(l==0)
n2 = gen_num();

else
n2 = n2 + gen_dec();

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

case '^' :
divide();
break;
}
LCD_Cmd(0xC0);
LCD_Double(ans);
_delay_ms(700);
op = get_key();
if((key!='+')&&(key!='-')&&(key!='*')&&(key!='/')&&(key!='c')&&(key!='^')&&(key!='b')){
calc_clear();
goto start;
}
LCD_Clear();
LCD_Double(ans);
LCD_Char(op);
i = 0;
n1 = ans;
break;

case '.' :
if(k==0){
n1 = gen_num();
i=0;
l=1;
}

else{
n2 = gen_num();
i=0;
l=1;
}
break;


case 's':

LCD_Message("Shift");

e  = get_key();

switch(e){
	

case '1' :
LCD_Clear();
i=0;
LCD_Cmd(0x10);
LCD_Char('s');
LCD_Char('i');
LCD_Char('n');
LCD_Char('(');
while((key!='+')&&(key!='-')&&(key!='*')&&(key!='/')&&(key!='=')&&(key!='^')){
first:
_delay_ms(700);
   key=get_key();
LCD_Char(key);
dig[i] = atoi(&key);
i = i+1;
if(key=='.'){
l = 1;
ans = gen_num();
i = 0;
}
if(key=='b'){
if(i==1){
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Char(' ');
LCD_Char(' ');
LCD_Char(' ');
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
i=0;
goto start;
}
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
i = i-2;

if(i==1&&l==1)
l=0;
if(i==1&&w==1){
w=0;
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
}

if(key == 'c'){
calc_clear();
goto start;
}
}
 }
 
 if(i==1&&key=='-'){
 w=1;
 i=0;
 goto first;
 }
 if(l==0)
 ans = sin(gen_num()*(M_PI/180.000));
 
 if(l==1){
 ans = sin((ans+gen_dec())*(M_PI/180.000));
 l=0;
 }
 
 if(key=='='){
 LCD_Cmd(0x10);
LCD_Char(')');
LCD_Char(key);
 LCD_Cmd(0xC0);
 
 if(k==0){
 LCD_Double(ans);
 k=1;
 i = 0;
 n1 = ans;
 break;
 }
 
 else{
opcalc();
 LCD_Double(ans);
 i = 0;
 n1 = ans;
 break;
 }
 }
 
 if(k==0){
 k=1;
 LCD_Cmd(0x10);
LCD_Char(')');
LCD_Char(key);
 n1 = ans;
 i = 0;
 }
 
 else{
 LCD_Clear();
opcalc();
 LCD_Double(ans);
 LCD_Char(key);
 n1 = ans;
 i = 0;
 }
op = key;
break;

case '2' :
LCD_Clear();
i=0;
LCD_Cmd(0x10);
LCD_Char('c');
LCD_Char('o');
LCD_Char('s');
LCD_Char('(');
while((key!='+')&&(key!='-')&&(key!='*')&&(key!='/')&&(key!='=')&&(key!='^')){
second:
_delay_ms(700);
   key=get_key();
LCD_Char(key);
dig[i] = atoi(&key);
i = i+1;
if(key=='.'){
l = 1;
ans = gen_num();
i = 0;
}
if(key=='b'){
if(i==1){
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Char(' ');
LCD_Char(' ');
LCD_Char(' ');
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
i=0;
goto start;
}
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
i = i-2;

if(i==1&&l==1)
l=0;
if(i==1&&w==1){
w=0;
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
}

_delay_ms(1000);
key = READ_SWITCHES();
if(key == 'c'){
calc_clear();
goto start;
}
}
 }
 if(i==1&&key=='-'){
 w=1;
 i=0;
 goto second;
 }
 if(l==0)
 ans = cos(gen_num()*(M_PI/180.000));
 
 if(l==1){
 ans = cos((ans+gen_dec())*(M_PI/180.000));
 l=0;
 }
 
 if(key=='='){
 LCD_Cmd(0x10);
LCD_Char(')');
LCD_Char(key);
 LCD_Cmd(0xC0);
 
 if(k==0){
 LCD_Double(ans);
 k=1;
 i = 0;
 n1 = ans;
 break;
 }
 
 else{
opcalc();
 LCD_Double(ans);
 i = 0;
 n1 = ans;
 break;
 }
 }
 
 if(k==0){
 k=1;
 LCD_Cmd(0x10);
LCD_Char(')');
LCD_Char(key);
 n1 = ans;
 i = 0;
 }
 
 else{
 LCD_Clear();
opcalc();
 LCD_Double(ans);
 LCD_Char(key);
 n1 = ans;
 i = 0;
 }
op = key;
break;

case '3' :
LCD_Clear();
i=0;
LCD_Cmd(0x10);
LCD_Char('t');
LCD_Char('a');
LCD_Char('n');
LCD_Char('(');
while((key!='+')&&(key!='-')&&(key!='*')&&(key!='/')&&(key!='=')&&(key!='^')){
second1:
_delay_ms(700);
   key=get_key();
LCD_Char(key);
dig[i] = atoi(&key);
i = i+1;
if(key=='.'){
l = 1;
ans = gen_num();
i = 0;
}
if(key=='b'){
if(i==1){
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Char(' ');
LCD_Char(' ');
LCD_Char(' ');
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
i=0;
goto start;
}
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
i = i-2;

if(i==1&&l==1)
l=0;
if(i==1&&w==1){
w=0;
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
}

if(key == 'c'){
calc_clear();
goto start;
}
}
 }
 if(i==1&&key=='-'){
 w=1;
 i=0;
 goto second1;
 }
 if(l==0)
 ans = tan(gen_num()*(M_PI/180.000));
 
 if(l==1){
 ans = tan((ans+gen_dec())*(M_PI/180.000));
 l=0;
 }
 
 if(key=='='){
 LCD_Cmd(0x10);
LCD_Char(')');
LCD_Char(key);
 LCD_Cmd(0xC0);
 
 if(k==0){
 LCD_Double(ans);
 k=1;
 i = 0;
 n1 = ans;
 break;
 }
 
 else{
opcalc();
 LCD_Double(ans);
 i = 0;
 n1 = ans;
 break;
 }
 }
 
 if(k==0){
 k=1;
 LCD_Cmd(0x10);
LCD_Char(')');
LCD_Char(key);
 n1 = ans;
 i = 0;
 }
 
 else{
 LCD_Clear();
opcalc();
 LCD_Double(ans);
 LCD_Char(key);
 n1 = ans;
 i = 0;
 }
op = key;
break;

case '4' :
LCD_Clear();
i=0;
LCD_Cmd(0x10);
LCD_Char('l');
LCD_Char('n');
LCD_Char('(');
while((key!='+')&&(key!='-')&&(key!='*')&&(key!='/')&&(key!='=')&&(key!='^')){
second2:
_delay_ms(700);
   key=get_key();
LCD_Char(key);
dig[i] = atoi(&key);
i = i+1;
if(key=='.'){
l = 1;
ans = gen_num();
i = 0;
}
if(key=='b'){
if(i==1){
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Char(' ');
LCD_Char(' ');
LCD_Char(' ');
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Cmd(0x10);
i=0;
goto start;
}
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
i = i-2;

if(i==1&&l==1)
l=0;
if(i==1&&w==1){
w=0;
LCD_Cmd(0x10);
LCD_Char(' ');
LCD_Cmd(0x10);
}

if(key == 'c'){
calc_clear();
goto start;
}
}
 }
 if(i==1&&key=='-'){
 w=1;
 i=0;
 goto second2;
 }
 if(l==0)
 ans = log(gen_num());
 
 if(l==1){
 ans = log((ans+gen_dec()));
 l=0;
 }
 
 if(key=='='){
 LCD_Cmd(0x10);
LCD_Char(')');
LCD_Char(key);
 LCD_Cmd(0xC0);
 
 if(k==0){
 LCD_Double(ans);
 k=1;
 i = 0;
 n1 = ans;
 break;
 }
 
 else{
opcalc();
 LCD_Double(ans);
 i = 0;
 n1 = ans;
 break;
 }
 }
 
 if(k==0){
 k=1;
 LCD_Cmd(0x10);
LCD_Char(')');
LCD_Char(key);
 n1 = ans;
 i = 0;
 }
 
 else{
 LCD_Clear();
opcalc();
 LCD_Double(ans);
 LCD_Char(key);
 n1 = ans;
 i = 0;
 }
op = key;
break;
}
}
_delay_ms(700);

}

}
 
void Circ_Init(void)
{

// Use PB pins for LCD interface
// Use PD pins for rows
// Use PC pins for coloumns
 
DDRB = 0xFF; // 1111.1111; set PB0-PB7 as outputs
DDRD=0b00000000; // Set PD4-PD7 as i/p
DDRC=0xFF;// Set PC0-PC5 as o/p
PORTD = 0xFF;    //enable all internal pull-ups  
return;

}

char READ_SWITCHES()
{
PORTC = 0b00000000;// Turn all rows to LOW
PORTD = 0b11111000;// Enable Pull-ups

//Check which coloumn has LOW i/p
if (!(PIND & (1<<PD4)))
{
// Change corresponding rows and check the i/p
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD4)))
return '/';
PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD4)))
return '6';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD4)))
return '5';
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD4)))
return '4';
}
else if (!(PIND & (1<<PD5)))
{
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD5)))
return '*';
PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD5)))
return '3';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD5)))
return '2';
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD5)))
return '1';
}

else if (!(PIND & (1<<PD6)))
{
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD6)))
return '-';
PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD6)))
return '+';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD6)))
return '.';
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD6)))
return '0';
}

else if (!(PIND & (1<<PD7)))
{
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD7)))
return '=';
PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD7)))
return 'o';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD7))){
return 's';
}
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD7)))
return 'r';
}

else if (!(PIND & (1<<PD3)))
{
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD3)))
return 'c';
PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD3)))
return '9';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD3))){
return '8';
}
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD3)))
return '7';
}



return 'n';           // Means no key has been pressed
}



char get_key(void)
{
char key = 'n';
while(key=='n')
{
key=READ_SWITCHES();
}
return key;
}

double gen_num(){
int n = 0;
int j;
for(j=0;j<i;j++){
n = n + dig[j]*pow(10,i-2-j);
}

if(w==0)
return (double)n;

else{
w=0;
return -(double)n;
}
}


double gen_dec(){
double n = 0;
int j;
for(j=0;j<(i-1);j++){
n = n + dig[j]*pow(10,-(j+1));
}
l=0;

if(w==0)
return n;

else{
w=0;
return -n;
}
}

void opcheck(){

if(k == 0){
if(w==1){
LCD_Cmd(0x10);
LCD_Char(')');
LCD_Char(key);
}
k = 1;
if(l==0)
n1 = gen_num();

else
n1 = n1 + gen_dec();

op = key;
}

else{
if(l==0)
n2 = gen_num();

else
n2 = n2 + gen_dec();

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
LCD_Clear();
LCD_Double(ans);
LCD_Char(key);
n1 = ans;
op = key;
}
i = 0;
}

void add(){
ans = n1+n2;
}

void sub(){
ans = n1-n2;
}

void mult(){
ans = n1*n2;
}

void divide(){
ans = n1/n2;
}

void calc_clear(){
LCD_Clear();
i = 0;
ans = 0;
k = 0;
l = 0;
w=0;
}

void opcalc(){
switch(op){
 case '+':
 ans = n1 + ans;
 break;
 
 case '-':
 ans = n1 - ans;
 break;
 
 case '*':
 ans = n1 * ans;
 break;
 
 case '/':
 ans = n1 / ans;
 break;
 }
}
char* DoubleToStr(double num){
 int start = num >= 0 ? 0 : 1;
 if (start == 1) num = -num;
 int bdp = 0, adp = 0;
 int n = num;
 do {
        bdp++;
        n /= 10;
    } while (n != 0);
    int temp = 10000;
 n = (int)((num+10e-6 - (int)num)*temp);
 while (n % temp != 0) { temp /= 10; adp++; }
 
 n = (int)num;
 char* str = (char*)malloc((bdp+(start==0 ? 1 : 2))*sizeof(char));
 if (start == 1) str[0] = '-';
 str[bdp+start] = adp == 0 ? '\0' : '.';
 
 for (int i = 0; i < bdp; i++){
        str[start + bdp - (i + 1)] = ((n % 10) + '0');
        n = n / 10;
    }
    if (adp == 0) return str;
    temp = 1;
    for (int i=0; i<adp; i++) temp *= 10;
    n = (int)((num+10e-6 - (int)num)*temp);
   
    for (int i = 0; i < adp; i++){
        str[start + (bdp+1) + adp - (i + 1)] = ((n % 10) + '0');
        n = n / 10;
    }
    str[start+bdp+adp+1] = '\0';
 return str;
}
int isDigit(char c){ return '0' <= c && c <= '9'; }
double readNum(const char* str, int *index){
 int mul = 1;
 if (str[*index] == '-'){ (*index)++; mul = -1; }
 double num = 0;
 while (str[*index] != 0){
  if (!isDigit(str[*index])) break;
  num *= 10.0;
  num += str[(*index)++] - '0';
 }
 if (str[*index] != '.') return mul*num;
 (*index)++; double m10 = 10;
 while (str[*index] != 0){
  if (!isDigit(str[*index])) break;
  num += (str[(*index)++] - '0')/m10; m10 *= 10;
 }
 return mul*num;
}
void LCD_Double(double data)
// displays the Double value of DATA at current LCD cursor position
{
 char* st = DoubleToStr(data); // save enough space for result //
 LCD_Message(st); // display in on LCD
}
