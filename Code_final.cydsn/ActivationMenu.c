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
#include "ActivationMenu.h"
#include "affichage.h"
#include "variables.h"
#include "capteur_MAX.h"

// variable venant du laboratoire 3, permettant l'afichage
uint8 imageBufferCache[CY_EINK_FRAME_SIZE] = {0};

// Variables pour le menu:
volatile int nbSW2=0; // nbSW2 compte le nombre de fois que l'on entre dans le menu.
volatile SemaphoreHandle_t bouton_semph;
SemaphoreHandle_t graph_semph;

// Variables permettant de savoir quelle option est active.
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
volatile bool entreeProgramme = true; // Permet d'entrer dans le menu au début.
volatile uint8_t hauteurCercle=17;
volatile uint8_t options=0;
volatile const uint8_t NBOPTIONS =8;
volatile const uint8_t LARGEURGRAPHE =116;


// Variable capSense:
volatile uint16_t bouton0=0;
volatile uint16_t bouton1=0;
volatile uint8_t currentBouton0=7;
volatile uint8_t currentBouton1=7;
volatile uint8_t currentOption=0;

// Variables options:
volatile uint8_t rcMin=50;
volatile uint8_t rcMax=175;
volatile uint8_t SPo2Min=90;
volatile uint8_t courantDELi= 30;
volatile uint8_t courantDELr = 30;
volatile bool grapheIr =true;
volatile bool bypassAlarmeActive = false;
volatile uint16_t copieBouton0;
volatile uint16_t copieBouton1;

// Cette fonction sera appelée à l'entrée du main et initialise le GUI, les interruptions, le EINK et les variables transmettant les sémaphores.
void initialisation (void) {
    
    // Variables pour transmission sémaphore
    bouton_semph = xSemaphoreCreateBinary();
    graph_semph = xSemaphoreCreateBinary();
    
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
    
    // initialisation interruption bouton SW2.
    Cy_SysInt_Init(&SW2_isr_cfg, isr_bouton);
    NVIC_ClearPendingIRQ(SW2_isr_cfg.intrSrc);
    NVIC_EnableIRQ(SW2_isr_cfg.intrSrc);
}

// Cette fonction permet de passer à faux toutes les pages d'options actives.
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

// Interruption appelée lorsqu'on appuie sur le bouton SW2, elle envoie un sémaphore qui sera pris par activerMenu().
void isr_bouton(void){
    
    nbSW2++;
    DesactiverPage();
    // On désactive les pages pour que le menu puisse s'afficher si l'interruption est déclenchée alors que l'usager était sur une page d'option.
    xSemaphoreGiveFromISR(bouton_semph,NULL);
    Cy_GPIO_ClearInterrupt(SW2_PORT, SW2_NUM );
    NVIC_ClearPendingIRQ(SW2_isr_cfg.intrSrc);
}

// Cette tâche détermine si c'est le menu ou la page d'option qui devrait être appelée. Elle prend le sémaphore envoyé par isr_bouton().
void activerMenu() {   
    for (;;) {
    
    // Ajout d'un délais pour le debouncing.
    vTaskDelay(pdMS_TO_TICKS(50));
    if (xSemaphoreTake(bouton_semph, 0)==true) {
        // Usage d'un modulo pour qu'une fois sur deux ce soit le menu et l'autre fois la page principale qui soit affiché, le tout en alternance.
        if (nbSW2 % 2 !=0) {
            sensorConfiguration(0b01000000, 0b00000000, 0b00010000, 0b00000000, 0b00000011, 0b01100000, 0b00000100, 0b00000011, courantDELr_config, courantDELi_config, 0b00000010);
            menuActif = false;
        }
        else {
            if(nbSW2 > 0){
                iterations = 0;
                BPM = 0;
                SpO2 = 0;
                compteur = 0;
                accelerometre = false;
                sensorConfiguration(0,0,0,0,0b01000000,0,0,0,0,0,0);
            }
            menuActif=true;
        }     
    }
    }
}

