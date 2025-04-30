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

	//Configuracion de memoria flash:
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

	// Espera hasta que el PLL esté configurado correctamente como SYSCLK
	while ((RCC_CFGR & (0x3U << 2)) != (0x2U << 2));

}

// Función de retardo aproximado en milisegundos
void delay_ms(uint32_t ms)
{
    volatile uint32_t count;
    while(ms--)
    {
        // Este bucle interno es aproximado; puedes ajustarlo para lograr 1 ms
        for(count = 0; count < 8000; count++) { }
    }
}
