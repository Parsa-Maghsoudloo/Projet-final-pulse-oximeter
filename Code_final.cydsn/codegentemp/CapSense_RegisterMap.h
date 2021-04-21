/***************************************************************************//**
* \file CapSense_RegisterMap.h
* \version 3.0
*
* \brief
*   This file provides the definitions for the Component data structure register.
*
* \see CapSense v3.0 Datasheet
*
*//*****************************************************************************
* Copyright (2016-2017), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/

#if !defined(CY_SENSE_CapSense_REGISTER_MAP_H)
#define CY_SENSE_CapSense_REGISTER_MAP_H

#include "syslib/cy_syslib.h"
#include "CapSense_Configuration.h"
#include "CapSense_Structure.h"

/*****************************************************************************/
/* RAM Data structure register definitions                                   */
/*****************************************************************************/
#define CapSense_CONFIG_ID_VALUE                            (CapSense_dsRam.configId)
#define CapSense_CONFIG_ID_OFFSET                           (0u)
#define CapSense_CONFIG_ID_SIZE                             (2u)
#define CapSense_CONFIG_ID_PARAM_ID                         (0x87000000u)

#define CapSense_DEVICE_ID_VALUE                            (CapSense_dsRam.deviceId)
#define CapSense_DEVICE_ID_OFFSET                           (2u)
#define CapSense_DEVICE_ID_SIZE                             (2u)
#define CapSense_DEVICE_ID_PARAM_ID                         (0x8B000002u)

#define CapSense_HW_CLOCK_VALUE                             (CapSense_dsRam.hwClock)
#define CapSense_HW_CLOCK_OFFSET                            (4u)
#define CapSense_HW_CLOCK_SIZE                              (2u)
#define CapSense_HW_CLOCK_PARAM_ID                          (0x86000004u)

#define CapSense_TUNER_CMD_VALUE                            (CapSense_dsRam.tunerCmd)
#define CapSense_TUNER_CMD_OFFSET                           (6u)
#define CapSense_TUNER_CMD_SIZE                             (2u)
#define CapSense_TUNER_CMD_PARAM_ID                         (0xA1000006u)

#define CapSense_SCAN_COUNTER_VALUE                         (CapSense_dsRam.scanCounter)
#define CapSense_SCAN_COUNTER_OFFSET                        (8u)
#define CapSense_SCAN_COUNTER_SIZE                          (2u)
#define CapSense_SCAN_COUNTER_PARAM_ID                      (0x85000008u)

#define CapSense_STATUS_VALUE                               (CapSense_dsRam.status)
#define CapSense_STATUS_OFFSET                              (12u)
#define CapSense_STATUS_SIZE                                (4u)
#define CapSense_STATUS_PARAM_ID                            (0xCB00000Cu)

#define CapSense_WDGT_ENABLE0_VALUE                         (CapSense_dsRam.wdgtEnable[0u])
#define CapSense_WDGT_ENABLE0_OFFSET                        (16u)
#define CapSense_WDGT_ENABLE0_SIZE                          (4u)
#define CapSense_WDGT_ENABLE0_PARAM_ID                      (0xE6000010u)

#define CapSense_WDGT_STATUS0_VALUE                         (CapSense_dsRam.wdgtStatus[0u])
#define CapSense_WDGT_STATUS0_OFFSET                        (20u)
#define CapSense_WDGT_STATUS0_SIZE                          (4u)
#define CapSense_WDGT_STATUS0_PARAM_ID                      (0xCC000014u)

#define CapSense_SNS_STATUS0_VALUE                          (CapSense_dsRam.snsStatus[0u])
#define CapSense_SNS_STATUS0_OFFSET                         (24u)
#define CapSense_SNS_STATUS0_SIZE                           (1u)
#define CapSense_SNS_STATUS0_PARAM_ID                       (0x48000018u)

#define CapSense_SNS_STATUS1_VALUE                          (CapSense_dsRam.snsStatus[1u])
#define CapSense_SNS_STATUS1_OFFSET                         (25u)
#define CapSense_SNS_STATUS1_SIZE                           (1u)
#define CapSense_SNS_STATUS1_PARAM_ID                       (0x4E000019u)

#define CapSense_SNS_STATUS2_VALUE                          (CapSense_dsRam.snsStatus[2u])
#define CapSense_SNS_STATUS2_OFFSET                         (26u)
#define CapSense_SNS_STATUS2_SIZE                           (1u)
#define CapSense_SNS_STATUS2_PARAM_ID                       (0x4400001Au)

#define CapSense_SNS_STATUS3_VALUE                          (CapSense_dsRam.snsStatus[3u])
#define CapSense_SNS_STATUS3_OFFSET                         (27u)
#define CapSense_SNS_STATUS3_SIZE                           (1u)
#define CapSense_SNS_STATUS3_PARAM_ID                       (0x4200001Bu)

#define CapSense_CSD0_CONFIG_VALUE                          (CapSense_dsRam.csd0Config)
#define CapSense_CSD0_CONFIG_OFFSET                         (28u)
#define CapSense_CSD0_CONFIG_SIZE                           (2u)
#define CapSense_CSD0_CONFIG_PARAM_ID                       (0xA780001Cu)

#define CapSense_MOD_CSX_CLK_VALUE                          (CapSense_dsRam.modCsxClk)
#define CapSense_MOD_CSX_CLK_OFFSET                         (30u)
#define CapSense_MOD_CSX_CLK_SIZE                           (1u)
#define CapSense_MOD_CSX_CLK_PARAM_ID                       (0x6380001Eu)

#define CapSense_BUTTON0_RESOLUTION_VALUE                   (CapSense_dsRam.wdgtList.button0.resolution)
#define CapSense_BUTTON0_RESOLUTION_OFFSET                  (32u)
#define CapSense_BUTTON0_RESOLUTION_SIZE                    (2u)
#define CapSense_BUTTON0_RESOLUTION_PARAM_ID                (0xAB800020u)

#define CapSense_BUTTON0_FINGER_TH_VALUE                    (CapSense_dsRam.wdgtList.button0.fingerTh)
#define CapSense_BUTTON0_FINGER_TH_OFFSET                   (34u)
#define CapSense_BUTTON0_FINGER_TH_SIZE                     (2u)
#define CapSense_BUTTON0_FINGER_TH_PARAM_ID                 (0xA7800022u)

