#include "Headers/Macros.h"
#include "Headers/delay_functions.h"
#include "Headers/communications.h"
#include "Headers/delay_functions.h"

void rcc_init(void){

	//Clock enable bus RCC USART, GPIO and AFIO
	RCC_APB1ENR |= (1U << 18);
	RCC_APB2ENR |= (0x3U << 3);
	RCC_APB2ENR |= (1U << 0);
	RCC_APB2ENR |= (1U << 9);

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

void init_adc(void){

	ADC1_CR2 |= (1U << 0);
	delay_us(10);


	//Calibracion del sensor
	ADC1_CR2 |= (1U << 2);
	while (ADC1_CR2 & (1U << 2)); //Bucle de espera a la terminacion de CAL

	//Activacion de sensor de temperatura
	ADC1_CR2 |= (1U << 23);
	delay_us(100);

	ADC1_CR2 &= ~(1U << 20);
	//ADC1_CR1 &= ~(1U << 8);

	//Habilita 2 converisones
	ADC1_SQR1 &= ~(0xFU << 20);
	ADC1_SQR1 |= (0x1U << 20);


	//Configura sample time largo para canal 16
	ADC1_SMPR1 &= ~(0x7U << 18);
	ADC1_SMPR1 |= (0x7U << 18);  // channel 16

	// Canal 17 (VREFINT)
	ADC1_SMPR1 &= ~(0x7U << 21); // Limpia bits
	ADC1_SMPR1 |= (0x7U << 21);  // Tiempo de muestreo máximo

	// Configura SQ1 = canal 16, SQ2 = canal 17
	ADC1_SQR3 = (16U << 0) | (17U << 5);

	ADC1_CR1 |= (1U << 8); // Habilita el modo de escaneo

	ADC1_CR2 |= (1U << 1);

	ADC1_SR = 0;

}

void init_hardware(void){

	rcc_init();
	system_init_72MHz();
	delay_init();
	button_enable();
	init_adc();

}
