/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <stdlib.h>
#include <stdio.h>

void sensorEcriture(uint8_t slave_addr, uint8_t register_addr, uint8_t *buffer, uint16_t nb_bytes);

void sensorLecture(uint8_t slave_addr, uint8_t register_addr, uint8_t *buffer1, uint8_t *buffer2, uint16_t nb_bytes, uint16_t position);

void sensorConfiguration(uint8_t int_enable, uint8_t average, uint8_t roll_over, uint8_t nb_restant, uint8_t sensor_mode, uint8_t range_contr, uint8_t SPS, uint8_t ADC_resol, uint8_t LED1_curr, uint8_t LED2_curr);

/* [] END OF FILE */
