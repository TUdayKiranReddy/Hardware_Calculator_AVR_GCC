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
LCD_Char(' ');
LCD_Char(' ');
LCD_Char(' ');
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

default:
LCD_Message("Removing Shift");
_delay_ms(1000);
LCD_Clear();
break;

}
}
_delay_ms(700);

}

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

case '^' :
raise();
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

void raise(){
ans = pow(n1,n2);
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
 
 case '^':
 ans = pow(n1,ans);
 break;
 }
}