// Fonction fournie par PSOC pour que l'affichage se fasse sur l'écran.
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

// Fonction fournie par PSOC pour que le contenu actuel de l'écran s'efface.
void ClearScreen(void)
{
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}

// Fonction appelée par afficherEcranPrincipal() permettant de dessiner la courbe de saturation voulue.
void DessinerGraphique(float32_t max, float32_t min){
  
    int16_t signalAffiche[200]={};
    
    // Pour déterminer le facteur d'échelle, on calcul max-min pour déterminer l'amplitude des valeurs, 
    //puis on divise par le nombre de pixels en hauteur (LARGEURGRAPHE) qui seront utilisés pour afficher la courbe.
    volatile float32_t facteurEchelle = (max-min)/(float32_t)LARGEURGRAPHE;
    
    for (int i=0; i<200 ; i++) {
        if(grapheIr == true){
            // On prend la valeur issue du traitement et on soustrait la valeur minimale, pour que la plus petite valeur soit au pixel le plus bas et on divise par le facteur d'échelle.
            signalAffiche[i] = (int16_t)((buff_filtered_IR_copy[i]-min)/facteurEchelle);
        }
        else{
            signalAffiche[i] = (int16_t)((buff_filtered_RED_copy[i]-min)/facteurEchelle);
        }
    }
    GUI_DrawGraph(signalAffiche, 200, 30, 24);
    
}

// Cette tâche permet d'afficher le menu.
void afficherMenu()
{
    
   for(;;) {
    
    // Vérification qu'aucune page d'option n'est activée, la page menu peut seulement s'activer si toutes les options sont à false.
    if (menuActif == true && infoActif == false && rcMinActif == false && courbeActif == false && choixAlarme == false && rcMaxActif == false && SpO2MinActif == false && DELrActif == false && DELirActif == false) {
        // Changement du flag menuUpdate à chaque fois que l'on active le menu depuis l'interruption.
        if (oldMenuActif != menuActif) {
        menuUpdate = true;
        oldMenuActif = menuActif;
        }
        GUI_Clear();
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("Desactiver alarme", 40, 15);
        GUI_DispStringAt("Obtenir les informations", 40, 35);
        GUI_DispStringAt("Definir les bornes : ", 40, 55);
        GUI_DispStringAt("Rythme cardiaque minimal", 130, 55);
        GUI_DispStringAt("Rythme cardiaque maximal", 130, 75);
        GUI_DispStringAt("SpO2 minimal", 130, 95);
        GUI_DispStringAt("Changer courbe saturation", 40, 115);
        GUI_DispStringAt("Modifier courant : ", 40, 135);
        GUI_DispStringAt("DELir", 125, 135);
        GUI_DispStringAt("DELr", 125, 155);
        // Affichage du curseur, la valeur d'hauteurCercle est déterminée dans deplacerCurseur() à partir de l'option où doit se trouver le curseur.
        GUI_DrawCircle(25, hauteurCercle, 3);
        
        // L'affichage se rafrachit uniquement s'il y a eu une modification dans le menu.
        if (menuUpdate == true) {
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
        vTaskDelay(pdMS_TO_TICKS(50));
        menuUpdate = false;
            }
    }
    vTaskDelay(pdMS_TO_TICKS(500));
    }

}

