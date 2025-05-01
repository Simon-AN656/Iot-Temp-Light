#include "Headers/communications.h"
#include "Headers/Macros.h"
#include "Headers/delay_functions.h"
#include <string.h>

volatile char rx_buffer[64];   // Definición del buffer de recepción
volatile uint8_t rx_index = 0; // Definición del índice de recepción

//Funcion para activar UART3
void uart_init (void){

	//Pin configuration PB10 ouput-push-pull and PB11 floating-input
	GPIOx_CRH(GPIOB_BASE) &= ~(0xFFU << 8);
	GPIOx_CRH(GPIOB_BASE) |= (0x4BU << 8);

	//
	USARTx_CR2(USART3_BASE) &= ~(0x3U << 12);

/************************************************************
* BaudRate setup USARTDIV = PCLK/(16 * BaudRate)
* BaudRate= 115200	PCLK= 8MHz
* USARTDIV =  8MHz/(16 * 115200) = 8MHz/1843200 = 4.34
* DIV_Mantissa =  4/19
* DIV_Fraction = .34 * 16 = 5.44 = 6/ .53 * 16 = 8.48 = 9
* USART_BRR = (Mantisa << 4)∣Fraccion = (4 << 4)∣6
* NOTE: Default HSI 8MHz
* ***********************************************************/

	USARTx_BRR(USART3_BASE) = (0x13 << 4) | 9;

	//Control register 1 configuration
	USARTx_CR1(USART3_BASE) = 0x0000;
	USARTx_CR1(USART3_BASE) |= (1U << 13) | (0x3U << 2);
	// Realiza la lectura para limpiar RXNE si estuviera activo
	(void) USARTx_DR(USART3_BASE);
	//Se habilita el bit RXNIEIE para la interrupcion de RX
	USARTx_CR1(USART3_BASE) |= (1U << 5);
	//Se configura la prioridad y habilita el NVIC para la interrupcion de USART3
	NVIC_SET_PRIORITY(39, 3);
	NVIC_ISER1 |= (1U << 7);

}

void init_system (void){

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

void button_enable (void){

	//Limpieza y configuarcin de bits 4:7 para PB1
	GPIOx_CRL(GPIOB_BASE) &= ~(0xFU << 4);
	GPIOx_CRL(GPIOB_BASE) |= (1U << 7);
	//Configuracion de ODR en estado alto
	GPIOx_ODR(GPIOB_BASE) &= ~(1U << 1);
	GPIOx_ODR(GPIOB_BASE) |= (1U << 1);

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


//Función para enviar un string a través de UART
void transmit_string(const char* str) {
    while (*str) {
        // Enviar cada caracter del string
        while (!(USARTx_SR(USART3_BASE) & (1U << 7))) {}  // Esperar a que el buffer de TX esté vacío
        USARTx_DR(USART3_BASE) = *str++;  // Enviar el carácter
    }
}

void comunicate_process (void){

	GPIOx_ODR(GPIOB_BASE) |= (1U << 15);
	delay_us(480);
	GPIOx_ODR(GPIOB_BASE) &= ~(1U << 15);

}

void recive_data_ok (void){

	GPIOx_ODR(GPIOB_BASE) |= (1U << 14);
	delay_us(480);
	GPIOx_ODR(GPIOB_BASE) &= ~(1U << 14);

}

void recive_data_error (void){

	GPIOx_ODR(GPIOB_BASE) |= (1U << 13);
	delay_us(480);
	GPIOx_ODR(GPIOB_BASE) &= ~(1U << 13);

}



