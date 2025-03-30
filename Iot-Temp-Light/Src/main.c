/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "Headers/Macros.h"
#include "Headers/communications.h"
#include "Headers/delay_functions.h"



int main(void)
{
	uart_init();

	while(1){

		comunicate_process();
		delay_ms(50);
		recive_data_ok();
		delay_ms(50);
		recive_data_error();
		delay_ms(50);


	}


}