#define CapSense_BUTTON0_NOISE_TH_VALUE                     (CapSense_dsRam.wdgtList.button0.noiseTh)
#define CapSense_BUTTON0_NOISE_TH_OFFSET                    (36u)
#define CapSense_BUTTON0_NOISE_TH_SIZE                      (1u)
#define CapSense_BUTTON0_NOISE_TH_PARAM_ID                  (0x62800024u)

#define CapSense_BUTTON0_NNOISE_TH_VALUE                    (CapSense_dsRam.wdgtList.button0.nNoiseTh)
#define CapSense_BUTTON0_NNOISE_TH_OFFSET                   (37u)
#define CapSense_BUTTON0_NNOISE_TH_SIZE                     (1u)
#define CapSense_BUTTON0_NNOISE_TH_PARAM_ID                 (0x64800025u)

#define CapSense_BUTTON0_HYSTERESIS_VALUE                   (CapSense_dsRam.wdgtList.button0.hysteresis)
#define CapSense_BUTTON0_HYSTERESIS_OFFSET                  (38u)
#define CapSense_BUTTON0_HYSTERESIS_SIZE                    (1u)
#define CapSense_BUTTON0_HYSTERESIS_PARAM_ID                (0x6E800026u)

#define CapSense_BUTTON0_ON_DEBOUNCE_VALUE                  (CapSense_dsRam.wdgtList.button0.onDebounce)
#define CapSense_BUTTON0_ON_DEBOUNCE_OFFSET                 (39u)
#define CapSense_BUTTON0_ON_DEBOUNCE_SIZE                   (1u)
#define CapSense_BUTTON0_ON_DEBOUNCE_PARAM_ID               (0x68800027u)

#define CapSense_BUTTON0_LOW_BSLN_RST_VALUE                 (CapSense_dsRam.wdgtList.button0.lowBslnRst)
#define CapSense_BUTTON0_LOW_BSLN_RST_OFFSET                (40u)
#define CapSense_BUTTON0_LOW_BSLN_RST_SIZE                  (1u)
#define CapSense_BUTTON0_LOW_BSLN_RST_PARAM_ID              (0x61800028u)

#define CapSense_BUTTON0_SNS_CLK_VALUE                      (CapSense_dsRam.wdgtList.button0.snsClk)
#define CapSense_BUTTON0_SNS_CLK_OFFSET                     (42u)
#define CapSense_BUTTON0_SNS_CLK_SIZE                       (2u)
#define CapSense_BUTTON0_SNS_CLK_PARAM_ID                   (0xA580002Au)

#define CapSense_BUTTON0_SNS_CLK_SOURCE_VALUE               (CapSense_dsRam.wdgtList.button0.snsClkSource)
#define CapSense_BUTTON0_SNS_CLK_SOURCE_OFFSET              (44u)
#define CapSense_BUTTON0_SNS_CLK_SOURCE_SIZE                (1u)
#define CapSense_BUTTON0_SNS_CLK_SOURCE_PARAM_ID            (0x4B80002Cu)

#define CapSense_BUTTON1_RESOLUTION_VALUE                   (CapSense_dsRam.wdgtList.button1.resolution)
#define CapSense_BUTTON1_RESOLUTION_OFFSET                  (46u)
#define CapSense_BUTTON1_RESOLUTION_SIZE                    (2u)
#define CapSense_BUTTON1_RESOLUTION_PARAM_ID                (0xA781002Eu)

#define CapSense_BUTTON1_FINGER_TH_VALUE                    (CapSense_dsRam.wdgtList.button1.fingerTh)
#define CapSense_BUTTON1_FINGER_TH_OFFSET                   (48u)
#define CapSense_BUTTON1_FINGER_TH_SIZE                     (2u)
#define CapSense_BUTTON1_FINGER_TH_PARAM_ID                 (0xAD810030u)

#define CapSense_BUTTON1_NOISE_TH_VALUE                     (CapSense_dsRam.wdgtList.button1.noiseTh)
#define CapSense_BUTTON1_NOISE_TH_OFFSET                    (50u)
#define CapSense_BUTTON1_NOISE_TH_SIZE                      (1u)
#define CapSense_BUTTON1_NOISE_TH_PARAM_ID                  (0x69810032u)

#define CapSense_BUTTON1_NNOISE_TH_VALUE                    (CapSense_dsRam.wdgtList.button1.nNoiseTh)
#define CapSense_BUTTON1_NNOISE_TH_OFFSET                   (51u)
#define CapSense_BUTTON1_NNOISE_TH_SIZE                     (1u)
#define CapSense_BUTTON1_NNOISE_TH_PARAM_ID                 (0x6F810033u)

#define CapSense_BUTTON1_HYSTERESIS_VALUE                   (CapSense_dsRam.wdgtList.button1.hysteresis)
#define CapSense_BUTTON1_HYSTERESIS_OFFSET                  (52u)
#define CapSense_BUTTON1_HYSTERESIS_SIZE                    (1u)
#define CapSense_BUTTON1_HYSTERESIS_PARAM_ID                (0x64810034u)

#define CapSense_BUTTON1_ON_DEBOUNCE_VALUE                  (CapSense_dsRam.wdgtList.button1.onDebounce)
#define CapSense_BUTTON1_ON_DEBOUNCE_OFFSET                 (53u)
#define CapSense_BUTTON1_ON_DEBOUNCE_SIZE                   (1u)
#define CapSense_BUTTON1_ON_DEBOUNCE_PARAM_ID               (0x62810035u)

#define CapSense_BUTTON1_LOW_BSLN_RST_VALUE                 (CapSense_dsRam.wdgtList.button1.lowBslnRst)
#define CapSense_BUTTON1_LOW_BSLN_RST_OFFSET                (54u)
#define CapSense_BUTTON1_LOW_BSLN_RST_SIZE                  (1u)
#define CapSense_BUTTON1_LOW_BSLN_RST_PARAM_ID              (0x68810036u)

#define CapSense_BUTTON1_SNS_CLK_VALUE                      (CapSense_dsRam.wdgtList.button1.snsClk)
#define CapSense_BUTTON1_SNS_CLK_OFFSET                     (56u)
#define CapSense_BUTTON1_SNS_CLK_SIZE                       (2u)
#define CapSense_BUTTON1_SNS_CLK_PARAM_ID                   (0xAF810038u)

