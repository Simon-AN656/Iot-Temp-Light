#ifndef ADC_FUNCTIONS_H
#define ADC_FUNCTIONS_H
#include <stdint.h>


void get_temp_vref(uint16_t* direct_temp, uint16_t* direct_vref);
float get_celsius(void);
void float_to_str(float val, char *buffer, int prec);
void send_temp(void);
/*
void send_vdda(void);
void send_vsense(void);
float get_vdda(void);
float get_vsense(void);
void send_dvref(void);
void send_dtemp(void);
*/

#endif
