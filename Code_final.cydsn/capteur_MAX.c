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
#include "variables.h"
#include "affichage.h"

/* Variables intermédiaires pour l'acquisition de données */
uint8_t red[3];
uint8_t ir[3];
uint32_t redSample;
uint32_t irSample;


/***************************************************************************
Fonction permettant d'écrire un ou plusieurs bytes dans un registre du
capteur MAX30102. L'argument "buffer" contient l'information à écrire.
****************************************************************************/
void sensorEcriture(uint8_t slave_addr, uint8_t register_addr, uint8_t *buffer, uint16_t nb_bytes){

    Cy_SCB_I2C_MasterSendStart(I2C_HW, slave_addr, CY_SCB_I2C_WRITE_XFER, 0, &I2C_context);
    Cy_SCB_I2C_MasterWriteByte(I2C_HW, register_addr, 0, &I2C_context);
    
    for(int i = 0; i < nb_bytes; i++){
        Cy_SCB_I2C_MasterWriteByte(I2C_HW, buffer[i], 0, &I2C_context);
    }
    
    Cy_SCB_I2C_MasterSendStop(I2C_HW, 0, &I2C_context);
}


/***************************************************************************
Fonction permettant de lire un ou plusieurs bytes dans un registre du
capteur MAX30102. L'information est stockée dans les tableaux "buffer1" et
"buffer2", pour séparer les données de la LED rouge et la LED infrarouge.
****************************************************************************/
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

/***************************************************************************
Fonction permettant de configurer le capteur MAX30102 selon plusieurs
options, définies dans le nom des paramètres.
****************************************************************************/
void sensorConfiguration(uint8_t int_enable, uint8_t average, uint8_t roll_over, uint8_t nb_restant, uint8_t sensor_mode, uint8_t range_contr, uint8_t SPS, uint8_t ADC_resol, uint8_t LED1_curr, uint8_t LED2_curr, uint8_t temp){
    
    uint8_t fifo_config = average|(roll_over|nb_restant);
    uint8_t mode_config = sensor_mode;
    uint8_t SpO2_config = range_contr|(SPS|ADC_resol);
    
    sensorEcriture(capteurAdresse, 0x02, &int_enable, 1);
    sensorEcriture(capteurAdresse, 0x08, &fifo_config, 1);
    sensorEcriture(capteurAdresse, 0x09, &mode_config, 1);
    sensorEcriture(capteurAdresse, 0x0A, &SpO2_config, 1);
    sensorEcriture(capteurAdresse, 0x0C, &LED1_curr, 1);
    sensorEcriture(capteurAdresse, 0x0D, &LED2_curr, 1);
    sensorEcriture(capteurAdresse, 0x03, &temp, 1);
}


/***************************************************************************
Tâche d'acquisition de données, dans laquelle on revient à chaque 8
millisecondes. Cette tâche vérifie chaque fois si une nouvelle donnée est
apparue dans le FIFO; si oui, elle lit cette valeur et la place dans un 
tableau de données.
****************************************************************************/
void acquisition(){
    
    for(;;){
        /* Cette tâche n'est active que si nous nous retrouvons dans la page de présentation des données */
        if(menuActif == false){
            uint8_t test[1];
            sensorLecture(capteurAdresse, 0x00, test_1, test, 0, 1);
            
            if(test[0] != 0)
            {
                compteur +=1;
                sensorLecture(capteurAdresse, fifoAdresse, red, ir, 3, 0);
                
                /* Regroupement des différents valeurs de 8 bits en valeurs cohérentes de 32 bits */
                redSample = (uint32_t)((((uint32_t)red[0])<<16)|(((uint32_t)red[1])<<8)|((uint32_t)red[2]));
                irSample = (uint32_t)((((uint32_t)ir[0])<<16)|(((uint32_t)ir[1])<<8)|((uint32_t)ir[2]));
                vecteur_RED[compteur-1] = (float32_t) redSample;
                vecteur_IR[compteur-1] = (float32_t) irSample;
                
                if(compteur%500 == 0){
                    if(iterations == 0){            //Seulement après 10 secondes lorsque c'est la première fois qu'on acquière des données
                        if(compteur >= 1000){
                            read = compteur - 500;
                            if(compteur%2000 == 0){
                                compteur = 0;
                                iterations += 1;
                            }
                            xSemaphoreGive(semaph);
                        }
                    }
                    else{
                        if(compteur%2000 == 0){
                            iterations += 1;
                            read = compteur - 500;
                            compteur = 0;
                            xSemaphoreGive(semaph);
                        }
                        else{
                            read = compteur - 500;
                            xSemaphoreGive(semaph);
                        }
                    }
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(8));
    }
}


/* [] END OF FILE */
