#ifndef MACROS_H
#define MACROS_H
#include <stdint.h>
/*********************************************************************
 * 0x4001 0800 - 0x4001 0BFF GPIO Port A Bus-- APB2
 * 0x4001 0C00 - 0x4001 0FFF GPIO Port B Bus-- APB2
 * 0x4001 1000 - 0x4001 13FF GPIO Port C Bus-- APB2
 * 0x4000 0000 - 0x4000 03FF TIM2 timer Bus-- APB1
 * 0x4002 1000 - 0x4002 13FF Reset and clock control RCC Bus-- AHB
 * 0x4000 4800 - 0x4000 4BFF USART3
 *********************************************************************/


//Definicion de mascros de las bases de los  registros
#define GPIOB_BASE 		0x40010C00U
#define GPIOC_BASE 		0x40011000U
#define USART3_BASE 	0x40004800U
#define RCC_BASE 		0x40021000U
#define EXTI_BASE 		0x40010400U
#define AFIO_BASE		0x40010000U
#define ADC1_BASE		0x40012400U
#define NVIC_BASE		0xE000E100U
#define FLASH_BASE 		0x40022000U
#define TIM2_BASE 		0x40000000U


//Flash access control memory
#define FLASH_ACR_OFFSET 	0x00U

//Definicion de macros para offset de los registros
#define RCC_APB1ENR_OFFSET	0x1CU
#define RCC_APB2ENR_OFFSET 	0x18U
#define RCC_CR_OFFSET		0x00U
#define RCC_CFGR_OFFSET		0x04U
#define EXTI_IMR_OFFSET		0x00U
#define EXTI_RTSR_OFFSET	0x08U
#define EXTI_FTSR_OFFSET	0x0CU
#define EXTI_PR_OFFSET		0x14U
#define AFIO_EXTICR1_OFFSET	0x08U
#define ADC1_CR2_OFFSET		0x08U
#define ADC1_SQR1_OFFSET	0x2CU
#define ADC1_SQR3_OFFSET	0x34U
#define ADC1_SR_OFFSET		0x00U
#define ADC1_DR_OFFSET		0x4CU
#define CRH_OFFSET 			0x04U
#define CRL_OFFSET			0x00U
#define ODR_OFFSET			0x0CU
#define IDR_OFFSET			0x08U
#define TIMx_CR1_OFFSET 	0x00U
#define TIMx_SR_OFFSET 		0x10U
#define TIMx_CNT_OFFSET 	0x24U
#define TIMx_PSC_OFFSET 	0x28U
#define TIMx_ARR_OFFSET 	0x2CU
#define TIMx_EGR_OFFSET 	0x14U
#define USART_SR_OFFSET 	0x00U
#define USART_DR_OFFSET		0x04U
#define USART_BRR_OFFSET	0x08U
#define USART_CR1_OFFSET	0x0CU
#define USART_CR2_OFFSET	0x10U
#define AFIO_MAPR_OFFSET  	0x04U
#define NVIC_ISER0_OFFSET	0x00U
#define NVIC_ISER1_OFFSET	0x04U

//Macros para NVIC
#define NVIC_ISER1 (*(volatile uint32_t*)(NVIC_BASE + NVIC_ISER1_OFFSET))
#define NVIC_IPR_BASE  0xE000E400
#define NVIC_ISER0 (*(volatile uint32_t*)(NVIC_BASE + NVIC_ISER0_OFFSET))

/************************************************************************************
 * Macro para establecer la prioridad de una interrupción (IRQ)
 * IRQn: número de la interrupción (p.ej. 39)
 * PRIORITY: valor de prioridad (0 a 15, donde menor valor es mayor prioridad)
 * Los 4 bits más altos de cada byte son efectivos, entonces se hace: PRIORITY << 4
 * **********************************************************************************/
#define NVIC_SET_PRIORITY(IRQn, PRIORITY)  \
    (*(volatile uint8_t*)(NVIC_IPR_BASE + ((IRQn) & 0xFF)) = ((PRIORITY & 0x0F) << 4))


