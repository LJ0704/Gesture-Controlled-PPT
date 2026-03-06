/*
 * Gesture_sensor.h
 *
 *  Created on: Dec 3, 2025
 *      Author: Likhita
 */

#ifndef INC_GESTURE_SENSOR_H_
#define INC_GESTURE_SENSOR_H_

#include <stm32f091xc.h>
void I2C_Init(void);
void I2C_WriteReg(uint8_t dev_adx, uint8_t reg_adx, uint8_t *bufp, uint16_t data_len);
void I2C_ReadReg(uint8_t dev_adx, uint8_t reg_adx, uint8_t *bufp, uint16_t data_len);
void DR_Pin_Init(void);
uint8_t Gesture_DataReady(void);

#endif /* INC_GESTURE_SENSOR_H_ */