// Cette tache permet d'afficher l'écran principal (la page avec la courbe et les mesures).
void afficherEcranPrincipal()
{
   for (;;) {
       if (menuActif == false){
            if (oldMenuActif != menuActif) {
                menuUpdate = true;
                GUI_Clear();
                oldMenuActif = menuActif;
            }
            
            if (xSemaphoreTake(graph_semph, pdMS_TO_TICKS(500))==true && alarmeActive == false){
                ClearScreen();
                char rc[65];
                char spo2[65];
                uint8_t spo2_graph = (uint8_t)SpO2;

                sprintf(rc, "%d", BPM);
                sprintf(spo2, "%d", spo2_graph);

                // On vérifie si l'alarme est active.
                activerAlarme();
                // Si l'alarme est active et qu'elle n'a pas été désactivée alors la page d'alarme s'affiche.
                if (BPM != 0 && SpO2 != 0 && alarmeActive == true && bypassAlarmeActive == false) {
                    GUI_SetTextAlign(GUI_TA_LEFT);
                    GUI_SetFont(GUI_FONT_8_1);
                    GUI_SetTextAlign(GUI_TA_LEFT);

                    GUI_DispStringAt("Rythme cardiaque (batt/min) : ", 15, 20);
                    GUI_DispStringAt(rc, 155, 20);
                    GUI_DispStringAt("SpO2 (%):", 15, 40);
                    GUI_DispStringAt(spo2, 65, 40);
                    GUI_SetFont(GUI_FONT_32_1);
                    GUI_DispStringAt("L'alarme est active", 15, 60);
                    GUI_SetFont(GUI_FONT_16_1);
                    GUI_DispStringAt("Veuillez la desactiver pour poursuivre", 15, 90);
                    if (accelerometre == true) {
                        GUI_DispStringAt("Vous avez bouge trop rapidement", 15, 120);
                    }
                    if (SpO2 < SPo2Min && SpO2 != 0) {
                        GUI_DispStringAt("Le SpO2 est trop bas", 15, 120);

                    }
                    if (BPM < rcMin && BPM != 0) {
                        GUI_DispStringAt("Le rythme cardiaque est trop bas", 15, 150);
                    }
                    if (BPM > rcMax && BPM != 0) {
                        GUI_DispStringAt("Le rythme cardiaque est trop eleve", 15, 150);
                    }
                }
                
                // Sinon on affiche la courbe et les mesures de BPM et SpO2.
                else{    
                    GUI_SetFont(GUI_FONT_8_1);
                    GUI_SetTextAlign(GUI_TA_LEFT);
                    GUI_DispStringAt("Rythme cardiaque (batt/min) : ", 60, 146);
                    GUI_DispStringAt(rc, 200, 146);
                    GUI_DispStringAt("SpO2 (%):", 110, 162);
                    GUI_DispStringAt(spo2, 160, 162);
                    
                    
                    if (grapheIr ==true) {
                        GUI_SetFont(GUI_FONT_16_1);
                        GUI_DispStringAt("Courbe infrarouge", 80, 4);
                        DessinerGraphique(maxIR, minIR);
                    }
                    else {
                        GUI_SetFont(GUI_FONT_16_1);
                        GUI_DispStringAt("Courbe rouge", 90, 4);
                        DessinerGraphique(maxRED, minRED);
                    }
                }
                
                // On passe le flag à true, car la réception du sémaphore indique qu'il y aura un changement.
                menuUpdate = true;
                // Réinitialisation à false pour la prochaine acquisition.
                bypassAlarmeActive = false;
                    
                if (menuUpdate == true || entreeProgramme==true) {
                    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
                    vTaskDelay(pdMS_TO_TICKS(50));
                    menuUpdate = false;
                    entreeProgramme = false;
                }
            }
        }
    vTaskDelay(pdMS_TO_TICKS(500));
    }  
}

// Fonction permettant d'afficher l'option "Obtenir les informations".
void afficherInfo()
{
    char bufferRcMin[3];
    char bufferRcMax[3];
    char bufferSpO2[9];
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

   if (alarmeActive == false || bypassAlarmeActive == true) {
    GUI_DispStringAt("Aucune alarme n'est activee ", 20, 155);
    }
   else {
    GUI_DispStringAt("L'alarme est activee ", 20, 150);
}
   UpdateDisplay(CY_EINK_FULL_4STAGE, true);

}

//Fonction permettant d'afficher la fonction qui détermine la borne minimale du rythme cardiaque.
void afficherRCMin()
{
        GUI_Clear();
        char bufferRcMin[3];
        sprintf(bufferRcMin, "%d", rcMin);
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("Definir rythme cardiaque minimal", 60, 60);
        GUI_DispStringAt("Bouton0 : -                   Bouton1 : +", 50, 160);
        GUI_SetFont(GUI_FONT_32_1);
        GUI_DispStringAt(bufferRcMin, 110, 75);
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);

        
}

