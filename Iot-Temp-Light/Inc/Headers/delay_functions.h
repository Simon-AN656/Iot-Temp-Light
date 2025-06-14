// delay_function.h
#ifndef DELAY_FUNCTION_H
#define DELAY_FUNCTION_H

#include <stdint.h>  // Para que el tipo uint32_t esté definido

// Declaración de la función delay_ms
void delay_us(uint16_t us);
void delay_ms(uint16_t ms);
void system_init_72MHz();
void delay_init();

#endif // DELAY_FUNCTION_H
