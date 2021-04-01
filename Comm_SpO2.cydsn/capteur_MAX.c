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

#include "project.h"
#include "GUI.h"
#include "pervasive_eink_hardware_driver.h"
#include "cy_eink_library.h"
#include "LCDConf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdlib.h>
#include "capteur_MAX.h"


uint8_t capteurAdresse1 = 0b1010111;


void sensorEcriture(uint8_t slave_addr, uint8_t register_addr, uint8_t *buffer1, uint16_t nb_bytes){

    Cy_SCB_I2C_MasterSendStart(I2C_HW, slave_addr, CY_SCB_I2C_WRITE_XFER, 0, &I2C_context);
    Cy_SCB_I2C_MasterWriteByte(I2C_HW, register_addr, 0, &I2C_context);
    
    for(int i = 0; i < nb_bytes; i++){
        Cy_SCB_I2C_MasterWriteByte(I2C_HW, buffer1[i], 0, &I2C_context);
    }
    
    Cy_SCB_I2C_MasterSendStop(I2C_HW, 0, &I2C_context);
}


void sensorLecture(uint8_t slave_addr, uint8_t register_addr, uint8_t *buffer1, uint8_t *buffer2, uint16_t nb_bytes, uint16_t position){
    
    Cy_SCB_I2C_MasterSendStart(I2C_HW, slave_addr, CY_SCB_I2C_WRITE_XFER, 0, &I2C_context);
    Cy_SCB_I2C_MasterWriteByte(I2C_HW, register_addr, 0, &I2C_context);
    Cy_SCB_I2C_MasterSendReStart(I2C_HW, slave_addr, CY_SCB_I2C_READ_XFER, 0, &I2C_context);
    
    for(int i = 0; i < (2*nb_bytes)-1; i++){
        if(i < 3){
            Cy_SCB_I2C_MasterReadByte(I2C_HW, CY_SCB_I2C_ACK, &buffer1[position+i], 0, &I2C_context);
        }
        else{
            Cy_SCB_I2C_MasterReadByte(I2C_HW, CY_SCB_I2C_ACK, &buffer2[position+i-3], 0, &I2C_context);
        }
    }
    
    Cy_SCB_I2C_MasterReadByte(I2C_HW, CY_SCB_I2C_NAK, &buffer2[position+nb_bytes-1], 0, &I2C_context);
    Cy_SCB_I2C_MasterSendStop(I2C_HW, 0, &I2C_context);
}


void sensorConfiguration(uint8_t int_enable, uint8_t average, uint8_t roll_over, uint8_t nb_restant, uint8_t sensor_mode, uint8_t range_contr, uint8_t SPS, uint8_t ADC_resol, uint8_t LED1_curr, uint8_t LED2_curr){
    
    uint8_t fifo_config = average|(roll_over|nb_restant);
    uint8_t mode_config = sensor_mode;
    uint8_t SpO2_config = range_contr|(SPS|ADC_resol);
    
    sensorEcriture(capteurAdresse1, 0x02, &int_enable, 1);
    sensorEcriture(capteurAdresse1, 0x08, &fifo_config, 1);
    sensorEcriture(capteurAdresse1, 0x09, &mode_config, 1);
    sensorEcriture(capteurAdresse1, 0x0A, &SpO2_config, 1);
    sensorEcriture(capteurAdresse1, 0x0C, &LED1_curr, 1);
    sensorEcriture(capteurAdresse1, 0x0D, &LED2_curr, 1);
    
}


/* [] END OF FILE */
