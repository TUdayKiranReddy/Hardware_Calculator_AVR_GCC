double gen_num(int i);
double gen_dec(int i);
void opcheck(int i);


double gen_num(int i){
int n = 0;
for(int j=0;j<i;j++){
n = n + dig[j]*pow(10,i-2-j);
}
return (double)n;
}

double gen_dec(int i){
double n = 0;
int j;
for(j=0;j<(i-1);j++){
n = n + dig[j]*pow(10,-(j+1));
}
l=0;
return n;
}

void opcheck(int i){
int k = 0;
int l = 0;
char key,op;
if(k == 0){
k = 1;
if(l==0)
n1 = gen_num(i);

else
n1 = n1 + gen_dec(i);

op = key;
}

else{
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
LCD_Clear();
LCD_DoubleToStr(ans);
LCD_Char(key);
n1 = ans;
op = key;
}
i = 0;
}