#define CapSense_BUTTON1_SNS_CLK_SOURCE_VALUE               (CapSense_dsRam.wdgtList.button1.snsClkSource)
#define CapSense_BUTTON1_SNS_CLK_SOURCE_OFFSET              (58u)
#define CapSense_BUTTON1_SNS_CLK_SOURCE_SIZE                (1u)
#define CapSense_BUTTON1_SNS_CLK_SOURCE_PARAM_ID            (0x4081003Au)

#define CapSense_SNS0_RESOLUTION_VALUE                      (CapSense_dsRam.wdgtList.sns0.resolution)
#define CapSense_SNS0_RESOLUTION_OFFSET                     (60u)
#define CapSense_SNS0_RESOLUTION_SIZE                       (2u)
#define CapSense_SNS0_RESOLUTION_PARAM_ID                   (0xAB82003Cu)

#define CapSense_SNS0_FINGER_TH_VALUE                       (CapSense_dsRam.wdgtList.sns0.fingerTh)
#define CapSense_SNS0_FINGER_TH_OFFSET                      (62u)
#define CapSense_SNS0_FINGER_TH_SIZE                        (2u)
#define CapSense_SNS0_FINGER_TH_PARAM_ID                    (0xA782003Eu)

#define CapSense_SNS0_NOISE_TH_VALUE                        (CapSense_dsRam.wdgtList.sns0.noiseTh)
#define CapSense_SNS0_NOISE_TH_OFFSET                       (64u)
#define CapSense_SNS0_NOISE_TH_SIZE                         (1u)
#define CapSense_SNS0_NOISE_TH_PARAM_ID                     (0x62820040u)

#define CapSense_SNS0_NNOISE_TH_VALUE                       (CapSense_dsRam.wdgtList.sns0.nNoiseTh)
#define CapSense_SNS0_NNOISE_TH_OFFSET                      (65u)
#define CapSense_SNS0_NNOISE_TH_SIZE                        (1u)
#define CapSense_SNS0_NNOISE_TH_PARAM_ID                    (0x64820041u)

#define CapSense_SNS0_HYSTERESIS_VALUE                      (CapSense_dsRam.wdgtList.sns0.hysteresis)
#define CapSense_SNS0_HYSTERESIS_OFFSET                     (66u)
#define CapSense_SNS0_HYSTERESIS_SIZE                       (1u)
#define CapSense_SNS0_HYSTERESIS_PARAM_ID                   (0x6E820042u)

#define CapSense_SNS0_ON_DEBOUNCE_VALUE                     (CapSense_dsRam.wdgtList.sns0.onDebounce)
#define CapSense_SNS0_ON_DEBOUNCE_OFFSET                    (67u)
#define CapSense_SNS0_ON_DEBOUNCE_SIZE                      (1u)
#define CapSense_SNS0_ON_DEBOUNCE_PARAM_ID                  (0x68820043u)

#define CapSense_SNS0_LOW_BSLN_RST_VALUE                    (CapSense_dsRam.wdgtList.sns0.lowBslnRst)
#define CapSense_SNS0_LOW_BSLN_RST_OFFSET                   (68u)
#define CapSense_SNS0_LOW_BSLN_RST_SIZE                     (1u)
#define CapSense_SNS0_LOW_BSLN_RST_PARAM_ID                 (0x63820044u)

#define CapSense_SNS0_SNS_CLK_VALUE                         (CapSense_dsRam.wdgtList.sns0.snsClk)
#define CapSense_SNS0_SNS_CLK_OFFSET                        (70u)
#define CapSense_SNS0_SNS_CLK_SIZE                          (2u)
#define CapSense_SNS0_SNS_CLK_PARAM_ID                      (0xA7820046u)

#define CapSense_SNS0_SNS_CLK_SOURCE_VALUE                  (CapSense_dsRam.wdgtList.sns0.snsClkSource)
#define CapSense_SNS0_SNS_CLK_SOURCE_OFFSET                 (72u)
#define CapSense_SNS0_SNS_CLK_SOURCE_SIZE                   (1u)
#define CapSense_SNS0_SNS_CLK_SOURCE_PARAM_ID               (0x4B820048u)

#define CapSense_SNS4_RESOLUTION_VALUE                      (CapSense_dsRam.wdgtList.sns4.resolution)
#define CapSense_SNS4_RESOLUTION_OFFSET                     (74u)
#define CapSense_SNS4_RESOLUTION_SIZE                       (2u)
#define CapSense_SNS4_RESOLUTION_PARAM_ID                   (0xA783004Au)

#define CapSense_SNS4_FINGER_TH_VALUE                       (CapSense_dsRam.wdgtList.sns4.fingerTh)
#define CapSense_SNS4_FINGER_TH_OFFSET                      (76u)
#define CapSense_SNS4_FINGER_TH_SIZE                        (2u)
#define CapSense_SNS4_FINGER_TH_PARAM_ID                    (0xAA83004Cu)

#define CapSense_SNS4_NOISE_TH_VALUE                        (CapSense_dsRam.wdgtList.sns4.noiseTh)
#define CapSense_SNS4_NOISE_TH_OFFSET                       (78u)
#define CapSense_SNS4_NOISE_TH_SIZE                         (1u)
#define CapSense_SNS4_NOISE_TH_PARAM_ID                     (0x6E83004Eu)

#define CapSense_SNS4_NNOISE_TH_VALUE                       (CapSense_dsRam.wdgtList.sns4.nNoiseTh)
#define CapSense_SNS4_NNOISE_TH_OFFSET                      (79u)
#define CapSense_SNS4_NNOISE_TH_SIZE                        (1u)
#define CapSense_SNS4_NNOISE_TH_PARAM_ID                    (0x6883004Fu)

#define CapSense_SNS4_HYSTERESIS_VALUE                      (CapSense_dsRam.wdgtList.sns4.hysteresis)
#define CapSense_SNS4_HYSTERESIS_OFFSET                     (80u)
#define CapSense_SNS4_HYSTERESIS_SIZE                       (1u)
#define CapSense_SNS4_HYSTERESIS_PARAM_ID                   (0x64830050u)

