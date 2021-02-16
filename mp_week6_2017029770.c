#include <avr/io.h>
#include <util/delay.h>

#define KEY_CTRL PORTE
#define R0 0x10
#define FND_C0 0x01
#define FND_C1 0x02

const char Font[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

//I made function that show the LED and Dynamic FND_LED with the value of selected key at the same time
//This suppose that the condition is prepared properly for Dynamic FND

unsigned char key_scan(void){
	unsigned char scan = 0;
	unsigned char key_control = 0;
	unsigned char input_data = 0;
	unsigned char key = 0;

	key_control = R0;

	for(scan=0; scan<4; scan++){
		KEY_CTRL &= 0x0F;
		KEY_CTRL |= key_control;
		_delay_ms(1);
		input_data = PINF & 0x07;

		if(input_data != 0){
			key = (input_data>>1) + 1 + scan*3;
		}

		key_control <<= 1;
	}
	
	return key;
}

int main(void){

	unsigned char led = 0;
	unsigned char key = 0;
	DDRF = 0x00;
	DDRE = 0xFF;
	DDRA = 0xFF;


	unsigned char digit0, digit1, digit2, digit3;

	DDRB = 0xFF;
	DDRG = 0xFF;

	PORTB = 0x00;
	PORTG = 0xFF;


	while(1){

		key = key_scan();

		led = 0x01;

		digit3 = key%10;
		digit2 = (key/10)%10;

		if(key == 0){
			led = 0x00;
		}

		else if(key < 9){
			led = led << (key-1);
		}

		else if(key == 9){
			led = 0x81;
		}

		else if(key == 10){
			led = 0x0F;
		}

		else if(key == 11){
			led = 0xFF;
		}

		else if(key == 12){
			led = 0xF0;
		}

		PORTA = led;

		PORTG |= 0x0F;
		PORTG &= ~FND_C3;
		PORTB = Font[digit0];
		_delay_ms(1);

		PORTG |= 0x0F;
		PORTG &= ~FND_C2;
		PORTB = Font[digit1];

	}
}