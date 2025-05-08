#ifndef ADC_FUNCTIONS_H
#define ADC_FUNCTIONS_H
#include <stdint.h>

void get_temp_vref(uint16_t* direct_temp);
float get_celsius(void);
void float_to_str(float val, char *buffer, int prec);
void send_temp(void);

#endif