#define CapSense_SNS4_ON_DEBOUNCE_VALUE                     (CapSense_dsRam.wdgtList.sns4.onDebounce)
#define CapSense_SNS4_ON_DEBOUNCE_OFFSET                    (81u)
#define CapSense_SNS4_ON_DEBOUNCE_SIZE                      (1u)
#define CapSense_SNS4_ON_DEBOUNCE_PARAM_ID                  (0x62830051u)

#define CapSense_SNS4_LOW_BSLN_RST_VALUE                    (CapSense_dsRam.wdgtList.sns4.lowBslnRst)
#define CapSense_SNS4_LOW_BSLN_RST_OFFSET                   (82u)
#define CapSense_SNS4_LOW_BSLN_RST_SIZE                     (1u)
#define CapSense_SNS4_LOW_BSLN_RST_PARAM_ID                 (0x68830052u)

#define CapSense_SNS4_SNS_CLK_VALUE                         (CapSense_dsRam.wdgtList.sns4.snsClk)
#define CapSense_SNS4_SNS_CLK_OFFSET                        (84u)
#define CapSense_SNS4_SNS_CLK_SIZE                          (2u)
#define CapSense_SNS4_SNS_CLK_PARAM_ID                      (0xAD830054u)

#define CapSense_SNS4_SNS_CLK_SOURCE_VALUE                  (CapSense_dsRam.wdgtList.sns4.snsClkSource)
#define CapSense_SNS4_SNS_CLK_SOURCE_OFFSET                 (86u)
#define CapSense_SNS4_SNS_CLK_SOURCE_SIZE                   (1u)
#define CapSense_SNS4_SNS_CLK_SOURCE_PARAM_ID               (0x42830056u)

#define CapSense_BUTTON0_RX0_RAW0_VALUE                     (CapSense_dsRam.snsList.button0[0u].raw[0u])
#define CapSense_BUTTON0_RX0_RAW0_OFFSET                    (88u)
#define CapSense_BUTTON0_RX0_RAW0_SIZE                      (2u)
#define CapSense_BUTTON0_RX0_RAW0_PARAM_ID                  (0x8D000058u)

#define CapSense_BUTTON0_RX0_BSLN0_VALUE                    (CapSense_dsRam.snsList.button0[0u].bsln[0u])
#define CapSense_BUTTON0_RX0_BSLN0_OFFSET                   (90u)
#define CapSense_BUTTON0_RX0_BSLN0_SIZE                     (2u)
#define CapSense_BUTTON0_RX0_BSLN0_PARAM_ID                 (0x8100005Au)

#define CapSense_BUTTON0_RX0_BSLN_EXT0_VALUE                (CapSense_dsRam.snsList.button0[0u].bslnExt[0u])
#define CapSense_BUTTON0_RX0_BSLN_EXT0_OFFSET               (92u)
#define CapSense_BUTTON0_RX0_BSLN_EXT0_SIZE                 (1u)
#define CapSense_BUTTON0_RX0_BSLN_EXT0_PARAM_ID             (0x4400005Cu)

#define CapSense_BUTTON0_RX0_DIFF_VALUE                     (CapSense_dsRam.snsList.button0[0u].diff)
#define CapSense_BUTTON0_RX0_DIFF_OFFSET                    (94u)
#define CapSense_BUTTON0_RX0_DIFF_SIZE                      (2u)
#define CapSense_BUTTON0_RX0_DIFF_PARAM_ID                  (0x8000005Eu)

#define CapSense_BUTTON0_RX0_NEG_BSLN_RST_CNT0_VALUE        (CapSense_dsRam.snsList.button0[0u].negBslnRstCnt[0u])
#define CapSense_BUTTON0_RX0_NEG_BSLN_RST_CNT0_OFFSET       (96u)
#define CapSense_BUTTON0_RX0_NEG_BSLN_RST_CNT0_SIZE         (1u)
#define CapSense_BUTTON0_RX0_NEG_BSLN_RST_CNT0_PARAM_ID     (0x48000060u)

#define CapSense_BUTTON0_RX0_IDAC_COMP0_VALUE               (CapSense_dsRam.snsList.button0[0u].idacComp[0u])
#define CapSense_BUTTON0_RX0_IDAC_COMP0_OFFSET              (97u)
#define CapSense_BUTTON0_RX0_IDAC_COMP0_SIZE                (1u)
#define CapSense_BUTTON0_RX0_IDAC_COMP0_PARAM_ID            (0x4E000061u)

#define CapSense_BUTTON1_RX0_RAW0_VALUE                     (CapSense_dsRam.snsList.button1[0u].raw[0u])
#define CapSense_BUTTON1_RX0_RAW0_OFFSET                    (98u)
#define CapSense_BUTTON1_RX0_RAW0_SIZE                      (2u)
#define CapSense_BUTTON1_RX0_RAW0_PARAM_ID                  (0x8C000062u)

#define CapSense_BUTTON1_RX0_BSLN0_VALUE                    (CapSense_dsRam.snsList.button1[0u].bsln[0u])
#define CapSense_BUTTON1_RX0_BSLN0_OFFSET                   (100u)
#define CapSense_BUTTON1_RX0_BSLN0_SIZE                     (2u)
#define CapSense_BUTTON1_RX0_BSLN0_PARAM_ID                 (0x81000064u)

#define CapSense_BUTTON1_RX0_BSLN_EXT0_VALUE                (CapSense_dsRam.snsList.button1[0u].bslnExt[0u])
#define CapSense_BUTTON1_RX0_BSLN_EXT0_OFFSET               (102u)
#define CapSense_BUTTON1_RX0_BSLN_EXT0_SIZE                 (1u)
#define CapSense_BUTTON1_RX0_BSLN_EXT0_PARAM_ID             (0x45000066u)

#define CapSense_BUTTON1_RX0_DIFF_VALUE                     (CapSense_dsRam.snsList.button1[0u].diff)
#define CapSense_BUTTON1_RX0_DIFF_OFFSET                    (104u)
#define CapSense_BUTTON1_RX0_DIFF_SIZE                      (2u)
#define CapSense_BUTTON1_RX0_DIFF_PARAM_ID                  (0x82000068u)

#define CapSense_BUTTON1_RX0_NEG_BSLN_RST_CNT0_VALUE        (CapSense_dsRam.snsList.button1[0u].negBslnRstCnt[0u])
#define CapSense_BUTTON1_RX0_NEG_BSLN_RST_CNT0_OFFSET       (106u)
#define CapSense_BUTTON1_RX0_NEG_BSLN_RST_CNT0_SIZE         (1u)
#define CapSense_BUTTON1_RX0_NEG_BSLN_RST_CNT0_PARAM_ID     (0x4600006Au)

