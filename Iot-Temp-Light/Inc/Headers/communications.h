#ifndef COMMUNICATIONS_H
#define COMMUNICATIONS_H

void uart_init (void);
void transmit_string(const char* str);
void receive_string(char* buffer, int length);
void comunicate_process (void);
void recive_data_ok (void);
void recive_data_error (void);

#endif
