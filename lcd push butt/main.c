#include <avr/io.h> 
#include <util/delay.h> 
#include <stdlib.h> 

// TYPEDEFS
typedef uint8_t byte; // changed the name


// ------------------
//LCD DRIVER ROUTINES
//
// Routines:
// LCD_Init initializes the LCD controller
// LCD_Cmd sends LCD controller command
// LCD_Char sends single ascii character to display
// LCD_Clear clears the LCD display & homes cursor
// LCD_Integer displays an integer value
// LCD_Message displays a string
// PortB is used for data communications with the HD44780-controlled LCD.
// The following defines specify which port pins connect to the controller:
#define ClearBit(x,y) x &= ~_BV(y) // equivalent to cbi(x,y)
#define SetBit(x,y) x |= _BV(y) // equivalent to sbi(x,y)
#define LCD_RS 0 // pin for LCD R/S (eg PB0)
#define LCD_E 1 // pin for LCD enable
#define DAT4 2 // pin for d4
#define DAT5 3 // pin for d5
#define DAT6 4 // pin for d6
#define DAT7 5 // pin for d7
//// The following defines are controller commands
#define CLEARDISPLAY 0x01

void PulseEnableLine ()
{
 SetBit(PORTB,LCD_E); // take LCD enable line high
 _delay_us(40); // wait 40 microseconds
 ClearBit(PORTB,LCD_E); // take LCD enable line low
}
void SendNibble(byte data)
{
 PORTB &= 0xC3; // 1100.0011 = clear 4 data lines
 if (data & _BV(4)) SetBit(PORTB,DAT4);
 if (data & _BV(5)) SetBit(PORTB,DAT5);
 if (data & _BV(6)) SetBit(PORTB,DAT6);
 if (data & _BV(7)) SetBit(PORTB,DAT7);
 PulseEnableLine(); // clock 4 bits into controller
}
void SendByte (byte data)
{
 SendNibble(data); // send upper 4 bits
 SendNibble(data<<4); // send lower 4 bits
 ClearBit(PORTB,5); // turn off boarduino LED
}
void LCD_Cmd (byte cmd)
{
 ClearBit(PORTB,LCD_RS); // R/S line 0 = command data
 SendByte(cmd); // send it
}
void LCD_Char (byte ch)
{
 SetBit(PORTB,LCD_RS); // R/S line 1 = character data
 SendByte(ch); // send it
}
void LCD_Init()
{
 LCD_Cmd(0x33); // initialize controller
 LCD_Cmd(0x32); // set to 4-bit input mode
 LCD_Cmd(0x28); // 2 line, 5x7 matrix
 LCD_Cmd(0x0C); // turn cursor off (0x0E to enable)
 LCD_Cmd(0x06); // cursor direction = right
 LCD_Cmd(0x01); // start with clear display
 _delay_ms(3); // wait for LCD to initialize
}
void LCD_Clear() // clear the LCD display
{
 LCD_Cmd(CLEARDISPLAY);
 _delay_ms(3); // wait for LCD to process command
}

void LCD_Message(char *s) // display string on LCD
{
	for(int i = 0; s[i] != '\0'; ++i){
 //while (*text) // do until /0 character
 LCD_Char(s[i]);
 } // send char & update char pointer
}

void LCD_Integer(int data)
// displays the integer value of DATA at current LCD cursor position
{
 char st[8] = ""; // save enough space for result
 itoa(data,st,10); // 
 LCD_Message(st); // display in on LCD
}

// MAIN PROGRAM
int main(void)
{
// use PortB for LCD interface
 DDRB = 0xFF; // 1111.1111; set PB0-PB7 as outputs	 

 LCD_Init(); // initialize LCD controller

PORTD |= (1 << PD0); // For Integer 0
PORTD |= (1 << PD1); // For Integer 1
PORTD |= (1 << PD2); // For Integer 2
PORTD |= (1 << PD3); // For Integer 3
PORTD |= (1 << PD4); // For Integer 4
PORTD |= (1 << PD5); // For Integer 5
PORTD |= (1 << PD6); // For Integer 6
PORTD |= (1 << PD7); // For Integer 7
PORTC |= (1 << PC0); // For Integer 8
PORTC |= (1 << PC1); // For Integer 9
PORTC |= (1 << PC2); // For Clear 
PORTC |= (1 << PC3); // For Equal 
PORTC |= (1 << PC4); // For Function 
PORTC |= (1 << PC5); // For .

int del = 400;

LCD_Clear();
while (1)
{
	//LCD_Cmd(0XC0);
	//LCD_Clear();
if (bit_is_clear( PIND, PD0))
{
LCD_Integer(0);
_delay_ms(del); 
//LCD_Cmd(0x14);
}

if (bit_is_clear( PIND, PD1))
{
LCD_Integer(1);
_delay_ms(del); 
//LCD_Cmd(0x14);
}

if (bit_is_clear( PIND, PD2))
{
LCD_Integer(2);
_delay_ms(del); 
//LCD_Cmd(0x14);
}

if (bit_is_clear( PIND, PD3))
{
LCD_Integer(3);
_delay_ms(del); 
//LCD_Cmd(0x14);
}

if (bit_is_clear( PIND, PD4))
{
LCD_Integer(4);
_delay_ms(del); 
//LCD_Cmd(0x14);
}

if (bit_is_clear( PIND, PD5))
{
LCD_Integer(5);
_delay_ms(del); 
//LCD_Cmd(0x14);
}

if (bit_is_clear( PIND, PD6))
{
LCD_Integer(6);
_delay_ms(del); 
//LCD_Cmd(0x14);
}

if (bit_is_clear( PIND, PD7))
{
LCD_Integer(7);
_delay_ms(del); 
//LCD_Cmd(0x14);
}

if (bit_is_clear( PINC, PC0))
{
LCD_Integer(8);
_delay_ms(del); 
//LCD_Cmd(0x14);
}

if (bit_is_clear( PINC, PC1))
{
LCD_Integer(9);
_delay_ms(del); 
//LCD_Cmd(0x14);
}
 
if(bit_is_clear(PINC,PC2)){
	LCD_Clear();
}
 
//~ if(bit_is_clear(PINC,PC3)){
	//~ LCD_Clear();
//~ }
 
if(bit_is_clear(PINC,PC4) && bit_is_clear( PIND, PD0)){
	LCD_Message('+');
	_delay_ms(del);	
}

if(bit_is_clear(PINC,PC4) && bit_is_clear( PIND, PD1)){
	LCD_Message('-');	
}

if(bit_is_clear(PINC,PC4) && bit_is_clear( PIND, PD2)){
	LCD_Message('X');	
}

if(bit_is_clear(PINC,PC4) && bit_is_clear( PIND, PD3)){
	LCD_Message('/');	
}
 
if(bit_is_clear(PINC,PC5)){
	LCD_Message('.');
}

}
}
