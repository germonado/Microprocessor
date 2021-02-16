#include <avr/io.h>
/* As I saw the atmega128 spec, PortA is responsible for the GPIO PA7 - PA0,
   so the below code should set PortA, DDRA as 1 every port for using the outputs,
   and then every seven jumper cable should be connected with PA7-PA0 to LED7-LED0.
   After that, there will be seven lightening LEDs.
*/
int main(void) {
	DDRA = 0xFF;
	PORTA = 0xFF;
	return 0;
}