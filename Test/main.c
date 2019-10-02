#include <avr/io.h>
#include <util/delay.h>

int main( void)
{
PORTD |= (1 << PD2); // initializes the pull-up resistor on AVR pin PD2
DDRB    |= ((1 << DDB5)); //Data Direction Register B: writing a 1 to the bit enables output

while (1)
{
if (bit_is_clear( PIND, PD2))
{
PORTB = 0b00100000;
}
else {
PORTB = 0b00000000;
}
}
return (0);
}
