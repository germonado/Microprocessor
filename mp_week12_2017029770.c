#include <avr/io.h>
#include <avr/interrupt.h>

#define TRUE 1
#define FALSE 0

volatile unsigned char int t2_100 = 0;

const char Font[17] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
						0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C,
						0x39, 0x5E, 0x79, 0x71, 0x00};

unsigned char digit0 = 0;
unsigned char digit1 = 0;
unsigned char digit2 = 0;
unsigned char digit3 = 0;
/* assume that we control stop_watch with interrup 1 */
int flag = 0;

SIGNAL(SIG_OVERFLOW0){
	TCNT0 = 112;
	t2_100++;
}

SIGNAL(SIG_INTERRUPT1){
	/* flag for stop watch start and stop */
	if(flag == 0) flag = 1;
	else if(flag == 1) flag = 0;
}

void delay(unsigned long x){
	while(x--);
}

void fnd_display(unsigned char digit0, unsigned char digit1,
				unsigned char digit2, unsigned char digit3){
	PORTG |= 0x0F;
	PORTG &= ~FND_C0;
	PORTB = Font[digit0];
	delay(10);

	PORTG |= 0x0F;
	PORTG &= ~FND_C1;
	PORTB = Font[digit1];
	delay(10);

	PORTG |= 0x0F;
	PORTG &= ~FND_C2;
	PORTB = Font[digit2];
	delay(10);

	PORTG |= 0x0F;
	PORTG &= ~FND_C3;
	PORTB = Font[digit3];
	delay(10);
}

int main(void){
	unsigned char ledstate = TRUE;
	unsigned char update = TRUE;
	/* use the last week(mp_week11) setting environment */
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRG = 0xFF;
	PORTG = 0xFF;
	
	TCCR0 = 0x07;
	TCNT0 = 112;
	TIMSK = 0x01;

	EIMSK = 0xFF;

	EICRA = 0xFF;
	EICRB = 0xFF;

	sei();

	int sec = 0;
	int min = 0;
	while(1){
		/* if stop_watch get signal start */
		if(flag == 1){
			/* if stop_watch started and after 1 sec */
			if(t2_100 == 100){
				update = TRUE;
				t2_100 = 0;
			}
			/* calculate time */
			if(update == TRUE){
				update = FALSE;

				if(sec == 59){
					sec = 0;
					min++;
				}
				else if(sec != 59){
					sec++;
				}
				if(min == 60){
					min = 0;
				}
				else if(min != 60){
					min++;
				}
				digit0 = min/10;
				digit1 = min%10;
				digit2 = sec/10;
				digit3 = sec%10;
			}
		}
		/* if flag is stop, t2_100 counter is set 0 */
		else if(flag == 0){
			t2_100 = 0;
		}
		/* display number */
		fnd_display(digit0, digit1, digit2, digit3);
	}

}