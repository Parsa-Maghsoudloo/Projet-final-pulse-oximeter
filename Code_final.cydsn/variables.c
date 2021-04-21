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
#include "variables.h"
#include "semphr.h"


static float32_t buff_filtered_IR[1000];
static float32_t buff_filtered_RED[1000];
float32_t vecteur_RED[2000];
float32_t vecteur_IR[2000];
float32_t buff_filtered_IR_copy[200] = {0};
float32_t buff_filtered_RED_copy[200] = {0};


uint8_t capteurAdresse = 0b1010111;
uint8_t fifoAdresse = 0x07;

SemaphoreHandle_t semaph;
SemaphoreHandle_t graph_semph;
uint8_t test_1[1];
uint8_t test_2[1];

TaskHandle_t SpO2_Handle;
TaskHandle_t trait_Handle;

float SpO2 = 0;
volatile uint8_t BPM = 0;
volatile uint16_t read = 0;
volatile float32_t minIR = 100000;
volatile float32_t maxIR = -100000;
volatile float32_t minRED = 100000;
volatile float32_t maxRED = -100000;

uint32_t compteur = 0;
uint8_t iterations = 0;

volatile uint8_t courantDELi_config = 150;
volatile uint8_t courantDELr_config = 150;

volatile bool menuActif=true;
volatile bool alarmeActive = false;
volatile bool accelerometre = false;


/* [] END OF FILE */
