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
#include "queue.h"
#include "activationMenu.h"

uint8 imageBufferCache[CY_EINK_FRAME_SIZE] = {0};

volatile int nbSW2=0;
volatile SemaphoreHandle_t bouton_semph;
volatile bool menuActif=false;
volatile bool oldMenuActif =false;
volatile bool menuUpdate = false;
volatile bool entreeProgramme = true;
volatile uint8_t hauteurCercle=17;
volatile uint8_t options=0;
volatile const uint8_t NBOPTIONS =5;

// Variable capSense:
volatile uint16_t bouton0=0;
volatile uint16_t bouton1=0;
volatile uint8_t currentBouton0=7;
volatile uint8_t currentBouton1=7;
volatile uint8_t currentOption=50;

void initialisation (void) {
     bouton_semph = xSemaphoreCreateBinary();
    
    __enable_irq();
    
    /* Initialize emWin Graphics */
    GUI_Init();

    /* Start the eInk display interface and turn on the display power */
    Cy_EINK_Start(20);
    Cy_EINK_Power(1);
  
    
    GUI_SetPenSize(1);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    ClearScreen();
   
    Cy_SysInt_Init(&SW2_isr_cfg, isr_bouton);
    NVIC_ClearPendingIRQ(SW2_isr_cfg.intrSrc);
    NVIC_EnableIRQ(SW2_isr_cfg.intrSrc);
}

void isr_bouton(void){
    
    nbSW2++;
    xSemaphoreGiveFromISR(bouton_semph,NULL);
    Cy_GPIO_ClearInterrupt(SW2_PORT, SW2_NUM );
    NVIC_ClearPendingIRQ(SW2_isr_cfg.intrSrc);
}


void activerMenu() {   
    for (;;) {
    vTaskDelay(pdMS_TO_TICKS(50));
    if (xSemaphoreTake(bouton_semph, 0)==true) {
        if (nbSW2 % 2 !=0) {
            
            menuActif = true;
        }
        else {
            menuActif=false;
            
        }     
    }
    }
}
void UpdateDisplay(cy_eink_update_t updateMethod, bool powerCycle)
{
    cy_eink_frame_t* pEmwinBuffer;

    /* Get the pointer to Emwin's display buffer */
    pEmwinBuffer = (cy_eink_frame_t*)LCD_GetDisplayBuffer();

    /* Update the EInk display */
    Cy_EINK_ShowFrame(imageBufferCache, pEmwinBuffer, updateMethod, powerCycle);

    /* Copy the EmWin display buffer to the imageBuffer cache*/
    memcpy(imageBufferCache, pEmwinBuffer, CY_EINK_FRAME_SIZE);
}

void ClearScreen(void)
{
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}
void afficherMenu()
{
    
   for(;;) {
    
    if (menuActif == true) {
        if (oldMenuActif != menuActif) {
        menuUpdate = true;
        GUI_Clear();
        oldMenuActif = menuActif;
        }
        GUI_Clear();
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("Obtenir les informations", 50, 15);
        GUI_DispStringAt("Definir les bornes", 50, 50);
        GUI_DispStringAt("Changer courbe saturation", 50, 85);
        GUI_DispStringAt("Activer /  Desactiver alarme", 50, 120);
        GUI_DispStringAt("Modifier courant", 50, 155);
        GUI_DrawCircle(25, hauteurCercle, 5);
        if (menuUpdate == true) {
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
        vTaskDelay(pdMS_TO_TICKS(50));
        menuUpdate = false;
            }
    }
        vTaskDelay(pdMS_TO_TICKS(500));
    }

}
void afficherEcranPrincipal()
{
   for (;;) {
   if (menuActif == false) {
    if (oldMenuActif != menuActif) {
        menuUpdate = true;
        GUI_Clear();
        oldMenuActif = menuActif;
    } 
        const int hauteur= (2*75 + 10);
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("Ecran Principal", 10, hauteur);
        if (menuUpdate == true || entreeProgramme==true) {
           UpdateDisplay(CY_EINK_FULL_4STAGE, true);
           vTaskDelay(pdMS_TO_TICKS(50));
           menuUpdate = false;
           entreeProgramme = false;
        }

    }
    vTaskDelay(pdMS_TO_TICKS(500));
    }  
    

}

void afficherInfo()
{
   const int hauteur= (2*75 + 10);
   GUI_SetFont(GUI_FONT_8_1);
   GUI_SetTextAlign(GUI_TA_LEFT);
   GUI_DispStringAt("Info", 60,hauteur);

}

void deplacerCurseur(void) {
  
    if (currentBouton0 != bouton0) {
        currentBouton0 = bouton0;
        currentOption ++;
        menuUpdate =true;
    }
    if (currentBouton1 != bouton1) {
        currentBouton1 = bouton1;
        currentOption--;
        menuUpdate =true;   
    }
    
    options = currentOption % NBOPTIONS  ;
    hauteurCercle = (17 + options*35) ;
    
 }

void capSense_task(void)
{
    for(;;)
    {
        if (nbSW2 ==0) {
            CapSense_Start();
            CapSense_ScanAllWidgets();
        }
        if (menuActif == true && !CapSense_IsBusy()) {
//        if (!CapSense_IsBusy()) {
        CapSense_ProcessAllWidgets();
           
        if(CapSense_IsWidgetActive(CapSense_BUTTON0_WDGT_ID)){
           bouton0++;
        }
        
        if(CapSense_IsWidgetActive(CapSense_BUTTON1_WDGT_ID)){
          bouton1++;
        }
        
        CapSense_UpdateAllBaselines();
        CapSense_ScanAllWidgets();
        deplacerCurseur();
        
        }
        vTaskDelay(pdMS_TO_TICKS(200));
        
    }
}

/* [] END OF FILE */
