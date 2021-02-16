#include <avr/io.h>

void my_delay(unsigned long x){
	while(x--);
} 

int main(void){

	//Set as eight outpin
	DDRB = 0xFF;
	PORTB = 0b00000000;

	// Turn on LED0 to LED7 sequentially, and then back to the first
	while(1){

		PORTB = 0b00000001;
		my_delay(100000);

		PORTB = 0b00000010;
		my_delay(100000);
		
		PORTB = 0b00000100;
		my_delay(100000);
		
		PORTB = 0b00001000;
		my_delay(100000);

		PORTB = 0b00010000;
		my_delay(100000);

		PORTB = 0b00100000;
		my_delay(100000);
		
		PORTB = 0b01000000;
		my_delay(100000);
		
		PORTB = 0b10000000;
		my_delay(100000);

	}
	return 0;
}