#define CapSense_BUTTON1_RX0_IDAC_COMP0_VALUE               (CapSense_dsRam.snsList.button1[0u].idacComp[0u])
#define CapSense_BUTTON1_RX0_IDAC_COMP0_OFFSET              (107u)
#define CapSense_BUTTON1_RX0_IDAC_COMP0_SIZE                (1u)
#define CapSense_BUTTON1_RX0_IDAC_COMP0_PARAM_ID            (0x4000006Bu)

#define CapSense_SNS0_RX0_RAW0_VALUE                        (CapSense_dsRam.snsList.sns0[0u].raw[0u])
#define CapSense_SNS0_RX0_RAW0_OFFSET                       (108u)
#define CapSense_SNS0_RX0_RAW0_SIZE                         (2u)
#define CapSense_SNS0_RX0_RAW0_PARAM_ID                     (0x8300006Cu)

#define CapSense_SNS0_RX0_BSLN0_VALUE                       (CapSense_dsRam.snsList.sns0[0u].bsln[0u])
#define CapSense_SNS0_RX0_BSLN0_OFFSET                      (110u)
#define CapSense_SNS0_RX0_BSLN0_SIZE                        (2u)
#define CapSense_SNS0_RX0_BSLN0_PARAM_ID                    (0x8F00006Eu)

#define CapSense_SNS0_RX0_BSLN_EXT0_VALUE                   (CapSense_dsRam.snsList.sns0[0u].bslnExt[0u])
#define CapSense_SNS0_RX0_BSLN_EXT0_OFFSET                  (112u)
#define CapSense_SNS0_RX0_BSLN_EXT0_SIZE                    (1u)
#define CapSense_SNS0_RX0_BSLN_EXT0_PARAM_ID                (0x4D000070u)

#define CapSense_SNS0_RX0_DIFF_VALUE                        (CapSense_dsRam.snsList.sns0[0u].diff)
#define CapSense_SNS0_RX0_DIFF_OFFSET                       (114u)
#define CapSense_SNS0_RX0_DIFF_SIZE                         (2u)
#define CapSense_SNS0_RX0_DIFF_PARAM_ID                     (0x89000072u)

#define CapSense_SNS0_RX0_NEG_BSLN_RST_CNT0_VALUE           (CapSense_dsRam.snsList.sns0[0u].negBslnRstCnt[0u])
#define CapSense_SNS0_RX0_NEG_BSLN_RST_CNT0_OFFSET          (116u)
#define CapSense_SNS0_RX0_NEG_BSLN_RST_CNT0_SIZE            (1u)
#define CapSense_SNS0_RX0_NEG_BSLN_RST_CNT0_PARAM_ID        (0x4C000074u)

#define CapSense_SNS0_RX0_IDAC_COMP0_VALUE                  (CapSense_dsRam.snsList.sns0[0u].idacComp[0u])
#define CapSense_SNS0_RX0_IDAC_COMP0_OFFSET                 (117u)
#define CapSense_SNS0_RX0_IDAC_COMP0_SIZE                   (1u)
#define CapSense_SNS0_RX0_IDAC_COMP0_PARAM_ID               (0x4A000075u)

#define CapSense_SNS4_RX0_RAW0_VALUE                        (CapSense_dsRam.snsList.sns4[0u].raw[0u])
#define CapSense_SNS4_RX0_RAW0_OFFSET                       (118u)
#define CapSense_SNS4_RX0_RAW0_SIZE                         (2u)
#define CapSense_SNS4_RX0_RAW0_PARAM_ID                     (0x88000076u)

#define CapSense_SNS4_RX0_BSLN0_VALUE                       (CapSense_dsRam.snsList.sns4[0u].bsln[0u])
#define CapSense_SNS4_RX0_BSLN0_OFFSET                      (120u)
#define CapSense_SNS4_RX0_BSLN0_SIZE                        (2u)
#define CapSense_SNS4_RX0_BSLN0_PARAM_ID                    (0x87000078u)

#define CapSense_SNS4_RX0_BSLN_EXT0_VALUE                   (CapSense_dsRam.snsList.sns4[0u].bslnExt[0u])
#define CapSense_SNS4_RX0_BSLN_EXT0_OFFSET                  (122u)
#define CapSense_SNS4_RX0_BSLN_EXT0_SIZE                    (1u)
#define CapSense_SNS4_RX0_BSLN_EXT0_PARAM_ID                (0x4300007Au)

#define CapSense_SNS4_RX0_DIFF_VALUE                        (CapSense_dsRam.snsList.sns4[0u].diff)
#define CapSense_SNS4_RX0_DIFF_OFFSET                       (124u)
#define CapSense_SNS4_RX0_DIFF_SIZE                         (2u)
#define CapSense_SNS4_RX0_DIFF_PARAM_ID                     (0x8600007Cu)

#define CapSense_SNS4_RX0_NEG_BSLN_RST_CNT0_VALUE           (CapSense_dsRam.snsList.sns4[0u].negBslnRstCnt[0u])
#define CapSense_SNS4_RX0_NEG_BSLN_RST_CNT0_OFFSET          (126u)
#define CapSense_SNS4_RX0_NEG_BSLN_RST_CNT0_SIZE            (1u)
#define CapSense_SNS4_RX0_NEG_BSLN_RST_CNT0_PARAM_ID        (0x4200007Eu)

#define CapSense_SNS4_RX0_IDAC_COMP0_VALUE                  (CapSense_dsRam.snsList.sns4[0u].idacComp[0u])
#define CapSense_SNS4_RX0_IDAC_COMP0_OFFSET                 (127u)
#define CapSense_SNS4_RX0_IDAC_COMP0_SIZE                   (1u)
#define CapSense_SNS4_RX0_IDAC_COMP0_PARAM_ID               (0x4400007Fu)

#define CapSense_SNR_TEST_WIDGET_ID_VALUE                   (CapSense_dsRam.snrTestWidgetId)
#define CapSense_SNR_TEST_WIDGET_ID_OFFSET                  (128u)
#define CapSense_SNR_TEST_WIDGET_ID_SIZE                    (1u)
#define CapSense_SNR_TEST_WIDGET_ID_PARAM_ID                (0x67000080u)

