/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include <stm32f091xc.h>
#include "UART_Init.h"
#include "Gesture_sensor.h"
#include "Bluetooth_JDY31.h"


#define TEST_CODE
#define SEN13162_DEVICE_ID 0x10
#define last_detected_gesture 0x04
#define sensor_model_id 0xFF
#define reg_map_ver 0xFE
#define CLEAR 0
#define RIGHT_SWIPE 0x1
#define LEFT_SWIPE 0x2
#define DATA_READY 0
#define SET 1
////UART

#define F_SYS_CLK (48000000)
#define SYSTICK_CLK_DIV      8      // SysTick clock division factor
#define MS_TO_SYSTICK    (((F_SYS_CLK / SYSTICK_CLK_DIV) / 1000U))
#define SYSTICK_PRIORITY (3)


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/**
 *
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

	/* Configure the system clock */
	SystemClock_Config();

	//BlueTooth Initialization
	Init_USART1();
	//TeraTerm Initialization for debugging
	Init_USART2();
	//ZX SensorInitialization
	I2C_Init();

	/*********************************************************************/
	//To Disable the Testing for Bluetooth and ZX Sensor Comment the above definition
	//#define TEST_CODE in main.c
	//*****************************************************************/
#ifdef TEST_CODE

	//*****************Test BlueTooth******************//

	uart1_print("Hello");

	/*Ideally AT commands should have worked but the tests are not passing
	The Bluetooth is just receiving the data through serial
	Only confirmation that bluetooth is working is through connecting to different laptop bluetooth
	And when trying to disconnect and connect it is sending data*/


	uart1_print("AT\r\n");
	uart1_print("AT+NAME\r\n");
	uart1_print("AT+VERSION\r\n");

    //************************************************//

	//******************Test Gesture*******************//


	//Register Map: GestureSense XZ01 Sensor I2C Register Map
	uint8_t gesture_x = CLEAR;
    I2C_ReadReg(SEN13162_DEVICE_ID,sensor_model_id, &gesture_x, SET);

    //As per Datasheet its MODEL ID is 1
    printf("Model ID %d \r\n",gesture_x);
    I2C_ReadReg(SEN13162_DEVICE_ID,reg_map_ver, &gesture_x, SET);

    //As per Datasheet the Register Map version is 1
    printf("Register Map Version %d \r\n",gesture_x);

    //*************************************************//
#endif
#ifdef DEBUG
	printf("ZX Sensor Ready.\r\n");
#endif
	uart1_print("ZX Sensor Ready.\r\n");
		while(1)
		{
			uint8_t gesture = CLEAR;

			if(Gesture_DataReady() == DATA_READY)
			{
#ifdef DEBUG
				printf("detected motion\r\n");
#endif
				int sensor_active = SET;
				if(sensor_active == SET)
				{
					I2C_ReadReg(SEN13162_DEVICE_ID,last_detected_gesture, &gesture, SET);
                	if(gesture == RIGHT_SWIPE)
                	{
#ifdef DEBUG
                		printf("Right Swipe\r\n");
#endif
                		uart1_print("Right Swipe\r\n");

                	}
                	else if(gesture == LEFT_SWIPE)
                	{
#ifdef DEBUG
                		printf("Left Swipe");
#endif
                		uart1_print("Left Swipe\r\n");
                	}
				}
				else
				{

				}
			}
		}
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

