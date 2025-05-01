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

	system_init_72MHz();
	init_system();
	delay_init();
	comunicate_process();

    // Inicializar la UART

	comunicate_process();
    uart_init();
    button_enable();

    while(1) {

    	delay_us(480);
    	recive_data_ok();
    	delay_us(480);
        recive_data_ok();

            /* Detectar flanco de subida (botón presionado)
            if((GPIOx_IDR(GPIOB_BASE) & (1U << 1)) && !button_pressed) {
                //Marca del boton presionado
            	button_pressed = 1;

                delay_us(480);
                recive_data_ok();
                delay_us(480);
                recive_data_ok();
                delay_us(480);


            }

            // Detectar flanco de bajada (botón liberado)
            if(!(GPIOx_IDR(GPIOB_BASE) & (1U << 1))) {
            	//Reinicio de variable para marcar el boton como no presionado
                button_pressed = 0;
        }*/

    }
}

