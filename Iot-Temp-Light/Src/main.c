/**
 ******************************************************************************
 * Proyecto        : Control de luz Iot
 * @author         : Simon Arellano
 * @brief          : Main program body
 ******************************************************************************
 */

#include <stdint.h>
#include "Headers/Macros.h"
#include "Headers/communications.h"
#include "Headers/delay_functions.h"
#include <stddef.h>
#include <string.h>

uint8_t button_pressed = 0;

int main(void)
{
	//Clock enable bus RCC USART and GPIO
	RCC_APB1ENR |= (1U << 18);
	RCC_APB2ENR |= (0x3U << 3);

    // Inicializar la UART
	init_system();
	comunicate_process();
    uart_init();
    button_enable();

    while(1) {

            // Detectar flanco de subida (botón presionado)
            if((GPIOx_IDR(GPIOB_BASE) & (1U << 1)) && !button_pressed) {
                //Marca del boton presionado
            	button_pressed = 1;

                delay_ms(50);
                recive_data_ok();
                delay_ms(50);
                recive_data_ok();
                delay_ms(50);


            }

            // Detectar flanco de bajada (botón liberado)
            if(!(GPIOx_IDR(GPIOB_BASE) & (1U << 1))) {
            	//Reinicio de variable para marcar el boton como no presionado
                button_pressed = 0;
        }

    }
}