// Fonction permettant d'afficher la fonction qui détermine la borne maximale du rythme cardiaque.
void afficherRCMax()
{
        GUI_Clear();
        char bufferRcMax[3];
        sprintf(bufferRcMax, "%d", rcMax);
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("Definir rythme cardiaque maximal", 60, 60);
        GUI_DispStringAt("Bouton0 : -                   Bouton1 : +", 50, 160);
        GUI_SetFont(GUI_FONT_32_1);
        GUI_DispStringAt(bufferRcMax, 110, 75);
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}

// Fonction permettant d'afficher la fonction qui détermine la borne minimale du SpO2.
void afficherSpO2Min()
{
        GUI_Clear();
        char bufferSpO2[3];
        sprintf(bufferSpO2, "%d", SPo2Min);
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("Definir SpO2 minimal", 70, 60);
        GUI_DispStringAt("Bouton0 : -                   Bouton1 : +", 50, 160);
        GUI_SetFont(GUI_FONT_32_1);
        GUI_DispStringAt(bufferSpO2, 110, 75);
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}

// Fonction permettant de changer de courbe de saturation.
void afficherChoixCourbe()
{
        GUI_Clear();
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("Votre choix a bien ete enregistre.", 50, 55);
        
        // Vérification de la courbe active et changement du flag grapheIr pour afficher l'autre.
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

// Fonction permettant de désactiver l'alarme.
void afficherChoixAlarme()
{
        GUI_Clear();
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        
        // Vérification de l'état de l'alarme.
        if (alarmeActive == true) {
            GUI_DispStringAt("L'alarme a ete desactivee", 55, 80);
            bypassAlarmeActive = true;
            alarmeActive = false;
            accelerometre = false;
        }
        else {
            GUI_DispStringAt("L'alarme n'est pas active", 55, 80);
        }
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}

// Fonction permettant d'afficher la fonction qui détermine le courant envoyé dans la DEL infrarouge.
void afficherDELir()
{
        GUI_Clear();
        char bufferDELir[3];
        sprintf(bufferDELir, "%d", courantDELi);
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("DELir", 110, 60);
        GUI_DispStringAt("Bouton0 : -5                   Bouton1 : +5", 50, 160);
        GUI_SetFont(GUI_FONT_32_1);
        GUI_DispStringAt(bufferDELir, 110, 75);
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}

//Fonction permettant d'afficher la fonction qui détermine le courant envoyé dans la DEL rouge.
void afficherDELr()
{
        GUI_Clear();
        char bufferDELr[3];
        sprintf(bufferDELr, "%d", courantDELr);
        GUI_SetFont(GUI_FONT_8_1);
        GUI_SetTextAlign(GUI_TA_LEFT);
        GUI_DispStringAt("DELr", 110, 60);
        GUI_DispStringAt("Bouton0 : -                   Bouton1 : +", 50, 160);
        GUI_SetFont(GUI_FONT_32_1);
        GUI_DispStringAt(bufferDELr, 110, 75);
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}

// Fonction permettant de créer une copie du nombre d'incrémentation de chaque bouton.
void copierValeurBouton (void) {
    
    copieBouton0 = bouton0;
    copieBouton1 = bouton1;
}

// Fonction qui est appelée lorsque l'usage appuie sur le bouton SLD4. 
// On vérifie à quelle option le curseur de l'usager se trouve, puis on appelle la fonction correspondante.
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

// Fonction qui est appelée lorsque l'usage appuie sur le bouton SLD0. 
// En appelant DesactiverPage() on passe le flag de toutes options à false ce qui permet d'afficher le menu.
void actionSensor0 (void) {
    DesactiverPage();
    menuUpdate= true;
}

// Cette fonction est appelée lorsque l'usager se trouve dans le menu et qu'il a appuyé sur le bouton 0 ou 1.
void deplacerCurseur(void) {
    
    // On vérifie sur quel bouton il a appuyé et on incrémente currentOption en conséquence.
    // On passe le flage menuUpdate à true pour que l'écran se rafraichisse. 
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
    
    // Utilisation d'un modulo pour que la valeur options correspondant à la position du curseur soit toujour entre 0 et (NBOPTIONS -1).
    options = currentOption % NBOPTIONS  ;
    // La valeur de la variable hauteurCercle utilisée dans afficherMenu() est déterminée ici à partir de l'option active.
    // 16 est le nombre de pixels entre le haut de l'écran et la première option et 20 est la distance entre chaque option.
    hauteurCercle = (16 + options*20) ;    
 }

// Cette fonction est appelée lorsque l'usager est dans une page d'option demandant de sélectionner une valeur.
// On commence par vérifier qu'elle bouton a été activé par l'usager, puis on vérifie sur quel page d'option il se trouve.
void changerValeur (void) {
    
    if (copieBouton0 != bouton0 && currentBouton0 !=bouton0) {
        currentBouton0 = bouton0;
        if (rcMinActif == true){
            if ( rcMin <= 0) {
             rcMin=0;
            }
            else {
                rcMin--;
            }
            afficherRCMin();
        }
         if (rcMaxActif == true){
            if ( rcMax <= rcMin) {
            rcMax = rcMin;
            }
            else {
                rcMax--;
            }
            afficherRCMax();
        }
        if (SpO2MinActif ==true) {
            SPo2Min = SPo2Min - 1;
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
        courantDELi_config = 5*courantDELi;
        courantDELr_config = 5*courantDELr;
    }
     if (copieBouton1 != bouton1 && currentBouton1 != bouton1) {
        currentBouton1 = bouton1;
        if (rcMinActif == true){
            if ( rcMin >= rcMax) {
                rcMin=rcMax;
            }
            else {
                rcMin++;
            }
            afficherRCMin();
        }
        if (rcMaxActif == true){
            rcMax++;
            afficherRCMax();
        }
        if (SpO2MinActif ==true) {
            if ( SPo2Min >= 99.9) {
            SPo2Min = 100.0;
            }
            else {
                SPo2Min = SPo2Min + 1;
            }
            afficherSpO2Min();
            
        }
        if (DELirActif ==true) {
            if (courantDELi >= 46){
                courantDELi =50;
            }
            else {
            courantDELi = courantDELi+5;
            }
            afficherDELir();
            
        }
         if (DELrActif ==true) {
            if (courantDELr >= 46){
                courantDELr =50;
            }
            else {
            courantDELr = courantDELr+5;
            }
            afficherDELr();
        }
        courantDELi_config = 5*courantDELi;
        courantDELr_config = 5*courantDELr;
    }
    
    
}

//Cette fonction permet d'appler la bonne fonction après que l'usager ait appuyé sur le bouton 0 ou 1.
// S'il est dans le menu (donc tous les flags des pages d'options sont faux) alors deplacerCurseur() sera appele sinon c'est changerValeur() qui sera appelée.
void choixCurseur(void) {
    if (rcMinActif == false && rcMaxActif == false && SpO2MinActif == false && DELirActif ==false && DELrActif==false) {
        deplacerCurseur();
    }
    else {
        changerValeur();
    }
}

// Cette tâche permet de vérifier si l'usager a appuyé sur l'un des boutons du capSense.
void capSense_task(void)
{
    // initialisation
    if (nbSW2 ==0) {
            CapSense_Start();
            CapSense_ScanAllWidgets();
        }
    for(;;)
    {
        
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

// Cette fontion active l'alarme si le rythme cardiaque ou le SpO2 est hors des bornes ou si l'accéléromètre indique un mouvement trop brusque de l'usager.
void activerAlarme(void) {
    if ( SpO2 < SPo2Min || BPM < rcMin || BPM > rcMax || accelerometre == true) {
        alarmeActive = true;
    }
}
    


/* [] END OF FILE */