#define CapSense_SNR_TEST_SENSOR_ID_VALUE                   (CapSense_dsRam.snrTestSensorId)
#define CapSense_SNR_TEST_SENSOR_ID_OFFSET                  (129u)
#define CapSense_SNR_TEST_SENSOR_ID_SIZE                    (1u)
#define CapSense_SNR_TEST_SENSOR_ID_PARAM_ID                (0x61000081u)

#define CapSense_SNR_TEST_SCAN_COUNTER_VALUE                (CapSense_dsRam.snrTestScanCounter)
#define CapSense_SNR_TEST_SCAN_COUNTER_OFFSET               (130u)
#define CapSense_SNR_TEST_SCAN_COUNTER_SIZE                 (2u)
#define CapSense_SNR_TEST_SCAN_COUNTER_PARAM_ID             (0x88000082u)

#define CapSense_SNR_TEST_RAW_COUNT0_VALUE                  (CapSense_dsRam.snrTestRawCount[0u])
#define CapSense_SNR_TEST_RAW_COUNT0_OFFSET                 (132u)
#define CapSense_SNR_TEST_RAW_COUNT0_SIZE                   (2u)
#define CapSense_SNR_TEST_RAW_COUNT0_PARAM_ID               (0x85000084u)


/*****************************************************************************/
/* Flash Data structure register definitions                                 */
/*****************************************************************************/
#define CapSense_BUTTON0_PTR2SNS_FLASH_VALUE                (CapSense_dsFlash.wdgtArray[0].ptr2SnsFlash)
#define CapSense_BUTTON0_PTR2SNS_FLASH_OFFSET               (0u)
#define CapSense_BUTTON0_PTR2SNS_FLASH_SIZE                 (4u)
#define CapSense_BUTTON0_PTR2SNS_FLASH_PARAM_ID             (0xD1000000u)

#define CapSense_BUTTON0_PTR2WD_RAM_VALUE                   (CapSense_dsFlash.wdgtArray[0].ptr2WdgtRam)
#define CapSense_BUTTON0_PTR2WD_RAM_OFFSET                  (4u)
#define CapSense_BUTTON0_PTR2WD_RAM_SIZE                    (4u)
#define CapSense_BUTTON0_PTR2WD_RAM_PARAM_ID                (0xD0000004u)

#define CapSense_BUTTON0_PTR2SNS_RAM_VALUE                  (CapSense_dsFlash.wdgtArray[0].ptr2SnsRam)
#define CapSense_BUTTON0_PTR2SNS_RAM_OFFSET                 (8u)
#define CapSense_BUTTON0_PTR2SNS_RAM_SIZE                   (4u)
#define CapSense_BUTTON0_PTR2SNS_RAM_PARAM_ID               (0xD3000008u)

#define CapSense_BUTTON0_PTR2FLTR_HISTORY_VALUE             (CapSense_dsFlash.wdgtArray[0].ptr2FltrHistory)
#define CapSense_BUTTON0_PTR2FLTR_HISTORY_OFFSET            (12u)
#define CapSense_BUTTON0_PTR2FLTR_HISTORY_SIZE              (4u)
#define CapSense_BUTTON0_PTR2FLTR_HISTORY_PARAM_ID          (0xD200000Cu)

#define CapSense_BUTTON0_PTR2DEBOUNCE_VALUE                 (CapSense_dsFlash.wdgtArray[0].ptr2DebounceArr)
#define CapSense_BUTTON0_PTR2DEBOUNCE_OFFSET                (16u)
#define CapSense_BUTTON0_PTR2DEBOUNCE_SIZE                  (4u)
#define CapSense_BUTTON0_PTR2DEBOUNCE_PARAM_ID              (0xD4000010u)

#define CapSense_BUTTON0_STATIC_CONFIG_VALUE                (CapSense_dsFlash.wdgtArray[0].staticConfig)
#define CapSense_BUTTON0_STATIC_CONFIG_OFFSET               (20u)
#define CapSense_BUTTON0_STATIC_CONFIG_SIZE                 (4u)
#define CapSense_BUTTON0_STATIC_CONFIG_PARAM_ID             (0xD5000014u)

#define CapSense_BUTTON0_TOTAL_NUM_SNS_VALUE                (CapSense_dsFlash.wdgtArray[0].totalNumSns)
#define CapSense_BUTTON0_TOTAL_NUM_SNS_OFFSET               (24u)
#define CapSense_BUTTON0_TOTAL_NUM_SNS_SIZE                 (2u)
#define CapSense_BUTTON0_TOTAL_NUM_SNS_PARAM_ID             (0x99000018u)

#define CapSense_BUTTON0_TYPE_VALUE                         (CapSense_dsFlash.wdgtArray[0].wdgtType)
#define CapSense_BUTTON0_TYPE_OFFSET                        (26u)
#define CapSense_BUTTON0_TYPE_SIZE                          (1u)
#define CapSense_BUTTON0_TYPE_PARAM_ID                      (0x5D00001Au)

#define CapSense_BUTTON0_NUM_COLS_VALUE                     (CapSense_dsFlash.wdgtArray[0].numCols)
#define CapSense_BUTTON0_NUM_COLS_OFFSET                    (27u)
#define CapSense_BUTTON0_NUM_COLS_SIZE                      (1u)
#define CapSense_BUTTON0_NUM_COLS_PARAM_ID                  (0x5B00001Bu)

#define CapSense_BUTTON0_NUM_ROWS_VALUE                     (CapSense_dsFlash.wdgtArray[0].numRows)
#define CapSense_BUTTON0_NUM_ROWS_OFFSET                    (28u)
#define CapSense_BUTTON0_NUM_ROWS_SIZE                      (1u)
#define CapSense_BUTTON0_NUM_ROWS_PARAM_ID                  (0x5000001Cu)

#define CapSense_BUTTON1_PTR2SNS_FLASH_VALUE                (CapSense_dsFlash.wdgtArray[1].ptr2SnsFlash)
#define CapSense_BUTTON1_PTR2SNS_FLASH_OFFSET               (32u)
#define CapSense_BUTTON1_PTR2SNS_FLASH_SIZE                 (4u)
#define CapSense_BUTTON1_PTR2SNS_FLASH_PARAM_ID             (0xD8010020u)

