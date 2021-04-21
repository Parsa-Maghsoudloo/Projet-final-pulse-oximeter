/******************************************************************************
* File Name: motion_task.c
*
*******************************************************************************/

/* Header files include */
#include "motion_task.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "bmi160.h"
#include "i2cm_support.h"
#include "uart_debug.h"
#include "project.h"
#include "capteur_MAX.h"
#include "variables.h"

/* Fonction permettant à la LED orange de s'allumer pendant 500ms lorsqu'un mouvement est détecté */
void OrangeLedBlink(void){
    if(menuActif == false){
        Cy_GPIO_Write(LED_PORT, LED_NUM, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
        Cy_GPIO_Write(LED_PORT, LED_NUM, 1);
    }
}


/* Instance of BMI160 structure */
struct bmi160_dev sensor;

/* Motion task handle */
TaskHandle_t xTaskHandleMotion;

/** 
 * These static functions are used by the Motion Task. These are not available 
 * outside this file. See the respective function definitions for more details. 
 */
static void AnyMotion_Interrupt(void);
static int8_t MotionSensor_Init(void);
static int8_t MotionSensor_ConfigAnyMotionIntr(void);


/*******************************************************************************
* Function Name: void Task_Motion(void *pvParameters)
********************************************************************************
* Summary:
*  Task that processes the Motion Sensor, and then commands other tasks 
*  to take an action.
*
* Parameters:
*  void *pvParameters : Task parameter defined during task creation (unused)                            
*
* Return:
*  None
*
*******************************************************************************/
void Task_Motion(void* pvParameters)
{
    /* Variable used to store the return values of Motion Sensor APIs */
    static int8_t motionSensorApiResult;
    
    
    /* Remove warning for unused parameter */
    (void)pvParameters;
    
    /* Create binary semaphore and check the operation */
    xSemaphoreI2C = xSemaphoreCreateBinary();
    
    /* Initialize BMI160 Motion Sensor and check the operation */
    motionSensorApiResult = MotionSensor_Init();
    
    /* Configure AnyMotion interrupt and check the operation */
    motionSensorApiResult = MotionSensor_ConfigAnyMotionIntr();
        
    for(;;)
    {  
        /* Suspend the task */
        vTaskSuspend(xTaskHandleMotion);
    }
}

/*******************************************************************************
* Function Name: static void Orientation_Interrupt(void)
********************************************************************************
*
* Summary:
*  Fonction d'interruption Anymotion, qui est activée lorsque le bmi160 détecte
*  quelque mouvement que ce soit, à un certain seuil défini plus bas.
* 
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void AnyMotion_Interrupt(void)
{
    
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    /* Permet de comptabiliser les mouvements seulement si l'utilisateur est en train de prendre des donnees */
    if(menuActif == false && compteur >= 20){
        accelerometre = true;
        OrangeLedBlink();
    }
    
    /* Clear any pending interrupts */
    Cy_GPIO_ClearInterrupt(Pin_AnyMotion_INT_PORT, Pin_AnyMotion_INT_NUM);
    NVIC_ClearPendingIRQ(SysInt_AnyMotionINT_cfg.intrSrc);
    
    /* Resume Task_Motion */
    xHigherPriorityTaskWoken = xTaskResumeFromISR(xTaskHandleMotion);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken );
}


