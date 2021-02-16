#include <avr/io.h>

#define FND_C0 0x01
#define FND_C1 0x02
#define FND_C2 0x04
#define FND_C3 0x08

const char Font[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int main(void){

	unsigned char digit0, digit1, digit2, digit3;

	DDRB = 0xFF;
	DDRG = 0xFF;

	PORTB = 0x00;
	PORTG = 0xFF;

	int count = 0;
	
	//Counting 0 to 999
	for(count = 0; count <= 999; count++){

		//Calculate 4 digit numbers
		digit3 = count%10;
		digit2 = (count/10)%10;
		digit1 = (count/100)%10;
		digit0 = count/1000;

		int temp_time_count = 25;

		//For 1 second delay, delay 100 repeat 25 times.
		while(temp_time_count--){
			PORTG |= 0x0F;
			PORTG &= ~FND_C3;
			PORTB = Font[digit0];
			delay(100);

			PORTG |= 0x0F;
			PORTG &= ~FND_C2;
			PORTB = Font[digit1];
			delay(100);

			PORTG |= 0x0F;
			PORTG &= ~FND_C1;
			PORTB = Font[digit2];
			delay(100);

			PORTG |= 0x0F;
			PORTG &= ~FND_C0;
			PORTB = Font[digit3];
			delay(100);

		}
	}
	return 0;
}
