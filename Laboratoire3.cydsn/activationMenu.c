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
volatile bool infoActif = false;
volatile bool rcMinActif = false;
volatile bool rcMaxActif = false;
volatile bool SpO2MinActif = false;
volatile bool courbeActif = false;
volatile bool choixAlarme = false;
volatile bool DELirActif = false;
volatile bool DELrActif = false;
volatile bool entreeProgramme = true;
volatile uint8_t hauteurCercle=17;
volatile uint8_t options=0;
volatile const uint8_t NBOPTIONS =8;

// Variable capSense:
volatile uint16_t bouton0=0;
volatile uint16_t bouton1=0;
volatile uint8_t currentBouton0=7;
volatile uint8_t currentBouton1=7;
volatile uint8_t currentOption=80;

// Variables options:
volatile uint8_t rcMin=76;
volatile uint8_t rcMax=120;
volatile uint8_t SPo2Min=99;
volatile uint16_t courantDELi= 30;
volatile uint16_t courantDELr = 30;
volatile bool grapheIr =true;
volatile bool grapheR = false;
volatile bool alarmeActive = false;
volatile uint16_t copieBouton0;
volatile uint16_t copieBouton1;

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
   
    Cy_SysInt_Init(&SW2_isr_cfg, isr_bouton);
    NVIC_ClearPendingIRQ(SW2_isr_cfg.intrSrc);
    NVIC_EnableIRQ(SW2_isr_cfg.intrSrc);
}

void DesactiverPage(void) {
   
        infoActif = false;
        rcMinActif = false;
        courbeActif =false;
        choixAlarme =false;
        rcMaxActif =false;
        SpO2MinActif =false;
        DELirActif =false;
        DELrActif =false;
    
}
void isr_bouton(void){
    
    nbSW2++;
    DesactiverPage();
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
    
    if (menuActif == true && infoActif == false && rcMinActif == false && courbeActif == false && choixAlarme == false && rcMaxActif == false && SpO2MinActif == false && DELrActif == false && DELirActif == false) {
        if (oldMenuActif != menuActif) {
        menuUpdate = true;
        oldMenuActif = menuActif;
        }
        GUI_Clear();
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("Activer /  Desactiver alarme", 40, 15);
        GUI_DispStringAt("Obtenir les informations", 40, 35);
        GUI_DispStringAt("Definir les bornes : ", 40, 55);
        GUI_DispStringAt("Rythme cardiaque minimal", 130, 55);
        GUI_DispStringAt("Rythme cardiaque maximal", 130, 75);
        GUI_DispStringAt("SpO2 minimal", 130, 95);
        GUI_DispStringAt("Changer courbe saturation", 40, 115);
        GUI_DispStringAt("Modifier courant : ", 40, 135);
        GUI_DispStringAt("DELir", 125, 135);
        GUI_DispStringAt("DELr", 125, 155);
        GUI_DrawCircle(25, hauteurCercle, 3);
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
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("Ecran Principal", 10, 160);
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
    char bufferRcMin[3];
    char bufferRcMax[3];
    char bufferSpO2[3];
    char bufferDELi[5];
    char bufferDELr[5];
    
    sprintf(bufferRcMin, "%d", rcMin);
    sprintf(bufferRcMax, "%d", rcMax);
    sprintf(bufferSpO2, "%d", SPo2Min);
    sprintf(bufferDELi, "%d", courantDELi);
    sprintf(bufferDELr, "%d", courantDELr);
    
   GUI_Clear();
   GUI_SetFont(GUI_FONT_8_1);
   GUI_SetTextAlign(GUI_TA_LEFT);

   GUI_DispStringAt("Informations", 100,15);
   GUI_DispStringAt("Rythme cardiaque : ", 20, 55);
   GUI_DispStringAt(bufferRcMin, 115, 55);
   GUI_DispStringAt(" a ", 135, 55);
   GUI_DispStringAt(bufferRcMax, 150, 55);
   GUI_DispStringAt(" batt/sec ", 170, 55);

   GUI_DispStringAt("SpO2 minimal : ", 20, 80); 
   GUI_DispStringAt(bufferSpO2, 100, 80);
   GUI_DispStringAt(" % ", 120, 80);

   GUI_DispStringAt("Courant DELi : ", 20, 105);
   GUI_DispStringAt(bufferDELi, 100, 105);
   GUI_DispStringAt(" mV ", 120, 105);

   GUI_DispStringAt("Courant DELr : ", 20, 130);
   GUI_DispStringAt(bufferDELr, 100, 130);
   GUI_DispStringAt(" mV ", 120, 130);

   if (alarmeActive == false) {
    GUI_DispStringAt("Aucune alarme n'est activee ", 20, 155);
    }
   else {
    GUI_DispStringAt("L'alarme est activee ", 20, 150);
}
   UpdateDisplay(CY_EINK_FULL_4STAGE, true);

}
void afficherRCMin()
{
    
        GUI_Clear();
        char bufferRcMin[3];
        sprintf(bufferRcMin, "%d", rcMin);
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("Definir rythme cardiaque minimal", 60, 60);
        GUI_SetFont(GUI_FONT_32_1);
        GUI_DispStringAt(bufferRcMin, 110, 75);
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);

        
}
void afficherRCMax()
{
        GUI_Clear();
        char bufferRcMax[3];
        sprintf(bufferRcMax, "%d", rcMax);
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("Definir rythme cardiaque maximal", 60, 60);
        GUI_SetFont(GUI_FONT_32_1);
        GUI_DispStringAt(bufferRcMax, 110, 75);
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}
void afficherSpO2Min()
{
        GUI_Clear();
        char bufferSpO2[3];
        sprintf(bufferSpO2, "%d", SPo2Min);
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("Definir SpO2 minimal", 70, 60);
        GUI_SetFont(GUI_FONT_32_1);
        GUI_DispStringAt(bufferSpO2, 110, 75);
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}

