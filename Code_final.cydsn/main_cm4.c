/******************************************************************************
* File Name: main_cm4.c
*
* Version: 1.2
*
* Description: This file main application code for the CE223727 EmWin Graphics
*				library EInk Display 

********************************************************************************
*************MODIFIED by Christophe Cloutier-Tremblay.**************************
********************************************************************************
* 
*
* Hardware Dependency: CY8CKIT-028-EPD E-Ink Display Shield
*					   CY8CKIT-062-BLE PSoC6 BLE Pioneer Kit
*
******************************************************************************* 
* Copyright (2019), Cypress Semiconductor Corporation. All rights reserved. 
******************************************************************************* 
* This software, including source code, documentation and related materials 
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its 
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent 
* protection (United States and foreign), United States copyright laws and 
* international treaty provisions. Therefore, you may use this Software only 
* as provided in the license agreement accompanying the software package from 
* which you obtained this Software (“EULA”). 
* 
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive, 
* non-transferable license to copy, modify, and compile the Software source 
* code solely for use in connection with Cypress’s integrated circuit products. 
* Any reproduction, modification, translation, compilation, or representation 
* of this Software except as specified above is prohibited without the express 
* written permission of Cypress. 
* 
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product”). By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
********************************************************************************/




/********************************************************************************
Note : Le UART (DEBUG_UART) n'est pas utilisé dans le code, mais est tout de même
présent dans le module pour faire des tests. Nous le laissons au cas où vous
voudriez faire des tests de votre côté.
*********************************************************************************/



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
#include "affichage.h"
#include "semphr.h"
#include "variables.h"
#include "filtre.h"
#include "motion_task.h"
#include "ActivationMenu.h"
#include <arm_math.h>
#include <core_cm4.h>

#define TASK_MOTION_SENSOR_STACK_SIZE   (configMINIMAL_STACK_SIZE)

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */    
    
    I2C_Start();
    DEBUG_UART_Start();
    semaph = xSemaphoreCreateBinary();
    
    initialisation();
    
    /* Création des tâches */
    xTaskCreate(activerMenu, "Activation du menu", configMINIMAL_STACK_SIZE, NULL, 4, NULL);
    xTaskCreate(afficherMenu, "Affichage du menu", 300, NULL, 3, NULL);
    xTaskCreate(afficherEcranPrincipal, "Affichage de l'ecran", 300, NULL, 2, NULL);
    xTaskCreate((void*)capSense_task, "Bouton", 300, NULL, 3, NULL);
    
    xTaskCreate(acquisition, "Gestionnaire des taches", 300, NULL, 2, SpO2_Handle);
    xTaskCreate(Traitement, "Traitement", 300, NULL, 1, trait_Handle);
    xTaskCreate(Task_Motion, "Motion Task", TASK_MOTION_SENSOR_STACK_SIZE, NULL, 5, &xTaskHandleMotion);
    vTaskStartScheduler();
    
    
    for(;;)
    {
        
    }
}

/* [] END OF FILE */
