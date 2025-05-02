#include "Headers/delay_functions.h"
#include "Headers/communications.h"

void init_hardware(void){

	system_init_72MHz();
	delay_init();
	button_enable();

}
