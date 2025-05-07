#include "Headers/adc_functions.h"
#include "Headers/Macros.h"
#include "Headers/communications.h"
#include "Headers/delay_functions.h"
#include <stdint.h>


void send_temp(void){


	float temp =  get_celsius();
	char temp_str[32], final_str[40];

	float_to_str(temp, temp_str, 2);

	int len = 0;

	while (temp_str[len] != '\0') {

		final_str[len] = temp_str[len];
	    len++;
	}

	final_str[len++] = '\r';  // agrega \r
	final_str[len++] = '\n';  // agrega \n
	final_str[len] = '\0';    // fin de cadena

	transmit_string(final_str);

}

uint16_t get_temp_vref(void){

	//Inicia conversion SWSTART
	ADC1_CR2 |= (1U << 22);
	//Se escribe la lectura del canal 16 en la variable direct_temp
	while(!(ADC1_SR & (1 << 1)));

	return (uint16_t)ADC1_DR;

}

float get_celsius(void){


	uint16_t direct_temp = get_temp_vref();

	    // 1) Calcular Vdda real
	//float Vdda = 3.3f * ((float)VREFINT_CAL / (float)direct_vref);

	    // 2) Obtener voltaje del sensor
	float V_sense = (direct_temp * 3.3f) / 4096.0f;

	    // 3) Aplicar fórmula del datasheet
	    //    V_25 = 1.43 V, Avg_Slope = 4.3 mV/°C
    float temperatura = ((V_sense - 1.43f) / 0.0043f) + 25.0f;
    return temperatura;

}


void float_to_str(float val, char *buffer, int prec) {
    if (val < 0) {
        *buffer++ = '-';
        val = -val;
    }

    int32_t ipart = (int32_t)val;
    float fpart = val - (float)ipart;

    // Parte entera
    char *p = buffer;
    char temp[12];
    int i = 0;
    if (ipart == 0) {
        temp[i++] = '0';
    } else {
        while (ipart > 0) {
            temp[i++] = '0' + (ipart % 10);
            ipart /= 10;
        }
    }

    // Escribe parte entera en orden correcto
    while (i--) {
        *p++ = temp[i];
    }

    *p++ = '.';

    // Parte decimal
    for (int j = 0; j < prec; j++) {
        fpart *= 10.0f;
        int digit = (int)fpart;
        *p++ = '0' + digit;
        fpart -= digit;
    }

    *p = '\0';  // Fin de string
}
