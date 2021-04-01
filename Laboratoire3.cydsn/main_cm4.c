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

#include "project.h"
#include "GUI.h"
#include "pervasive_eink_hardware_driver.h"
#include "cy_eink_library.h"
#include "LCDConf.h"
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "activationMenu.h"

//
//volatile int option =0;
//volatile int* currentOption;
//volatile uint16_t bouton0=0;
//volatile uint16_t bouton1=0;
//volatile uint16_t sliderPos=0;
//
//typedef enum
//{
//    BUTTON0_TOUCHED     = 0x00u,
//    BUTTON1_TOUCHED     = 0x01u,  
//    SLIDER_FLICK_LEFT   = 0x02u,
//    SLIDER_FLICK_RIGHT  = 0x03u,
//    NO_TOUCH            = 0x04u
//    
//}   touch_data_t; 
//QueueHandle_t touchDataQ;


//
//void capSense_task(void)
//{
//    touch_data_t previousTouchData = NO_TOUCH; 
//    touch_data_t currentTouchData;
//    uint32_t     sliderGesture;
//    uint32_t     gestureTimestamp = 0;
//    for(;;)
//    {
//        CapSense_ProcessAllWidgets();
//        
//        currentTouchData  = NO_TOUCH;
//           
//        if(CapSense_IsWidgetActive(CapSense_BUTTON0_WDGT_ID)){
//           if(previousTouchData != BUTTON0_TOUCHED)
//                {
//                    currentTouchData = BUTTON0_TOUCHED;
//                }
//        }
//        
//        if(CapSense_IsWidgetActive(CapSense_BUTTON1_WDGT_ID)){
//           if(previousTouchData != BUTTON1_TOUCHED)
//                {
//                    currentTouchData = BUTTON1_TOUCHED;
//                }
//        }
//        CapSense_UpdateAllBaselines();
//        CapSense_ScanAllWidgets();
//        if(currentTouchData != NO_TOUCH)
//            {
//                previousTouchData = currentTouchData;
//                /* Send the processed touch data */
//                xQueueOverwrite(touchDataQ, &currentTouchData);
//            }
//    }
//}



int main(void) {
    
    initialisation();
    
//
//    CapSense_Start();
//    CapSense_ScanAllWidgets();
    
//      xTaskCreate(waitForSW2Press, "Appuie Bouton", 400, NULL, 2,NULL);
      
      xTaskCreate(activerMenu, "ActiverMenu", configMINIMAL_STACK_SIZE, NULL, 1, 0);
      xTaskCreate(afficherMenu, "AfficherMenu", 400, NULL, 1, 0);
      xTaskCreate(afficherEcranPrincipal, "AfficherEcran", 400, NULL, 1, 0);
//      xTaskCreate((void*)capSense_task, "Bouton", 400, NULL, 1, 0);
    
      vTaskStartScheduler();
//    while(CapSense_IsBusy());
    
    for(;;)
    {          
            
    }
    
}



