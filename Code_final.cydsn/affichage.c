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
#include "semphr.h"
#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"




void affichage_UART(float32_t valeur){

    char int_to_str[33];
    itoa(valeur, int_to_str, 10);
    DEBUG_UART_PutString(int_to_str);
}

void affichage_UART_int(uint32_t valeur){

    char int_to_str[33];
    itoa(valeur, int_to_str, 10);
    DEBUG_UART_PutString(int_to_str);
}




/* [] END OF FILE */