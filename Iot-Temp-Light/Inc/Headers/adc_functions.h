#ifndef ADC_FUNCTIONS_H
#define ADC_FUNCTIONS_H
#include <stdint.h>


uint16_t get_temp_vref(void);
float get_celsius(void);
void float_to_str(float val, char *buffer, int prec);
void send_temp(void);

#endif
