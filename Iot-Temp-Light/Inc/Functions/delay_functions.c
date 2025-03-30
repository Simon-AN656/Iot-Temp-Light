// delay_function.c
#include "Headers/delay_functions.h"

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
