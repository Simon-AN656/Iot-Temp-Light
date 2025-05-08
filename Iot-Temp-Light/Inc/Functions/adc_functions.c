#include "Headers/adc_functions.h"
#include "Headers/Macros.h"
#include "Headers/communications.h"
#include "Headers/delay_functions.h"
#include <stdint.h>

uint16_t direct_temp = 0;

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

void get_temp_vref(uint16_t* direct_temp){

	//Se escribe la lectura del canal 16 en la variable direct_temp
	while(!(ADC1_SR & (1 << 1)));
	*direct_temp = (uint16_t)ADC1_DR;

}

float get_celsius(void){

	get_temp_vref(&direct_temp);

	//float V_sense = get_vsense();

	    // 2) Obtener voltaje del sensor
	float V_sense = (direct_temp * 3.3) / 4096.0f;

	    // 3) Aplicar fórmula del datasheet
	    //    V_25 = 1.43 V, Avg_Slope = 4.3 mV/°C
    float temperatura = ((1.43f - V_sense) / 0.0043f) + 25.0f;
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


/*float get_vsense(void){

	float V_sense = (direct_temp * 3.3) / 4096.0f;

	return V_sense;

}

void send_dtemp(void){


	float temp =  direct_temp;
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


void send_vsense(void){


	float send_ve =  get_celsius();
	char ve_str[32], final_str[40];

	float_to_str(send_ve, ve_str, 2);

	int len = 0;

	while (ve_str[len] != '\0') {

		final_str[len] = ve_str[len];
	    len++;
	}

	final_str[len++] = '\r';  // agrega \r
	final_str[len++] = '\n';  // agrega \n
	final_str[len] = '\0';    // fin de cadena

	transmit_string(final_str);

}*/
