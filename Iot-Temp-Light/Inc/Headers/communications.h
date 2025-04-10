#ifndef COMMUNICATIONS_H
#define COMMUNICATIONS_H

void uart_init (void);
void button_enable (void);
void init_system (void);
void USART3_IRQHandler(void);
void transmit_string(const char* str);
void comunicate_process (void);
void recive_data_ok (void);
void recive_data_error (void);

#endif
