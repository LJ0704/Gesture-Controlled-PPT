/*
 * UART_Init.h
 *
 *  Created on: Dec 3, 2025
 *      Author: Likhita
 */

#ifndef INC_UART_INIT_H_
#define INC_UART_INIT_H_

#include <stm32f091xc.h>

#define baud_rate 9600
#define F_USART_CLOCK (48UL*1000UL*1000UL) //  24 MHz

void Init_USART2();

#endif /* INC_UART_INIT_H_ */
