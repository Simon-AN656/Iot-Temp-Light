#ifndef MACROS_H
#define MACROS_H
#include <stdint.h>
/*

0x4001 0800 - 0x4001 0BFF GPIO Port A Bus-- APB2
0x4001 0C00 - 0x4001 0FFF GPIO Port B Bus-- APB2
0x4001 1000 - 0x4001 13FF GPIO Port C Bus-- APB2
0x4000 0000 - 0x4000 03FF TIM2 timer Bus-- APB1
0x4002 1000 - 0x4002 13FF Reset and clock control RCC Bus-- AHB
0x4000 4800 - 0x4000 4BFF USART3
 */

//Definicion de mascros de las bases de los  registros
#define GPIOB_BASE 		0x40010C00U
#define USART3_BASE 	0x40004800U
#define RCC_BASE 		0x40021000U

//Definicion de macros para offset de los registros
#define RCC_APB1ENR_OFFSET	0x1CU
#define RCC_APB2ENR_OFFSET 	0x18U
#define CRH_OFFSET 			0x04U
#define ODR_OFFSET			0x0CU
#define IDR_OFFSET			0x08U
#define USART_SR_OFFSET 	0x00U
#define USART_DR_OFFSET		0x04U
#define USART_BRR_OFFSET	0x08U
#define USART_CR1_OFFSET	0x0CU

//Definicion de las macros para la activacion de los registros base + offsets
#define RCC_APB1ENR 		(*(volatile uint32_t*)(RCC_BASE + RCC_APB1ENR_OFFSET))
#define RCC_APB2ENR 		(*(volatile uint32_t*)(RCC_BASE + RCC_APB2ENR_OFFSET))
#define GPIOx_CRH(GPIOx) 	(*(volatile uint32_t*)(GPIOx + CRH_OFFSET))
#define GPIOx_ODR(GPIOx) 	(*(volatile uint32_t*)(GPIOx + ODR_OFFSET))
#define GPIOx_IDR(GPIOx) 	(*(volatile uint32_t*)(GPIOx + IDR_OFFSET))
#define USARTx_SR(USARTx) 	(*(volatile uint32_t*)(USARTx + USART_SR_OFFSET))
#define USARTx_DR(USARTx) 	(*(volatile uint32_t*)(USARTx + USART_DR_OFFSET))
#define USARTx_BRR(USARTx) 	(*(volatile uint32_t*)(USARTx + USART_BRR_OFFSET))
#define USARTx_CR1(USARTx) 	(*(volatile uint32_t*)(USARTx + USART_CR1_OFFSET))


#endif