void afficherChoixCourbe()
{
        GUI_Clear();
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("Votre choix a bien ete enregistre.", 50, 55);
        if (grapheIr == true) {
            GUI_DispStringAt("La courbe rouge sera affichee.", 55, 80);
            grapheIr =false;
        }
        else {
            GUI_DispStringAt("La courbe infrarouge sera affichee.", 45, 80);
            grapheIr = true;
        }
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}
void afficherChoixAlarme()
{
        GUI_Clear();
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        if (alarmeActive == true) {
            GUI_DispStringAt("L'alarme a ete desactivee", 55, 80);
            alarmeActive =false;
        }
        else {
            GUI_DispStringAt("L'alarme a ete activee", 55, 80);
            alarmeActive = true;
        }
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}
void afficherDELir()
{
        GUI_Clear();
        char bufferDELir[3];
        sprintf(bufferDELir, "%d", courantDELi);
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("DELir", 110, 60);
        GUI_SetFont(GUI_FONT_32_1);
        GUI_DispStringAt(bufferDELir, 110, 75);
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}

void afficherDELr()
{
        GUI_Clear();
        char bufferDELr[3];
        sprintf(bufferDELr, "%d", courantDELr);
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("DELr", 110, 60);
        GUI_SetFont(GUI_FONT_32_1);
        GUI_DispStringAt(bufferDELr, 110, 75);
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}
void copierValeurBouton (void) {
    
    copieBouton0 = bouton0;
    copieBouton1 = bouton1;
}

void actionSensor4 (void) {
    switch (options) {
        case 0 : choixAlarme =true; afficherChoixAlarme();
            break;
        case 1 : infoActif = true; afficherInfo();
            break;
        case 2 : rcMinActif = true; copierValeurBouton(); afficherRCMin();
            break;
        case 3 : rcMaxActif =true; copierValeurBouton(); afficherRCMax();
            break ;
        case 4 : SpO2MinActif =true; copierValeurBouton(); afficherSpO2Min();
            break ;
        case 5: courbeActif= true; afficherChoixCourbe();
            break;
        case 6: DELirActif=true; copierValeurBouton(); afficherDELir();
            break;
        case 7: DELrActif = true; copierValeurBouton(); afficherDELr();
            break;
    }
}
void actionSensor0 (void) {
    DesactiverPage();
    menuUpdate= true;
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
    hauteurCercle = (16 + options*20) ;
    
 }

void changerValeur (void) {
    
    if (copieBouton0 != bouton0 && currentBouton0 !=bouton0) {
        currentBouton0 = bouton0;
        if (rcMinActif == true){
            rcMin--;
            afficherRCMin();
        }
         if (rcMaxActif == true){
            rcMax--;
            afficherRCMax();
        }
        if (SpO2MinActif ==true) {
            SPo2Min --;
            afficherSpO2Min();
        }
        if (DELirActif ==true) {
            if (courantDELi <= 4){
                courantDELi =0;
                afficherDELir();
            }
            else {
            courantDELi = courantDELi-5;
            afficherDELir();
            }
        }
        if (DELrActif ==true) {
            if (courantDELr <= 4){
                courantDELr =0;
                afficherDELr();
            }
            else {
            courantDELr = courantDELr-5;
            afficherDELr();
            }
        }
    
    }
     if (copieBouton1 != bouton1 && currentBouton1 != bouton1) {
        currentBouton1 = bouton1;
        if (rcMinActif == true){
            rcMin++;
            afficherRCMin();
        }
        if (rcMaxActif == true){
            rcMax++;
            afficherRCMax();
        }
        if (SpO2MinActif ==true) {
            SPo2Min ++;
            afficherSpO2Min();
        }
        if (DELirActif ==true) {
            if (courantDELi >= 46){
                courantDELi =50;
                afficherDELir();
            }
            else {
            courantDELi = courantDELi+5;
            afficherDELir();
            }
        }
         if (DELrActif ==true) {
            if (courantDELr >= 46){
                courantDELr =50;
                afficherDELr();
            }
            else {
            courantDELr = courantDELr+5;
            afficherDELr();
            }
        }
    }
    
}

void choixCurseur(void) {
    if (rcMinActif == false && rcMaxActif == false && SpO2MinActif == false && DELirActif ==false && DELrActif==false) {
        deplacerCurseur();
    }
    else {
        changerValeur();
    }
    
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
        CapSense_ProcessAllWidgets();
           
            if(CapSense_IsWidgetActive(CapSense_BUTTON0_WDGT_ID)){
             bouton0++;
            }
        
            if(CapSense_IsWidgetActive(CapSense_BUTTON1_WDGT_ID)){
               bouton1++;
            }
            if (CapSense_IsWidgetActive(CapSense_SNS0_WDGT_ID)) {
                actionSensor0();
            }
            if (CapSense_IsWidgetActive(CapSense_SNS4_WDGT_ID)) {
                actionSensor4();
            }
            
        
        CapSense_UpdateAllBaselines();
        CapSense_ScanAllWidgets();
        choixCurseur();
        
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
        
    }


/* [] END OF FILE */
