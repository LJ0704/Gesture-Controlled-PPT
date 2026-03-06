/*
 * Bluetooth_JDY31.h
 *
 *  Created on: Dec 3, 2025
 *      Author: Likhita
 */

#ifndef INC_BLUETOOTH_JDY31_H_
#define INC_BLUETOOTH_JDY31_H_

#include <stm32f091xc.h>
#define baud_rate 9600
#define F_USART_CLOCK (48UL*1000UL*1000UL) //  24 MHz
void Init_USART1();
void uart_send(uint8_t d);
uint8_t uart_recv(void);
void uart1_print(const char* s);
#endif /* INC_BLUETOOTH_JDY31_H_ */
