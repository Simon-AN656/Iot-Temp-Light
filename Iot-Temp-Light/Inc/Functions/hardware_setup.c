#include "Headers/Macros.h"
#include "Headers/delay_functions.h"
#include "Headers/communications.h"

void rcc_init(void){

	//Clock enable bus RCC USART and GPIO
	RCC_APB1ENR |= (1U << 18);
	RCC_APB2ENR |= (0x3U << 3);
	RCC_APB2ENR |= (1U << 0);

}

void button_enable (void){

	//Limpieza y configuarcin de bits 4:7 para PB1
	GPIOx_CRL(GPIOB_BASE) &= ~(0xFU << 4);
	GPIOx_CRL(GPIOB_BASE) |= (1U << 7);
	//Configuracion de ODR en estado alto
	GPIOx_ODR(GPIOB_BASE) &= ~(1U << 1);
	GPIOx_ODR(GPIOB_BASE) |= (1U << 1);

	//Configuracion para interrupcion
	AFIO_EXTICR1 &= ~(0xFU << 4);
	AFIO_EXTICR1 |= (1U << 4);

	//Configuracion EXTI
	EXTI_IMR |= (1U << 1);
	EXTI_RTSR |= (1U << 1);
	//EXTI_FTSR |= (1U << 1);
	EXTI_PR |= (1U << 1);

	//Habilitacion de NVIC EXTI1
	NVIC_ISER0 |= (1U << 7);

}

void init_hardware(void){

	rcc_init();
	system_init_72MHz();
	delay_init();
	button_enable();

}
