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

	//Pin configuration PB10 ouput-push-pull and PB11 floating-input
	GPIOx_CRH(GPIOB_BASE) &= ~(0xFFU << 8);
	GPIOx_CRH(GPIOB_BASE) |= (0x4BU << 8);

	//
	USARTx_CR2(USART3_BASE) &= ~(0x3U << 12);

	/*BaudRate setup USARTDIV = PCLK/(16 * BaudRate)
	 BaudRate= 115200	PCLK= 8MHz
	 USARTDIV =  8MHz/(16 * 115200) = 8MHz/1843200 = 4.34
	 DIV_Mantissa =  4
	 DIV_Fraction = .34 * 16 = 5.44 = 6
	 USART_BRR = (Mantisa << 4)∣Fraccion = (4 << 4)∣6
	 NOTE: Default HSI 8MHz
	 */
	USARTx_BRR(USART3_BASE) = (4 << 4) | 6;

	//Control register 1 configuration
	USARTx_CR1(USART3_BASE) = 0x0000;
	USARTx_CR1(USART3_BASE) |= (1U << 13) | (0x3U << 2);
	(void) USARTx_DR(USART3_BASE);  // Realiza la lectura para limpiar RXNE si estuviera activo

	USARTx_CR1(USART3_BASE) |= (1U << 5);

	NVIC_SET_PRIORITY(39, 3);
	NVIC_ISER1 |= (1U << 7);

}

void init_system (void){

	//Se limpian y configuran bits 20:31 para pines PB13, PB14 y PB15
	GPIOx_CRH(GPIOB_BASE) &= ~(0xFFFU << 20);
	GPIOx_CRH(GPIOB_BASE) |= (0x333U << 20);
	//Se limpian y configuran bits 20:23 para pin PC13
	//GPIOx_CRH(GPIOC_BASE) &= ~(0xFU << 20);
	//GPIOx_CRH(GPIOC_BASE) |= (0x3U << 20);
	//Se ponen en 1 pin PC13
	GPIOx_ODR(GPIOB_BASE) |= (1U << 1);
	//GPIOx_ODR(GPIOC_BASE) |= (1U << 13);
	//GPIOx_ODR(GPIOC_BASE) &= ~(1U << 13);
}

void button_enable (void){

	//Limpieza y configuarcin de bits 4:7 para PB1
	GPIOx_CRL(GPIOB_BASE) &= ~(0xFU << 4);
	GPIOx_CRL(GPIOB_BASE) |= (1U << 7);
	//Configuracion de ODR en estado alto
	GPIOx_ODR(GPIOB_BASE) &= ~(1U << 1);
	GPIOx_ODR(GPIOB_BASE) |= (1U << 1);

}

void USART3_IRQHandler(void){


	if(USARTx_SR(USART3_BASE) & (1U << 5)){

		char dato = USARTx_DR(USART3_BASE);
		if(dato == 'G'){
			transmit_string("OK es la G\r\n");
			recive_data_ok();
		}else if(dato == 'R'){
			transmit_string("OK es la R\r\n");
			recive_data_error();
		}else if(dato == 'B'){
			transmit_string("OK es la B\r\n");
			comunicate_process();
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

// Función para recibir un string a través de UART con timeout
/*void receive_string(char* buffer, int length) {
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
}*/



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