//Definicion de las macros para la activacion de los registros base + offsets
#define FLASH_ACR 			(*(volatile uint32_t*)(FLASH_BASE + FLASH_ACR_OFFSET))
#define RCC_APB1ENR 		(*(volatile uint32_t*)(RCC_BASE + RCC_APB1ENR_OFFSET))
#define RCC_APB2ENR 		(*(volatile uint32_t*)(RCC_BASE + RCC_APB2ENR_OFFSET))
#define RCC_CR		 		(*(volatile uint32_t*)(RCC_BASE + RCC_CR_OFFSET))
#define RCC_CFGR		 	(*(volatile uint32_t*)(RCC_BASE + RCC_CFGR_OFFSET))
#define EXTI_IMR			(*(volatile uint32_t*)(EXTI_BASE + EXTI_IMR_OFFSET))
#define EXTI_RTSR			(*(volatile uint32_t*)(EXTI_BASE + EXTI_RTSR_OFFSET))
#define EXTI_FTSR			(*(volatile uint32_t*)(EXTI_BASE + EXTI_FTSR_OFFSET))
#define EXTI_PR				(*(volatile uint32_t*)(EXTI_BASE + EXTI_PR_OFFSET))
#define AFIO_EXTICR1		(*(volatile uint32_t*)(AFIO_BASE + AFIO_EXTICR1_OFFSET))
#define ADC1_CR2			(*(volatile uint32_t*)(ADC1_BASE + ADC1_CR2_OFFSET))
#define ADC1_SQR1			(*(volatile uint32_t*)(ADC1_BASE + ADC1_SQR1_OFFSET))
#define ADC1_SQR3			(*(volatile uint32_t*)(ADC1_BASE + ADC1_SQR3_OFFSET))
#define ADC1_SR				(*(volatile uint32_t*)(ADC1_BASE + ADC1_SR_OFFSET))
#define ADC1_DR				(*(volatile uint32_t*)(ADC1_BASE + ADC1_DR_OFFSET))
#define GPIOx_CRH(GPIOx) 	(*(volatile uint32_t*)(GPIOx + CRH_OFFSET))
#define GPIOx_CRL(GPIOx) 	(*(volatile uint32_t*)(GPIOx + CRL_OFFSET))
#define GPIOx_ODR(GPIOx) 	(*(volatile uint32_t*)(GPIOx + ODR_OFFSET))
#define GPIOx_IDR(GPIOx) 	(*(volatile uint32_t*)(GPIOx + IDR_OFFSET))
#define TIMx_CR1(TIMx) 		(*(volatile uint32_t*)(TIMx + TIMx_CR1_OFFSET))
#define TIMx_SR(TIMx)  		(*(volatile uint32_t*)(TIMx + TIMx_SR_OFFSET))
#define TIMx_CNT(TIMx)  	(*(volatile uint32_t*)(TIMx + TIMx_CNT_OFFSET))
#define TIMx_PSC(TIMx)  	(*(volatile uint32_t*)(TIMx + TIMx_PSC_OFFSET))
#define TIMx_ARR(TIMx)  	(*(volatile uint32_t*)(TIMx + TIMx_ARR_OFFSET))
#define TIMx_EGR(TIMx)  	(*(volatile uint32_t*)(TIMx + TIMx_EGR_OFFSET))
#define USARTx_SR(USARTx) 	(*(volatile uint32_t*)(USARTx + USART_SR_OFFSET))
#define USARTx_DR(USARTx) 	(*(volatile uint32_t*)(USARTx + USART_DR_OFFSET))
#define USARTx_BRR(USARTx) 	(*(volatile uint32_t*)(USARTx + USART_BRR_OFFSET))
#define USARTx_CR1(USARTx) 	(*(volatile uint32_t*)(USARTx + USART_CR1_OFFSET))
#define USARTx_CR2(USARTx) 	(*(volatile uint32_t*)(USARTx + USART_CR2_OFFSET))
#define AFIO_MAPR 			(*(volatile uint32_t*)(AFIO_BASE + AFIO_MAPR_OFFSET))


#endif
