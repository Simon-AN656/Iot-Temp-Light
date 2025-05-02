#include "Headers/Macros.h"
#include "Headers/delay_functions.h"
#include "Headers/communications.h"

void rcc_init(void){

	//Clock enable bus RCC USART and GPIO
	RCC_APB1ENR |= (1U << 18);
	RCC_APB2ENR |= (0x3U << 3);

}

void init_hardware(void){

	rcc_init();
	system_init_72MHz();
	delay_init();
	button_enable();

}
