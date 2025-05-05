#include "Headers/Macros.h"
#include "Headers/delay_functions.h"
#include "Headers/communications.h"

void rcc_init(void){

	//Clock enable bus RCC USART and GPIO
	RCC_APB1ENR |= (1U << 18);
	RCC_APB2ENR |= (0x3U << 3);

}

void button_enable (void){

	//Limpieza y configuarcin de bits 4:7 para PB1
	GPIOx_CRL(GPIOB_BASE) &= ~(0xFU << 4);
	GPIOx_CRL(GPIOB_BASE) |= (1U << 7);
	//Configuracion de ODR en estado alto
	GPIOx_ODR(GPIOB_BASE) &= ~(1U << 1);
	GPIOx_ODR(GPIOB_BASE) |= (1U << 1);

}

void init_hardware(void){

	rcc_init();
	system_init_72MHz();
	delay_init();
	button_enable();

}
