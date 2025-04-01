/*
 PB10 (TX):
Configúrala como salida de función alternativa (Alternate Function Push-Pull) con velocidad máxima (por ejemplo, 50MHz).
PB11 (RX):
Configúrala como entrada flotante (Input Floating) o con resistencia de pull-up, según tus necesidades.
 */

#include "Headers/communications.h"
#include "Headers/Macros.h"
#include "Headers/delay_functions.h"


//Funcion para activar UART3
void uart_init (void){

	//Activacion de RCC USART y GPIO
	RCC_APB1ENR |= (1U << 18);
	RCC_APB2ENR |= (0x3U << 3);

	//Activacion de pines PB10 y PB11
	GPIOx_CRH(GPIOB_BASE) &= ~(0xFFU << 8);
	GPIOx_CRH(GPIOB_BASE) |= (0x4BU << 8);
	GPIOx_CRH(GPIOB_BASE) &= ~(0xFFFU << 20);
	GPIOx_CRH(GPIOB_BASE) |= (0x333U << 20);
	GPIOx_CRL(GPIOB_BASE) &= ~(0xFU << 4);
	GPIOx_CRL(GPIOB_BASE) |= (1U << 7);
	GPIOx_ODR(GPIOB_BASE) &= ~(1U << 1);

	/*Definicion de BaudRate USARTDIV = PCLK/(16 * BaudRate)
	 BaudRate= 115200	PCLK= 8MHz
	 USARTDIV =  8MHz/(16 * 115200) = 36MHz/1843200 = 19.5313
	 DIV_Mantissa =  19
	 DIV_Fraction = .5313 * 16 = 8.50 = 8 (Redondeado)
	 USART_BRR = (Mantisa << 4)∣Fraccion = (4 << 4)∣5 = 0x45
	 */
	USARTx_BRR(USART3_BASE) = (0x13U << 4)|8U;

	//Configuracion de Control register 1
	USARTx_CR1(USART3_BASE) = 0x00000000U;
	USARTx_CR1(USART3_BASE) |= (1U << 13) | (0x3U << 2);

	//Se finalizo la iniciacion de UART
	delay_ms(100);
	GPIOx_CRH(GPIOC_BASE) &= ~(0xFU << 20);
	GPIOx_CRH(GPIOC_BASE) |= (0x3U << 20);
	GPIOx_ODR(GPIOC_BASE) |= (1U << 13);
	GPIOx_ODR(GPIOC_BASE) &= ~(1U << 13);
	delay_ms(100);

}

// Función para enviar un string a través de UART
void transmit_string(const char* str) {
    while (*str) {
        // Enviar cada caracter del string
        while (!(USARTx_SR(USART3_BASE) & (1U << 7))) {}  // Esperar a que el buffer de TX esté vacío
        USARTx_DR(USART3_BASE) = *str++;  // Enviar el carácter
    }
}

// Función para recibir un string a través de UART con timeout
void receive_string(char* buffer, int length) {
    int i = 0;
    int timeout = 10000;  // Tiempo de espera máximo para recibir datos (puedes ajustar este valor)

    while (i < length - 1) {
        // Esperar hasta que haya datos en RX o se alcance el tiempo de espera
        if (timeout-- == 0) {
            // Si se alcanzó el timeout, salimos
            buffer[i] = '\0';  // Aseguramos que el string termine correctamente
            return;
        }

        if (USARTx_SR(USART3_BASE) & (1U << 5)) {  // Verifica si hay datos en el buffer de recepción
            char received_char = USARTx_DR(USART3_BASE);  // Leer el dato recibido
            buffer[i++] = received_char;

            if (received_char == '\n') {
                break;  // Romper si hemos recibido el final de línea
            }
        }
    }
    buffer[i] = '\0';  // Asegurarse de que el string esté terminado en '\0'
}



void comunicate_process (void){

	GPIOx_ODR(GPIOB_BASE) |= (1U << 15);
	delay_ms(100);
	GPIOx_ODR(GPIOB_BASE) &= ~(1U << 15);

}

void recive_data_ok (void){

	GPIOx_ODR(GPIOB_BASE) |= (1U << 14);
	delay_ms(100);
	GPIOx_ODR(GPIOB_BASE) &= ~(1U << 14);

}

void recive_data_error (void){

	GPIOx_ODR(GPIOB_BASE) |= (1U << 13);
	delay_ms(100);
	GPIOx_ODR(GPIOB_BASE) &= ~(1U << 13);

}


