/*******************************************************************************
* File Name: cyfitter_gpio.h
* 
* PSoC Creator  4.4
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2020 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#ifndef INCLUDED_CYFITTER_GPIO_H
#define INCLUDED_CYFITTER_GPIO_H
#include "cy_device_headers.h"

/* SW2 */
#define SW2_0_DRIVEMODE CY_GPIO_DM_PULLUP
#define SW2_0_INBUF_ENABLED 1u
#define SW2_0_INIT_DRIVESTATE 1u
#define SW2_0_INIT_MUXSEL 0u
#define SW2_0_INPUT_SYNC 2u
#define SW2_0_INTERRUPT_MODE CY_GPIO_INTR_FALLING
#define SW2_0_NUM 4u
#define SW2_0_PORT GPIO_PRT0
#define SW2_0_SLEWRATE CY_GPIO_SLEW_FAST
#define SW2_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define SW2_DRIVEMODE CY_GPIO_DM_PULLUP
#define SW2_INBUF_ENABLED 1u
#define SW2_INIT_DRIVESTATE 1u
#define SW2_INIT_MUXSEL 0u
#define SW2_INPUT_SYNC 2u
#define SW2_INTERRUPT_MODE CY_GPIO_INTR_FALLING
#define SW2_NUM 4u
#define SW2_PORT GPIO_PRT0
#define SW2_SLEWRATE CY_GPIO_SLEW_FAST
#define SW2_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* PWM_OUT */
#define PWM_OUT_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define PWM_OUT_0_INBUF_ENABLED 0u
#define PWM_OUT_0_INIT_DRIVESTATE 1u
#define PWM_OUT_0_INIT_MUXSEL 8u
#define PWM_OUT_0_INPUT_SYNC 2u
#define PWM_OUT_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define PWM_OUT_0_NUM 2u
#define PWM_OUT_0_PORT GPIO_PRT6
#define PWM_OUT_0_SLEWRATE CY_GPIO_SLEW_FAST
#define PWM_OUT_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define PWM_OUT_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define PWM_OUT_INBUF_ENABLED 0u
#define PWM_OUT_INIT_DRIVESTATE 1u
#define PWM_OUT_INIT_MUXSEL 8u
#define PWM_OUT_INPUT_SYNC 2u
#define PWM_OUT_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define PWM_OUT_NUM 2u
#define PWM_OUT_PORT GPIO_PRT6
#define PWM_OUT_SLEWRATE CY_GPIO_SLEW_FAST
#define PWM_OUT_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* GreenLED */
#define GreenLED_0_DRIVEMODE CY_GPIO_DM_PULLUP_IN_OFF
#define GreenLED_0_INBUF_ENABLED 0u
#define GreenLED_0_INIT_DRIVESTATE 1u
#define GreenLED_0_INIT_MUXSEL 3u
#define GreenLED_0_INPUT_SYNC 2u
#define GreenLED_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define GreenLED_0_NUM 1u
#define GreenLED_0_PORT GPIO_PRT1
#define GreenLED_0_SLEWRATE CY_GPIO_SLEW_FAST
#define GreenLED_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define GreenLED_DRIVEMODE CY_GPIO_DM_PULLUP_IN_OFF
#define GreenLED_INBUF_ENABLED 0u
#define GreenLED_INIT_DRIVESTATE 1u
#define GreenLED_INIT_MUXSEL 3u
#define GreenLED_INPUT_SYNC 2u
#define GreenLED_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define GreenLED_NUM 1u
#define GreenLED_PORT GPIO_PRT1
#define GreenLED_SLEWRATE CY_GPIO_SLEW_FAST
#define GreenLED_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CapSense_Rx */
#define CapSense_Rx_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define CapSense_Rx_0_INBUF_ENABLED 0u
#define CapSense_Rx_0_INIT_DRIVESTATE 1u
#define CapSense_Rx_0_INIT_MUXSEL 4u
#define CapSense_Rx_0_INPUT_SYNC 2u
#define CapSense_Rx_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CapSense_Rx_0_NUM 1u
#define CapSense_Rx_0_PORT GPIO_PRT8
#define CapSense_Rx_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CapSense_Rx_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CapSense_Rx_1_DRIVEMODE CY_GPIO_DM_ANALOG
#define CapSense_Rx_1_INBUF_ENABLED 0u
#define CapSense_Rx_1_INIT_DRIVESTATE 1u
#define CapSense_Rx_1_INIT_MUXSEL 4u
#define CapSense_Rx_1_INPUT_SYNC 2u
#define CapSense_Rx_1_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CapSense_Rx_1_NUM 2u
#define CapSense_Rx_1_PORT GPIO_PRT8
#define CapSense_Rx_1_SLEWRATE CY_GPIO_SLEW_FAST
#define CapSense_Rx_1_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CapSense_Rx_2_DRIVEMODE CY_GPIO_DM_ANALOG
#define CapSense_Rx_2_INBUF_ENABLED 0u
#define CapSense_Rx_2_INIT_DRIVESTATE 1u
#define CapSense_Rx_2_INIT_MUXSEL 4u
#define CapSense_Rx_2_INPUT_SYNC 2u
#define CapSense_Rx_2_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CapSense_Rx_2_NUM 3u
#define CapSense_Rx_2_PORT GPIO_PRT8
#define CapSense_Rx_2_SLEWRATE CY_GPIO_SLEW_FAST
#define CapSense_Rx_2_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CapSense_Rx_3_DRIVEMODE CY_GPIO_DM_ANALOG
#define CapSense_Rx_3_INBUF_ENABLED 0u
#define CapSense_Rx_3_INIT_DRIVESTATE 1u
#define CapSense_Rx_3_INIT_MUXSEL 4u
#define CapSense_Rx_3_INPUT_SYNC 2u
#define CapSense_Rx_3_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CapSense_Rx_3_NUM 7u
#define CapSense_Rx_3_PORT GPIO_PRT8
#define CapSense_Rx_3_SLEWRATE CY_GPIO_SLEW_FAST
#define CapSense_Rx_3_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CapSense_Tx */
#define CapSense_Tx_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define CapSense_Tx_0_INBUF_ENABLED 0u
#define CapSense_Tx_0_INIT_DRIVESTATE 1u
#define CapSense_Tx_0_INIT_MUXSEL 0u
#define CapSense_Tx_0_INPUT_SYNC 2u
#define CapSense_Tx_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CapSense_Tx_0_NUM 0u
#define CapSense_Tx_0_PORT GPIO_PRT1
#define CapSense_Tx_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CapSense_Tx_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CapSense_Tx_DRIVEMODE CY_GPIO_DM_ANALOG
#define CapSense_Tx_INBUF_ENABLED 0u
#define CapSense_Tx_INIT_DRIVESTATE 1u
#define CapSense_Tx_INIT_MUXSEL 0u
#define CapSense_Tx_INPUT_SYNC 2u
#define CapSense_Tx_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CapSense_Tx_NUM 0u
#define CapSense_Tx_PORT GPIO_PRT1
#define CapSense_Tx_SLEWRATE CY_GPIO_SLEW_FAST
#define CapSense_Tx_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CY_EINK_Ssel */
#define CY_EINK_Ssel_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_Ssel_0_INBUF_ENABLED 0u
#define CY_EINK_Ssel_0_INIT_DRIVESTATE 0u
#define CY_EINK_Ssel_0_INIT_MUXSEL 0u
#define CY_EINK_Ssel_0_INPUT_SYNC 2u
#define CY_EINK_Ssel_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_Ssel_0_NUM 3u
#define CY_EINK_Ssel_0_PORT GPIO_PRT12
#define CY_EINK_Ssel_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_Ssel_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CY_EINK_Ssel_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_Ssel_INBUF_ENABLED 0u
#define CY_EINK_Ssel_INIT_DRIVESTATE 0u
#define CY_EINK_Ssel_INIT_MUXSEL 0u
#define CY_EINK_Ssel_INPUT_SYNC 2u
#define CY_EINK_Ssel_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_Ssel_NUM 3u
#define CY_EINK_Ssel_PORT GPIO_PRT12
#define CY_EINK_Ssel_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_Ssel_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CY_EINK_Border */
#define CY_EINK_Border_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_Border_0_INBUF_ENABLED 0u
#define CY_EINK_Border_0_INIT_DRIVESTATE 0u
#define CY_EINK_Border_0_INIT_MUXSEL 0u
#define CY_EINK_Border_0_INPUT_SYNC 2u
#define CY_EINK_Border_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_Border_0_NUM 6u
#define CY_EINK_Border_0_PORT GPIO_PRT5
#define CY_EINK_Border_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_Border_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CY_EINK_Border_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_Border_INBUF_ENABLED 0u
#define CY_EINK_Border_INIT_DRIVESTATE 0u
#define CY_EINK_Border_INIT_MUXSEL 0u
#define CY_EINK_Border_INPUT_SYNC 2u
#define CY_EINK_Border_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_Border_NUM 6u
#define CY_EINK_Border_PORT GPIO_PRT5
#define CY_EINK_Border_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_Border_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CY_EINK_DispEn */
#define CY_EINK_DispEn_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_DispEn_0_INBUF_ENABLED 0u
#define CY_EINK_DispEn_0_INIT_DRIVESTATE 0u
#define CY_EINK_DispEn_0_INIT_MUXSEL 0u
#define CY_EINK_DispEn_0_INPUT_SYNC 2u
#define CY_EINK_DispEn_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_DispEn_0_NUM 4u
#define CY_EINK_DispEn_0_PORT GPIO_PRT5
#define CY_EINK_DispEn_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_DispEn_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CY_EINK_DispEn_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_DispEn_INBUF_ENABLED 0u
#define CY_EINK_DispEn_INIT_DRIVESTATE 0u
#define CY_EINK_DispEn_INIT_MUXSEL 0u
#define CY_EINK_DispEn_INPUT_SYNC 2u
#define CY_EINK_DispEn_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_DispEn_NUM 4u
#define CY_EINK_DispEn_PORT GPIO_PRT5
#define CY_EINK_DispEn_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_DispEn_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CapSense_CintA */
#define CapSense_CintA_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define CapSense_CintA_0_INBUF_ENABLED 0u
#define CapSense_CintA_0_INIT_DRIVESTATE 1u
#define CapSense_CintA_0_INIT_MUXSEL 0u
#define CapSense_CintA_0_INPUT_SYNC 2u
#define CapSense_CintA_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CapSense_CintA_0_NUM 1u
#define CapSense_CintA_0_PORT GPIO_PRT7
#define CapSense_CintA_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CapSense_CintA_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CapSense_CintA_DRIVEMODE CY_GPIO_DM_ANALOG
#define CapSense_CintA_INBUF_ENABLED 0u
#define CapSense_CintA_INIT_DRIVESTATE 1u
#define CapSense_CintA_INIT_MUXSEL 0u
#define CapSense_CintA_INPUT_SYNC 2u
#define CapSense_CintA_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CapSense_CintA_NUM 1u
#define CapSense_CintA_PORT GPIO_PRT7
#define CapSense_CintA_SLEWRATE CY_GPIO_SLEW_FAST
#define CapSense_CintA_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CapSense_CintB */
#define CapSense_CintB_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define CapSense_CintB_0_INBUF_ENABLED 0u
#define CapSense_CintB_0_INIT_DRIVESTATE 1u
#define CapSense_CintB_0_INIT_MUXSEL 0u
#define CapSense_CintB_0_INPUT_SYNC 2u
#define CapSense_CintB_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CapSense_CintB_0_NUM 2u
#define CapSense_CintB_0_PORT GPIO_PRT7
#define CapSense_CintB_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CapSense_CintB_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CapSense_CintB_DRIVEMODE CY_GPIO_DM_ANALOG
#define CapSense_CintB_INBUF_ENABLED 0u
#define CapSense_CintB_INIT_DRIVESTATE 1u
#define CapSense_CintB_INIT_MUXSEL 0u
#define CapSense_CintB_INPUT_SYNC 2u
#define CapSense_CintB_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CapSense_CintB_NUM 2u
#define CapSense_CintB_PORT GPIO_PRT7
#define CapSense_CintB_SLEWRATE CY_GPIO_SLEW_FAST
#define CapSense_CintB_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CY_EINK_DispRst */
#define CY_EINK_DispRst_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_DispRst_0_INBUF_ENABLED 0u
#define CY_EINK_DispRst_0_INIT_DRIVESTATE 0u
#define CY_EINK_DispRst_0_INIT_MUXSEL 0u
#define CY_EINK_DispRst_0_INPUT_SYNC 2u
#define CY_EINK_DispRst_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_DispRst_0_NUM 2u
#define CY_EINK_DispRst_0_PORT GPIO_PRT5
#define CY_EINK_DispRst_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_DispRst_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CY_EINK_DispRst_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_DispRst_INBUF_ENABLED 0u
#define CY_EINK_DispRst_INIT_DRIVESTATE 0u
#define CY_EINK_DispRst_INIT_MUXSEL 0u
#define CY_EINK_DispRst_INPUT_SYNC 2u
#define CY_EINK_DispRst_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_DispRst_NUM 2u
#define CY_EINK_DispRst_PORT GPIO_PRT5
#define CY_EINK_DispRst_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_DispRst_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CY_EINK_DispBusy */
#define CY_EINK_DispBusy_0_DRIVEMODE CY_GPIO_DM_HIGHZ
#define CY_EINK_DispBusy_0_INBUF_ENABLED 1u
#define CY_EINK_DispBusy_0_INIT_DRIVESTATE 0u
#define CY_EINK_DispBusy_0_INIT_MUXSEL 0u
#define CY_EINK_DispBusy_0_INPUT_SYNC 2u
#define CY_EINK_DispBusy_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_DispBusy_0_NUM 3u
#define CY_EINK_DispBusy_0_PORT GPIO_PRT5
#define CY_EINK_DispBusy_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_DispBusy_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CY_EINK_DispBusy_DRIVEMODE CY_GPIO_DM_HIGHZ
#define CY_EINK_DispBusy_INBUF_ENABLED 1u
#define CY_EINK_DispBusy_INIT_DRIVESTATE 0u
#define CY_EINK_DispBusy_INIT_MUXSEL 0u
#define CY_EINK_DispBusy_INPUT_SYNC 2u
#define CY_EINK_DispBusy_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_DispBusy_NUM 3u
#define CY_EINK_DispBusy_PORT GPIO_PRT5
#define CY_EINK_DispBusy_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_DispBusy_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CY_EINK_DispIoEn */
#define CY_EINK_DispIoEn_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_DispIoEn_0_INBUF_ENABLED 0u
#define CY_EINK_DispIoEn_0_INIT_DRIVESTATE 0u
#define CY_EINK_DispIoEn_0_INIT_MUXSEL 0u
#define CY_EINK_DispIoEn_0_INPUT_SYNC 2u
#define CY_EINK_DispIoEn_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_DispIoEn_0_NUM 2u
#define CY_EINK_DispIoEn_0_PORT GPIO_PRT0
#define CY_EINK_DispIoEn_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_DispIoEn_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CY_EINK_DispIoEn_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_DispIoEn_INBUF_ENABLED 0u
#define CY_EINK_DispIoEn_INIT_DRIVESTATE 0u
#define CY_EINK_DispIoEn_INIT_MUXSEL 0u
#define CY_EINK_DispIoEn_INPUT_SYNC 2u
#define CY_EINK_DispIoEn_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_DispIoEn_NUM 2u
#define CY_EINK_DispIoEn_PORT GPIO_PRT0
#define CY_EINK_DispIoEn_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_DispIoEn_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CY_EINK_Discharge */
#define CY_EINK_Discharge_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_Discharge_0_INBUF_ENABLED 0u
#define CY_EINK_Discharge_0_INIT_DRIVESTATE 0u
#define CY_EINK_Discharge_0_INIT_MUXSEL 0u
#define CY_EINK_Discharge_0_INPUT_SYNC 2u
#define CY_EINK_Discharge_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_Discharge_0_NUM 5u
#define CY_EINK_Discharge_0_PORT GPIO_PRT5
#define CY_EINK_Discharge_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_Discharge_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CY_EINK_Discharge_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_Discharge_INBUF_ENABLED 0u
#define CY_EINK_Discharge_INIT_DRIVESTATE 0u
#define CY_EINK_Discharge_INIT_MUXSEL 0u
#define CY_EINK_Discharge_INPUT_SYNC 2u
#define CY_EINK_Discharge_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_Discharge_NUM 5u
#define CY_EINK_Discharge_PORT GPIO_PRT5
#define CY_EINK_Discharge_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_Discharge_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CY_EINK_SPIM_miso_m */
#define CY_EINK_SPIM_miso_m_0_DRIVEMODE CY_GPIO_DM_HIGHZ
#define CY_EINK_SPIM_miso_m_0_INBUF_ENABLED 1u
#define CY_EINK_SPIM_miso_m_0_INIT_DRIVESTATE 1u
#define CY_EINK_SPIM_miso_m_0_INIT_MUXSEL 20u
#define CY_EINK_SPIM_miso_m_0_INPUT_SYNC 2u
#define CY_EINK_SPIM_miso_m_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_SPIM_miso_m_0_NUM 1u
#define CY_EINK_SPIM_miso_m_0_PORT GPIO_PRT12
#define CY_EINK_SPIM_miso_m_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_SPIM_miso_m_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CY_EINK_SPIM_miso_m_DRIVEMODE CY_GPIO_DM_HIGHZ
#define CY_EINK_SPIM_miso_m_INBUF_ENABLED 1u
#define CY_EINK_SPIM_miso_m_INIT_DRIVESTATE 1u
#define CY_EINK_SPIM_miso_m_INIT_MUXSEL 20u
#define CY_EINK_SPIM_miso_m_INPUT_SYNC 2u
#define CY_EINK_SPIM_miso_m_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_SPIM_miso_m_NUM 1u
#define CY_EINK_SPIM_miso_m_PORT GPIO_PRT12
#define CY_EINK_SPIM_miso_m_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_SPIM_miso_m_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CY_EINK_SPIM_mosi_m */
#define CY_EINK_SPIM_mosi_m_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_SPIM_mosi_m_0_INBUF_ENABLED 0u
#define CY_EINK_SPIM_mosi_m_0_INIT_DRIVESTATE 1u
#define CY_EINK_SPIM_mosi_m_0_INIT_MUXSEL 20u
#define CY_EINK_SPIM_mosi_m_0_INPUT_SYNC 2u
#define CY_EINK_SPIM_mosi_m_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_SPIM_mosi_m_0_NUM 0u
#define CY_EINK_SPIM_mosi_m_0_PORT GPIO_PRT12
#define CY_EINK_SPIM_mosi_m_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_SPIM_mosi_m_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CY_EINK_SPIM_mosi_m_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_SPIM_mosi_m_INBUF_ENABLED 0u
#define CY_EINK_SPIM_mosi_m_INIT_DRIVESTATE 1u
#define CY_EINK_SPIM_mosi_m_INIT_MUXSEL 20u
#define CY_EINK_SPIM_mosi_m_INPUT_SYNC 2u
#define CY_EINK_SPIM_mosi_m_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_SPIM_mosi_m_NUM 0u
#define CY_EINK_SPIM_mosi_m_PORT GPIO_PRT12
#define CY_EINK_SPIM_mosi_m_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_SPIM_mosi_m_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* CY_EINK_SPIM_sclk_m */
#define CY_EINK_SPIM_sclk_m_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_SPIM_sclk_m_0_INBUF_ENABLED 0u
#define CY_EINK_SPIM_sclk_m_0_INIT_DRIVESTATE 1u
#define CY_EINK_SPIM_sclk_m_0_INIT_MUXSEL 20u
#define CY_EINK_SPIM_sclk_m_0_INPUT_SYNC 2u
#define CY_EINK_SPIM_sclk_m_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_SPIM_sclk_m_0_NUM 2u
#define CY_EINK_SPIM_sclk_m_0_PORT GPIO_PRT12
#define CY_EINK_SPIM_sclk_m_0_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_SPIM_sclk_m_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define CY_EINK_SPIM_sclk_m_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CY_EINK_SPIM_sclk_m_INBUF_ENABLED 0u
#define CY_EINK_SPIM_sclk_m_INIT_DRIVESTATE 1u
#define CY_EINK_SPIM_sclk_m_INIT_MUXSEL 20u
#define CY_EINK_SPIM_sclk_m_INPUT_SYNC 2u
#define CY_EINK_SPIM_sclk_m_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define CY_EINK_SPIM_sclk_m_NUM 2u
#define CY_EINK_SPIM_sclk_m_PORT GPIO_PRT12
#define CY_EINK_SPIM_sclk_m_SLEWRATE CY_GPIO_SLEW_FAST
#define CY_EINK_SPIM_sclk_m_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

#endif /* INCLUDED_CYFITTER_GPIO_H */