#define CapSense_BUTTON1_PTR2WD_RAM_VALUE                   (CapSense_dsFlash.wdgtArray[1].ptr2WdgtRam)
#define CapSense_BUTTON1_PTR2WD_RAM_OFFSET                  (36u)
#define CapSense_BUTTON1_PTR2WD_RAM_SIZE                    (4u)
#define CapSense_BUTTON1_PTR2WD_RAM_PARAM_ID                (0xD9010024u)

#define CapSense_BUTTON1_PTR2SNS_RAM_VALUE                  (CapSense_dsFlash.wdgtArray[1].ptr2SnsRam)
#define CapSense_BUTTON1_PTR2SNS_RAM_OFFSET                 (40u)
#define CapSense_BUTTON1_PTR2SNS_RAM_SIZE                   (4u)
#define CapSense_BUTTON1_PTR2SNS_RAM_PARAM_ID               (0xDA010028u)

#define CapSense_BUTTON1_PTR2FLTR_HISTORY_VALUE             (CapSense_dsFlash.wdgtArray[1].ptr2FltrHistory)
#define CapSense_BUTTON1_PTR2FLTR_HISTORY_OFFSET            (44u)
#define CapSense_BUTTON1_PTR2FLTR_HISTORY_SIZE              (4u)
#define CapSense_BUTTON1_PTR2FLTR_HISTORY_PARAM_ID          (0xDB01002Cu)

#define CapSense_BUTTON1_PTR2DEBOUNCE_VALUE                 (CapSense_dsFlash.wdgtArray[1].ptr2DebounceArr)
#define CapSense_BUTTON1_PTR2DEBOUNCE_OFFSET                (48u)
#define CapSense_BUTTON1_PTR2DEBOUNCE_SIZE                  (4u)
#define CapSense_BUTTON1_PTR2DEBOUNCE_PARAM_ID              (0xDD010030u)

#define CapSense_BUTTON1_STATIC_CONFIG_VALUE                (CapSense_dsFlash.wdgtArray[1].staticConfig)
#define CapSense_BUTTON1_STATIC_CONFIG_OFFSET               (52u)
#define CapSense_BUTTON1_STATIC_CONFIG_SIZE                 (4u)
#define CapSense_BUTTON1_STATIC_CONFIG_PARAM_ID             (0xDC010034u)

#define CapSense_BUTTON1_TOTAL_NUM_SNS_VALUE                (CapSense_dsFlash.wdgtArray[1].totalNumSns)
#define CapSense_BUTTON1_TOTAL_NUM_SNS_OFFSET               (56u)
#define CapSense_BUTTON1_TOTAL_NUM_SNS_SIZE                 (2u)
#define CapSense_BUTTON1_TOTAL_NUM_SNS_PARAM_ID             (0x90010038u)

#define CapSense_BUTTON1_TYPE_VALUE                         (CapSense_dsFlash.wdgtArray[1].wdgtType)
#define CapSense_BUTTON1_TYPE_OFFSET                        (58u)
#define CapSense_BUTTON1_TYPE_SIZE                          (1u)
#define CapSense_BUTTON1_TYPE_PARAM_ID                      (0x5401003Au)

#define CapSense_BUTTON1_NUM_COLS_VALUE                     (CapSense_dsFlash.wdgtArray[1].numCols)
#define CapSense_BUTTON1_NUM_COLS_OFFSET                    (59u)
#define CapSense_BUTTON1_NUM_COLS_SIZE                      (1u)
#define CapSense_BUTTON1_NUM_COLS_PARAM_ID                  (0x5201003Bu)

#define CapSense_BUTTON1_NUM_ROWS_VALUE                     (CapSense_dsFlash.wdgtArray[1].numRows)
#define CapSense_BUTTON1_NUM_ROWS_OFFSET                    (60u)
#define CapSense_BUTTON1_NUM_ROWS_SIZE                      (1u)
#define CapSense_BUTTON1_NUM_ROWS_PARAM_ID                  (0x5901003Cu)

#define CapSense_SNS0_PTR2SNS_FLASH_VALUE                   (CapSense_dsFlash.wdgtArray[2].ptr2SnsFlash)
#define CapSense_SNS0_PTR2SNS_FLASH_OFFSET                  (64u)
#define CapSense_SNS0_PTR2SNS_FLASH_SIZE                    (4u)
#define CapSense_SNS0_PTR2SNS_FLASH_PARAM_ID                (0xDA020040u)

#define CapSense_SNS0_PTR2WD_RAM_VALUE                      (CapSense_dsFlash.wdgtArray[2].ptr2WdgtRam)
#define CapSense_SNS0_PTR2WD_RAM_OFFSET                     (68u)
#define CapSense_SNS0_PTR2WD_RAM_SIZE                       (4u)
#define CapSense_SNS0_PTR2WD_RAM_PARAM_ID                   (0xDB020044u)

#define CapSense_SNS0_PTR2SNS_RAM_VALUE                     (CapSense_dsFlash.wdgtArray[2].ptr2SnsRam)
#define CapSense_SNS0_PTR2SNS_RAM_OFFSET                    (72u)
#define CapSense_SNS0_PTR2SNS_RAM_SIZE                      (4u)
#define CapSense_SNS0_PTR2SNS_RAM_PARAM_ID                  (0xD8020048u)

#define CapSense_SNS0_PTR2FLTR_HISTORY_VALUE                (CapSense_dsFlash.wdgtArray[2].ptr2FltrHistory)
#define CapSense_SNS0_PTR2FLTR_HISTORY_OFFSET               (76u)
#define CapSense_SNS0_PTR2FLTR_HISTORY_SIZE                 (4u)
#define CapSense_SNS0_PTR2FLTR_HISTORY_PARAM_ID             (0xD902004Cu)

#define CapSense_SNS0_PTR2DEBOUNCE_VALUE                    (CapSense_dsFlash.wdgtArray[2].ptr2DebounceArr)
#define CapSense_SNS0_PTR2DEBOUNCE_OFFSET                   (80u)
#define CapSense_SNS0_PTR2DEBOUNCE_SIZE                     (4u)
#define CapSense_SNS0_PTR2DEBOUNCE_PARAM_ID                 (0xDF020050u)

