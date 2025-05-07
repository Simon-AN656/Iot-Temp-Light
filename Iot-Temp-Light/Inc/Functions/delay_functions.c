#include "Headers/delay_functions.h"
#include "Headers/Macros.h"

/*******************************************************************************
 * Función: system_init_72MHz
 * Descripción: Configura el sistema a 72 MHz usando HSE y PLL.
 *  - Configura el reloj del sistema (SYSCLK) a 72 MHz.
 *  - Configura el bus AHB (72 MHz), APB1 (36 MHz) y APB2 (72 MHz).
 *  - Configura la memoria flash para velocidad de acceso adecuada.
 *
 * Pasos:
 * 1. Habilita el oscilador HSE (High-Speed External).
 * 2. Configura el PLL (Phase Locked Loop) para multiplicar el HSE por 9.
 * 3. Configura el bus AHB y los buses APB1/APB2.
 * 4. Configura el acceso a la memoria flash para la velocidad de 72 MHz.
 *
 * Configuración:
 * - HSE: 8 MHz (frecuencia de entrada).
 * - PLL: Multiplicador de 9 (8 MHz * 9 = 72 MHz).
 * - AHB: 72 MHz.
 * - APB1: 36 MHz.
 * - APB2: 72 MHz.
 * ****************************************************************************/
void system_init_72MHz(){

	//Configuracion de memoria flash
	FLASH_ACR |= (1U << 4);
	FLASH_ACR &= ~(0x7 << 0);
	FLASH_ACR |= (0x2 << 0);

	//Se habilita el oscilador externo(HSE)
	RCC_CR |= (1U << 16);
	while ((RCC_CR & (1 << 17)) == 0)

	//Configuracion de PLL
	RCC_CFGR &= ~(0xFU << 18);
	RCC_CFGR |= (1U << 16);
	RCC_CFGR |= (0x7U << 18);

	//Habilitacion de PLL
	RCC_CR |= (1U << 24);
	while ((RCC_CR & (1 << 25)) == 0);

	// Configuración de los buses: AHB (72 MHz), APB1 (36 MHz), APB2 (72 MHz)
	RCC_CFGR &= ~(0x3U << 0);
	RCC_CFGR |= (0x2U << 0);

	RCC_CFGR &= ~(0x3FFU << 4);
	RCC_CFGR |= (1U << 10);

	//Divisior de PLL de ADC dividido a 6 = 12MHz
	RCC_CFGR &= ~(0x3U << 14);
	RCC_CFGR |= (0x2U << 14);

	// Espera hasta que el PLL esté configurado correctamente como SYSCLK
	while ((RCC_CFGR & (0x3U << 2)) != (0x2U << 2));


/********************************************************************************************************
 * Inicialización de los LEDs para indicar el estado del sistema:
 * - El LED en PC13 se enciende para indicar que el microcontrolador está encendido y el sistema
 *   ha sido inicializado correctamente.
 * - Se configuran los pines PB13, PB14 y PB15 para LEDs RGB que servirán como indicadores de estado
 *   en las funciones `receive_data_ok`, `receive_data_error` y `communicate_process`.
 *
 * Descripción de la configuración:
 * - Configuración de pines PB13, PB14 y PB15 como salidas (para LEDs RGB).
 * - Configuración de pin PC13 como salida para el indicador de encendido.
 * - Se enciende el LED de encendido en PC13 (se pone en '1').
 * - Se apaga el LED de encendido en PC13 (se pone en '0') al finalizar la configuración.
 ********************************************************************************************************/

	//Se limpian y configuran bits 20:31 para pines PB13, PB14 y PB15
	GPIOx_CRH(GPIOB_BASE) &= ~(0xFFFU << 20);
	GPIOx_CRH(GPIOB_BASE) |= (0x333U << 20);
	//Se limpian y configuran bits 20:23 para pin PC13
	GPIOx_CRH(GPIOC_BASE) &= ~(0xFU << 20);
	GPIOx_CRH(GPIOC_BASE) |= (0x3U << 20);
	//Se ponen en 1 pin PC13
	GPIOx_ODR(GPIOB_BASE) |= (1U << 1);
	GPIOx_ODR(GPIOC_BASE) |= (1U << 13);
	GPIOx_ODR(GPIOC_BASE) &= ~(1U << 13);

}

void delay_init(){

	RCC_APB1ENR |= (1U << 0);

	TIMx_PSC(TIM2_BASE) = 72 - 1;
	TIMx_ARR(TIM2_BASE) = 0xFFFF;
	TIMx_EGR(TIM2_BASE) = (1U << 0);
	TIMx_CR1(TIM2_BASE) = 0;

}

void delay_us(uint16_t us){

	TIMx_CR1(TIM2_BASE) &= ~(1U << 0);      // CEN = 0

	    // 2) Fuerza el update para cargar PSC si hiciera falta
	TIMx_EGR(TIM2_BASE) = (1U << 0);

	TIMx_CNT(TIM2_BASE) = 0;
	TIMx_SR(TIM2_BASE) &= ~(1U << 0);
	TIMx_CR1(TIM2_BASE) |= (1U << 0);

	while (TIMx_CNT(TIM2_BASE) < us){

	}

	TIMx_CR1(TIM2_BASE) &= ~(1U << 0);
}

// Función de retardo aproximado en milisegundos
void delay_ms(uint16_t ms)
{
    while(ms--)
    {

    	delay_us(1000);

    }
}
