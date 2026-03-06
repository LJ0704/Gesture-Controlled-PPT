/*
 * Bluetooth_JDY31.c
 *
 *  Created on: Dec 3, 2025
 *      Author: Likhita
 */

#include "Bluetooth_JDY31.h"

#define CLEAR_MODER 0x3
#define GPIOP_OUTPUT 0x2
#define GPIOPA9_TX_MODER 18
#define GPIOPA10_RX_MODER 20
#define CLEAR_AF 0xF
#define GPIOPA9_TX_AF 0x4
#define GPIOPA10_TX_AF 0x8
#define SET_AF_1 0x1

/**
 * @brief     This function initializes UART 1 in asynchronous mode, with data size setting as 8, no parity.
 *            The Baud rate is set to 9600Hz.
 *
 * @param[in]  NA
 *
 * @formula    USARTx_BRR = f busclock/ baud_rate
 *             f busclock = 24MHz
 *
 * @return     NA
 *
 * Reference : Deans Book Page : 268 Listing 8.14 Init_USART1 to enable interrupt and baud rate
 *             Deans Book Page : 263 Listing 8.8
 *             Reference Manual RM0091 Chapter 27 for register information
 *
 *
 */
void Init_USART1() {

	//Enable APB2 USART1
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	//Enable clock for GPIO A port
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	//User Manual : Page No: 38/68
	//GPIO A pin 9 - TX and 10 - RX in alternate function 1 (USART1)
	//Set mode field to 2 for alternate function
	GPIOA->MODER &= ~(CLEAR_MODER << GPIOPA9_TX_MODER);
	GPIOA->MODER &= ~(CLEAR_MODER << GPIOPA10_RX_MODER);
	GPIOA->MODER |= (GPIOP_OUTPUT << GPIOPA9_TX_MODER);
	GPIOA->MODER |= (GPIOP_OUTPUT << GPIOPA10_RX_MODER);

	GPIOA->AFR[1] &= ~((CLEAR_AF << GPIOPA9_TX_AF) | (CLEAR_AF << GPIOPA10_TX_AF));
	GPIOA->AFR[1] |=  ((SET_AF_1 << GPIOPA9_TX_AF) | (SET_AF_1 << GPIOPA10_TX_AF));


    //Setting BRR register for baud rate 9600 Hz
	USART1->BRR = F_USART_CLOCK/ baud_rate;

	//Enable transmitter and receiver and USART
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_RE;
	USART1->CR1 |= USART_CR1_UE;

}


/**
 * @brief     This function sends information over UART of Bluetooth Module
 *
 * @param[in]  d, data
 *
 * Reference : Deans Book Page : 268 Listing 8.14 Init_USART1 to enable interrupt and baud rate
 *             Deans Book Page : 263 Listing 8.8
 *             Reference Manual RM0091 Chapter 27 for register information
 *
 *
 */
void uart_send(uint8_t d)
{
    while(!(USART1->ISR & USART_ISR_TXE));
    USART1->TDR = d;
}

/**
 * @brief     This function receive information over UART of Bluetooth Module
 *
 * @param[in]  NA
 *
 * Reference : Deans Book Page : 268 Listing 8.14 Init_USART1 to enable interrupt and baud rate
 *             Deans Book Page : 263 Listing 8.8
 *             Reference Manual RM0091 Chapter 27 for register information
 *
 *
 */
uint8_t uart_recv(void)
{
    while(!(USART1->ISR & USART_ISR_RXNE));
    return USART1->RDR;
}

/**
 * @brief     This function send string information over UART of Bluetooth Module
 *
 * @param[in]  NA
 *
 */
void uart1_print(const char* s)
{
    while(*s)
    	uart_send(*s++);
}
