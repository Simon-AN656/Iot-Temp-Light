#include "Headers/interrupts.h"
#include "Headers/hardware_setup.h"
#include "Headers/communications.h"
#include "Headers/Macros.h"
#include "Headers/delay_functions.h"
#include "Headers/adc_functions.h"
#include <string.h>

volatile uint8_t button_pressed = 0;
volatile char rx_buffer[64];   // Definición del buffer de recepción
volatile uint8_t rx_index = 0; // Definición del índice de recepción

void EXTI1_IRQHandler (void){

	if (EXTI_PR & (1U << 1)) {
		EXTI_PR |= (1U << 1);    // limpiar flag
		transmit_string("MCU Temperature: ");
	    send_temp();

	}

}

void USART3_IRQHandler(void)
{
    if (USARTx_SR(USART3_BASE) & (1U << 5)) // RXNE
    {
        char dato = USARTx_DR(USART3_BASE);

        // Si el dato es terminador y no hay nada en el buffer, descartar
        if ((dato == '\r' || dato == '\n') && (rx_index == 0))
            {
        // No hacer nada, ya que es un terminador extra
           return;
           }

        if (dato == '\r' || dato == '\n') {
            rx_buffer[rx_index] = '\0';

            // Procesar comando directamente:
            if (strcmp((char*)rx_buffer, "ON G") == 0) {
                transmit_string("Recibido G\r\n");
            } else if (strcmp((char*)rx_buffer, "ON R") == 0) {
                transmit_string("Recibido R\r\n");
            }else if (strcmp((char*)rx_buffer, "ON B") == 0) {
                transmit_string("Recibido B\r\n");
            }
            else {
                transmit_string("Comando desconocido\r\n");
                transmit_string((char*)rx_buffer);
                transmit_string("\r\n");

            }

            rx_index = 0;
        } else {
            if (rx_index < sizeof(rx_buffer) - 1) {
                rx_buffer[rx_index++] = dato;
            } else {
                rx_index = 0;
            }
        }
    }
}

