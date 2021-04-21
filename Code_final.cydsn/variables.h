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
#include "semphr.h"
#include "task.h"
#include "project.h"

/* Tableaux contenant les valeurs filtrées, les valeurs non-filtrées et une copie des deux dernières secondes d'acquisition pour le tracé des courbes */
static float32_t buff_filtered_IR[1000];
static float32_t buff_filtered_RED[1000];
float32_t vecteur_RED[2000];
float32_t vecteur_IR[2000];
float32_t buff_filtered_IR_copy[200];
float32_t buff_filtered_RED_copy[200];

/* Adresse du capteur MAX30102 et de son registre contenant les données */
uint8_t capteurAdresse;
uint8_t fifoAdresse;

/* Sémaphores pour la communication entre les tâches, et tableaux utilisés pour faire des tests d'acquisition à chaque itération */
SemaphoreHandle_t semaph;
SemaphoreHandle_t graph_semph;
uint8_t test_1[1];
uint8_t test_2[1];

/* Variables propres aux tâches d'acquisition et de traitement */
TaskHandle_t SpO2_Handle;
TaskHandle_t trait_Handle;

/* Variables modifiées dans le traitement, pour ensuite être utilisées pour l'affichage des données */
float SpO2;
volatile uint8_t BPM;
volatile uint16_t read;
volatile float32_t minIR;
volatile float32_t maxIR;
volatile float32_t minRED;
volatile float32_t maxRED;

/* Variables utilisées pour l'acquisition des données (nombre de données acquises depuis le changement d'itération, et nombre d'itérations) */
uint32_t compteur;
uint8_t iterations;

/* Valeurs de courant dans les DEL, qui sont utilisées pour configurer le capteur selon les demandes */
volatile uint8_t courantDELi_config;
volatile uint8_t courantDELr_config;

/* Variables booléennes utilisées pour la communication entre différentes tâches */
volatile bool menuActif;
volatile bool alarmeActive;
volatile bool accelerometre;


/* [] END OF FILE */
