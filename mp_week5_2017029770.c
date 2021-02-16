#include <avr/io.h>
#include <stdio.h>

int main(void){

	unsigned char input_data_rot_switch;
	DDRD = 0x00;
	DDRB = 0xff;

	while(1){
		
		if(PIND == 0x00) {
			PIND = 0x01;
		}
		else if(PIND < 8){
			PIND = 2 << (PIND-1);
		}
		else{
			PIND = 0x00;
		}
		PORTB = PIND;
	}
}