/*******************************************************************************
* Function Name: static int8_t MotionSensor_ConfigAnyMotionIntr(void)
********************************************************************************
*
* Summary:
*  Configures the motion sensor to detect change in orientation. This functions 
*  maps INT2 to provide a pulse on orientation change and configures the active 
*  level and pulse width.
* 
* Parameters:
*  None
*
* Return:
*  Returns the error status, a non-zero value indicates an error. 
*
*******************************************************************************/
static int8_t MotionSensor_ConfigAnyMotionIntr(void)
{
    /* Structure for storing interrupt configuration */
    struct bmi160_int_settg int_config;
    /* Variable used to store the return values of BMI160 APIs */
    uint8_t rslt = BMI160_OK;
    
    /* Map the step interrupt to INT1 pin */
    int_config.int_channel = BMI160_INT_CHANNEL_2;

    /* Select the Interrupt type to any-motion interrupt */
    int_config.int_type = BMI160_ACC_ANY_MOTION_INT; //Anymotion int
    
    /* Interrupt pin configuration */
    /* Enabling interrupt pins to act as output pin */
    int_config.int_pin_settg.output_en = BMI160_ENABLE;
    /*Choosing push-pull mode for interrupt pin */
    int_config.int_pin_settg.output_mode = BMI160_DISABLE;
    /* Choosing active High output */
    int_config.int_pin_settg.output_type = BMI160_ENABLE;
    /* Choosing edge triggered output */
    int_config.int_pin_settg.edge_ctrl = BMI160_ENABLE;
    /* Disabling interrupt pin to act as input */
    int_config.int_pin_settg.input_en = BMI160_DISABLE;
    /* 2.5 millisecond latched output */
    int_config.int_pin_settg.latch_dur =BMI160_LATCH_DUR_2_5_MILLI_SEC;
    
    /* Interrupt type configuration */
   // na - Select the Any Motion Interrupt parameter
    
   // na - 1- Enable the any-motion, 0- disable any-motion
   int_config.int_type_cfg.acc_any_motion_int.anymotion_en = BMI160_ENABLE; 
   // na - Enabling x-axis for any motion interrupt - monitor x axis 
   int_config.int_type_cfg.acc_any_motion_int.anymotion_x = BMI160_ENABLE; 
   // na - Enabling y-axis for any motion interrupt - monitor y axis 
   int_config.int_type_cfg.acc_any_motion_int.anymotion_y = BMI160_ENABLE; 
   // na - Enabling z-axis for any motion interrupt - monitor z axis
   int_config.int_type_cfg.acc_any_motion_int.anymotion_z = BMI160_ENABLE; 
   
   
   //***SENSIBILITÉ de l'intteruption : Cela prend 3 points de suite au-dessus du seuil de 60 (threshold)***//
   int_config.int_type_cfg.acc_any_motion_int.anymotion_dur = 3;            
   int_config.int_type_cfg.acc_any_motion_int.anymotion_thr = 60;          
   
    
    /* Set the Step Detector interrupt */
    rslt = bmi160_set_int_config(&int_config, &sensor);
    
    /* Initialize and enable Orientation Interrupt*/
    Cy_SysInt_Init(&SysInt_AnyMotionINT_cfg, AnyMotion_Interrupt);
    NVIC_EnableIRQ(SysInt_AnyMotionINT_cfg.intrSrc);
    
    return rslt;
}


/*******************************************************************************
* Function Name: static int8_t MotionSensor_Init(void)
********************************************************************************
*
* Summary: 
*  Initializes the motion sensor. This initializes the driver, resets the chip
*  and checks connection with the sensor.
*
* Parameters:
*  None
*
* Return:
*  Returns the error status, a non-zero value indicates an error. An error indicates 
*  failure in communicating with the motion sensor.
*
*******************************************************************************/
static int8_t MotionSensor_Init(void)
{
    /* Variable used to store the return values of BMI160 APIs */
    uint8_t rslt        = BMI160_OK;
    
    /* Start the I2C master interface for BMI160 motion sensor */
    I2Cm_Start();
    /* Register interrupt callback */
    I2Cm_RegisterEventCallback(I2C_Callback);
    
    /* Sensor configurations */
    sensor.id           = BMI160_I2C_ADDR;
    sensor.interface    = BMI160_I2C_INTF;
    sensor.read         = (bmi160_com_fptr_t)I2C_ReadBytes;
    sensor.write        = (bmi160_com_fptr_t)I2C_WriteBytes;
    sensor.delay_ms     = vTaskDelay;
    
    /* Initialize BNI160 sensor */
    rslt += bmi160_init(&sensor);
        
    if(rslt == BMI160_OK) /* BMI160 initialization successful */
    {
        /* Select the Output data rate, range of accelerometer sensor */
        sensor.accel_cfg.odr    = BMI160_ACCEL_ODR_1600HZ;
        sensor.accel_cfg.range  = BMI160_ACCEL_RANGE_16G;
        sensor.accel_cfg.bw     = BMI160_ACCEL_BW_NORMAL_AVG4;

        /* Select the power mode of accelerometer sensor */
        sensor.accel_cfg.power  = BMI160_ACCEL_NORMAL_MODE;

        /* Select the Output data rate, range of Gyroscope sensor */
        sensor.gyro_cfg.odr     = BMI160_GYRO_ODR_3200HZ;
        sensor.gyro_cfg.range   = BMI160_GYRO_RANGE_2000_DPS;
        sensor.gyro_cfg.bw      = BMI160_GYRO_BW_NORMAL_MODE;

        /* Select the power mode of Gyroscope sensor */
        sensor.gyro_cfg.power   = BMI160_GYRO_NORMAL_MODE; 

        /* Set the sensor configuration */
        rslt = bmi160_set_sens_conf(&sensor);
    }
    return rslt;
}

/* [] END OF FILE */
