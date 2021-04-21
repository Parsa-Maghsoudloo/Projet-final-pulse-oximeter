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
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


uint8 imageBufferCache[CY_EINK_FRAME_SIZE];
void initialisation(void);
void isr_bouton(void);
void desactiverPage();
void activerMenu();
void UpdateDisplay(cy_eink_update_t updateMethod, bool powerCycle);
void ClearScreen(void);
void afficherMenu();
void afficherEcranPrincipal();
void afficherInfo();
void actionSensor4 (void);
void actionSensor0 (void);
void deplacerCurseur(void);
void capSense_task(void);
void activerAlarme (void);

/* [] END OF FILE */
