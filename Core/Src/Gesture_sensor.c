/*
 * Gesture_sensor.c
 *
 *  Created on: Dec 3, 2025
 *      Author: Likhita
 */


#include "Gesture_sensor.h"

#define CLEAR_MODER 0x3
#define GPIOP_OUTPUT 0x2
#define GPIOPB8_MODER 16
#define GPIOPB9_MODER 18
#define CLEAR_AF 0xF
#define GPIOPB9_AF 0x4
#define GPIOPB8_AF 0x0
#define SET_AF_1 0x1
#define CLEAR 0
#define SET 1
#define GPIOPB8 8
#define GPIOPB9 9
#define GPIOPB8_PULL 16
#define GPIOPB9_PULL 18
#define TIMIN 0x00B01A4B

/**
 * @brief     This function used to initialize I2C for ZX Gesture Sensor
 *
 * @param[in]  NA
 *
 * Reference : Deans Book Page :  Listing 8.15 Code to initialize I2C1 peripheral and pins PB8 and PB9.
 */
void I2C_Init(void) {
 //  Clock gating for I2C1 and GPIO B
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
 //  GPIO B pin 8 and 9 in alternate function
	GPIOB->MODER &= ~(CLEAR_MODER << GPIOPB8_MODER);
	GPIOB->MODER &= ~(CLEAR_MODER << GPIOPB9_MODER);
	GPIOB->MODER |= (GPIOP_OUTPUT << GPIOPB8_MODER);
	GPIOB->MODER |= (GPIOP_OUTPUT << GPIOPB9_MODER);
// Alternate function
	GPIOB->AFR[1] &= ~(CLEAR_AF << GPIOPB8_AF);
	GPIOB->AFR[1] &= ~(CLEAR_AF << GPIOPB9_AF);
	GPIOB->AFR[1] |= (SET_AF_1 << GPIOPB8_AF);
	GPIOB->AFR[1] |= (SET_AF_1 << GPIOPB9_AF);
    //Open-drain
	GPIOB->OTYPER |= (SET << GPIOPB8) | (SET << GPIOPB8);
	 //No need software pull up, sensor has a pull up
	GPIOB->PUPDR &= ~((CLEAR_MODER << GPIOPB8_PULL) | (CLEAR_MODER << GPIOPB9_PULL));
	I2C1->CR1 = CLEAR; //  Default configuration, peripheral disabled
	I2C1->CR2 = CLEAR; //  Default configuration, 7 bit addressing
	I2C1->TIMINGR = TIMIN; //  about 71 kbaud

	// Enable I2C
	I2C1->CR1 |= I2C_CR1_PE;
}

/**
 * @brief     This function write data to ZX Gesture Sensor
 *
 * @param[in]  dev_adx, Address of ZX Gesture Sensor
 *             reg_adx, Register Address of what function to be performed
 *             data_len, Data Length
 *             *bufp, pointer to data to be written
 *
 * Reference : Deans Book Page :  Listing 8.16 Function to write data to I2C device register.
 */
void I2C_WriteReg(uint8_t dev_adx, uint8_t reg_adx, uint8_t *bufp, uint16_t data_len)
{

	I2C1->CR2 = (dev_adx << 1) | (0 << 10) | ((data_len+1) << 16) | I2C_CR2_START;
	// Send register address
	while (I2C1->CR2 & I2C_CR2_START){};
	    I2C1->TXDR = reg_adx;
	    //  Wait until transmitter empty
	     while (!(I2C1->ISR & I2C_ISR_TXE)){};
	    // Send data bytes
	    while (data_len--)
	    {
	        I2C1->TXDR = *bufp;
	        bufp++;
	        while (!(I2C1->ISR & I2C_ISR_TXE)){};
	    }

	    // STOP
	    I2C1->CR2 |= I2C_CR2_STOP;
}

/**
 * @brief     This function read data to ZX Gesture Sensor
 *
 * @param[in]  dev_adx, Address of ZX Gesture Sensor
 *             reg_adx, Register Address of what function to be performed
 *             data_len, Data Length
 *             *bufp, pointer to data to be read
 *
 * Reference : Deans Book Page :  Listing 8.17 Function to read data to I2C device register.
 */
void I2C_ReadReg(uint8_t dev_adx, uint8_t reg_adx, uint8_t *bufp, uint16_t data_len)
{
    // Write register address
	I2C1->CR2 = (dev_adx << 1) | (0 << 10) | (1 << 16) | I2C_CR2_START;
		// Send register address
		while (I2C1->CR2 & I2C_CR2_START){};
		    I2C1->TXDR = reg_adx;
		    //  Wait until transmitter empty
		     while (!(I2C1->ISR & I2C_ISR_TXE)){};

    // Restart + read
    I2C1->CR2 |= (dev_adx << 1) | (1 << 10) | (data_len << 16) | I2C_CR2_START;

    while (data_len--)
    {
        while (!(I2C1->ISR & I2C_ISR_RXNE));
        *bufp++ = I2C1->RXDR;
    }

    // STOP
    I2C1->CR2 |= I2C_CR2_STOP;
}

/**
 * @brief     This function initialize Data ready pin of ZX sensor to interrupt when Data is Available
 *
 * @param[in]  NA
 *
 * Reference : Data Sheet: XYZ Interactive Technologies, ZX SparkFun Sensor Datasheet
 */
void DR_Pin_Init(void)
{
    /* Enable GPIOA clock */
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    /* PA0 as input */
    GPIOA->MODER &= ~(3 << (0 * 2));
}

/**
 * @brief     This function reads the Data Ready pin on the ZX sensor, if ready HIGH if not LOW
 *
 * @param[in]  NA
 *
 * Reference : Data Sheet: XYZ Interactive Technologies, ZX SparkFun Sensor Datasheet
 */
uint8_t Gesture_DataReady(void)
{
    return (GPIOA->IDR & (1 << 0)) ? 0 : 1;
}

