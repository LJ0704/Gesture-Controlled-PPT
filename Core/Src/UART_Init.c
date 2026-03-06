/*
 * UART_Init.c
 *
 *  Created on: Dec 3, 2025
 *      Author: Likhita
 */

#include "UART_Init.h"

#define CLEAR_MODER 0x3
#define GPIOP_OUTPUT 0x2
#define GPIOPA2_MODER 0x4
#define GPIOPA3_MODER 0x6
#define CLEAR_AF 0xF
#define GPIOPA2_AF 0x8
#define GPIOPA3_AF 0x12
#define SET_AF_1 0x1
/**
 * @brief     This function initializes UART 2 in asynchronous mode, with data size setting as 8, no parity.
 *            The Baud rate is set to 9600Hz.
 *
 * @param[in]  NA
 *
 * @formula    USARTx_BRR = f busclock/ baud_rate
 *             f busclock = 24MHz
 *
 * @return     NA
 *
 * Reference : Deans Book Page : 268 Listing 8.14 Init_USART2 to enable interrupt and bad rate
 *             Deans Book Page : 263 Listing 8.8
 *             Reference Manual RM0091 Chapter 27 for register information
 *
 *
 */
void Init_USART2() {

	//Enable APB2 USART2
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	//Enable clock for GPIO A port
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	//User Manual : Page No: 38/68
	//GPIO A pin 2 and 3 in alternate function 1 (USART1)
	//Set mode field to 2 for alternate function
	GPIOA->MODER &= ~(CLEAR_MODER << GPIOPA2_MODER);
	GPIOA->MODER &= ~(CLEAR_MODER << GPIOPA3_MODER);
	GPIOA->MODER |= (GPIOP_OUTPUT << GPIOPA2_MODER);
	GPIOA->MODER |= (GPIOP_OUTPUT << GPIOPA3_MODER);

	GPIOA->AFR[0] &= ~((CLEAR_AF << GPIOPA2_AF) | (CLEAR_AF << GPIOPA3_AF));
	GPIOA->AFR[0] |=  ((SET_AF_1 << GPIOPA2_AF) | (SET_AF_1 << GPIOPA3_AF));


    //Setting BRR register for baud rate 9600 Hz
	USART2->BRR = F_USART_CLOCK/ baud_rate;

	//Enable transmitter and receiver and USART
	USART2->CR1 |= USART_CR1_TE;
	USART2->CR1 |= USART_CR1_RE;
	USART2->CR1 |= USART_CR1_UE;

}



/**
 * @brief     This function connect UART2 with putchar
 *
 * @param[in]  NA
 * @param[out] ch, character sent
 *
 */
int __io_putchar(int ch)
{
    while(!(USART2->ISR & USART_ISR_TXE)); // wait until TX buffer empty
    USART2->TDR = (uint8_t)ch;             // send char
    return ch;
}