#define CapSense_SNS0_STATIC_CONFIG_VALUE                   (CapSense_dsFlash.wdgtArray[2].staticConfig)
#define CapSense_SNS0_STATIC_CONFIG_OFFSET                  (84u)
#define CapSense_SNS0_STATIC_CONFIG_SIZE                    (4u)
#define CapSense_SNS0_STATIC_CONFIG_PARAM_ID                (0xDE020054u)

#define CapSense_SNS0_TOTAL_NUM_SNS_VALUE                   (CapSense_dsFlash.wdgtArray[2].totalNumSns)
#define CapSense_SNS0_TOTAL_NUM_SNS_OFFSET                  (88u)
#define CapSense_SNS0_TOTAL_NUM_SNS_SIZE                    (2u)
#define CapSense_SNS0_TOTAL_NUM_SNS_PARAM_ID                (0x92020058u)

#define CapSense_SNS0_TYPE_VALUE                            (CapSense_dsFlash.wdgtArray[2].wdgtType)
#define CapSense_SNS0_TYPE_OFFSET                           (90u)
#define CapSense_SNS0_TYPE_SIZE                             (1u)
#define CapSense_SNS0_TYPE_PARAM_ID                         (0x5602005Au)

#define CapSense_SNS0_NUM_COLS_VALUE                        (CapSense_dsFlash.wdgtArray[2].numCols)
#define CapSense_SNS0_NUM_COLS_OFFSET                       (91u)
#define CapSense_SNS0_NUM_COLS_SIZE                         (1u)
#define CapSense_SNS0_NUM_COLS_PARAM_ID                     (0x5002005Bu)

#define CapSense_SNS0_NUM_ROWS_VALUE                        (CapSense_dsFlash.wdgtArray[2].numRows)
#define CapSense_SNS0_NUM_ROWS_OFFSET                       (92u)
#define CapSense_SNS0_NUM_ROWS_SIZE                         (1u)
#define CapSense_SNS0_NUM_ROWS_PARAM_ID                     (0x5B02005Cu)

#define CapSense_SNS4_PTR2SNS_FLASH_VALUE                   (CapSense_dsFlash.wdgtArray[3].ptr2SnsFlash)
#define CapSense_SNS4_PTR2SNS_FLASH_OFFSET                  (96u)
#define CapSense_SNS4_PTR2SNS_FLASH_SIZE                    (4u)
#define CapSense_SNS4_PTR2SNS_FLASH_PARAM_ID                (0xD3030060u)

#define CapSense_SNS4_PTR2WD_RAM_VALUE                      (CapSense_dsFlash.wdgtArray[3].ptr2WdgtRam)
#define CapSense_SNS4_PTR2WD_RAM_OFFSET                     (100u)
#define CapSense_SNS4_PTR2WD_RAM_SIZE                       (4u)
#define CapSense_SNS4_PTR2WD_RAM_PARAM_ID                   (0xD2030064u)

#define CapSense_SNS4_PTR2SNS_RAM_VALUE                     (CapSense_dsFlash.wdgtArray[3].ptr2SnsRam)
#define CapSense_SNS4_PTR2SNS_RAM_OFFSET                    (104u)
#define CapSense_SNS4_PTR2SNS_RAM_SIZE                      (4u)
#define CapSense_SNS4_PTR2SNS_RAM_PARAM_ID                  (0xD1030068u)

#define CapSense_SNS4_PTR2FLTR_HISTORY_VALUE                (CapSense_dsFlash.wdgtArray[3].ptr2FltrHistory)
#define CapSense_SNS4_PTR2FLTR_HISTORY_OFFSET               (108u)
#define CapSense_SNS4_PTR2FLTR_HISTORY_SIZE                 (4u)
#define CapSense_SNS4_PTR2FLTR_HISTORY_PARAM_ID             (0xD003006Cu)

#define CapSense_SNS4_PTR2DEBOUNCE_VALUE                    (CapSense_dsFlash.wdgtArray[3].ptr2DebounceArr)
#define CapSense_SNS4_PTR2DEBOUNCE_OFFSET                   (112u)
#define CapSense_SNS4_PTR2DEBOUNCE_SIZE                     (4u)
#define CapSense_SNS4_PTR2DEBOUNCE_PARAM_ID                 (0xD6030070u)

#define CapSense_SNS4_STATIC_CONFIG_VALUE                   (CapSense_dsFlash.wdgtArray[3].staticConfig)
#define CapSense_SNS4_STATIC_CONFIG_OFFSET                  (116u)
#define CapSense_SNS4_STATIC_CONFIG_SIZE                    (4u)
#define CapSense_SNS4_STATIC_CONFIG_PARAM_ID                (0xD7030074u)

#define CapSense_SNS4_TOTAL_NUM_SNS_VALUE                   (CapSense_dsFlash.wdgtArray[3].totalNumSns)
#define CapSense_SNS4_TOTAL_NUM_SNS_OFFSET                  (120u)
#define CapSense_SNS4_TOTAL_NUM_SNS_SIZE                    (2u)
#define CapSense_SNS4_TOTAL_NUM_SNS_PARAM_ID                (0x9B030078u)

#define CapSense_SNS4_TYPE_VALUE                            (CapSense_dsFlash.wdgtArray[3].wdgtType)
#define CapSense_SNS4_TYPE_OFFSET                           (122u)
#define CapSense_SNS4_TYPE_SIZE                             (1u)
#define CapSense_SNS4_TYPE_PARAM_ID                         (0x5F03007Au)

#define CapSense_SNS4_NUM_COLS_VALUE                        (CapSense_dsFlash.wdgtArray[3].numCols)
#define CapSense_SNS4_NUM_COLS_OFFSET                       (123u)
#define CapSense_SNS4_NUM_COLS_SIZE                         (1u)
#define CapSense_SNS4_NUM_COLS_PARAM_ID                     (0x5903007Bu)

#define CapSense_SNS4_NUM_ROWS_VALUE                        (CapSense_dsFlash.wdgtArray[3].numRows)
#define CapSense_SNS4_NUM_ROWS_OFFSET                       (124u)
#define CapSense_SNS4_NUM_ROWS_SIZE                         (1u)
#define CapSense_SNS4_NUM_ROWS_PARAM_ID                     (0x5203007Cu)


#endif /* End CY_SENSE_CapSense_REGISTER_MAP_H */


/* [] END OF FILE */
