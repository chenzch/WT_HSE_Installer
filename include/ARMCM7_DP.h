/**************************************************************************//**
 * @file     ARMCM7_DP.h
 * @brief    CMSIS Core Peripheral Access Layer Header File for
 *           ARMCM7 Device (configured for CM7 with double precision FPU)
 * @version  V5.3.3
 * @date     01. May 2023
 ******************************************************************************/
/*
 * Copyright (c) 2009-2020 Arm Limited. All rights reserved.
 * Copyright 2020-2021, 2024 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ARMCM7_DP_H
#define ARMCM7_DP_H

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS 229                /**< Number of interrupts in the Vector table */

typedef enum IRQn
{
/* -------------------  Processor Exceptions Numbers  ----------------------------- */
  NonMaskableInt_IRQn           = -14,     /*  2 Non Maskable Interrupt */
  HardFault_IRQn                = -13,     /*  3 HardFault Interrupt */
  MemoryManagement_IRQn         = -12,     /*  4 Memory Management Interrupt */
  BusFault_IRQn                 = -11,     /*  5 Bus Fault Interrupt */
  UsageFault_IRQn               = -10,     /*  6 Usage Fault Interrupt */
  SVCall_IRQn                   =  -5,     /* 11 SVC Interrupt */
  DebugMonitor_IRQn             =  -4,     /* 12 Debug Monitor Interrupt */
  PendSV_IRQn                   =  -2,     /* 14 Pend SV Interrupt */
  SysTick_IRQn                  =  -1,     /* 15 System Tick Interrupt */

/* -------------------  Processor Interrupt Numbers  ------------------------------ */
  /* Device specific interrupts */
  INT0_IRQn                    = 0,                /**< CPU to CPU int0 */
  INT1_IRQn                    = 1,                /**< CPU to CPU int1 */
  INT2_IRQn                    = 2,                /**< CPU to CPU int2 */
  INT3_IRQn                    = 3,                /**< CPU to CPU int3 */
  DMATCD0_IRQn                 = 4,                /**< DMA transfer complete and error CH0 */
  DMATCD1_IRQn                 = 5,                /**< DMA transfer complete and error CH1 */
  DMATCD2_IRQn                 = 6,                /**< DMA transfer complete and error CH2 */
  DMATCD3_IRQn                 = 7,                /**< DMA transfer complete and error CH3 */
  DMATCD4_IRQn                 = 8,                /**< DMA transfer complete and error CH4 */
  DMATCD5_IRQn                 = 9,                /**< DMA transfer complete and error CH5 */
  DMATCD6_IRQn                 = 10,               /**< DMA transfer complete and error CH6 */
  DMATCD7_IRQn                 = 11,               /**< DMA transfer complete and error CH7 */
  DMATCD8_IRQn                 = 12,               /**< DMA transfer complete and error CH8 */
  DMATCD9_IRQn                 = 13,               /**< DMA transfer complete and error CH9 */
  DMATCD10_IRQn                = 14,               /**< DMA transfer complete and error CH10 */
  DMATCD11_IRQn                = 15,               /**< DMA transfer complete and error CH11 */
  DMATCD12_IRQn                = 16,               /**< DMA transfer complete and error CH12 */
  DMATCD13_IRQn                = 17,               /**< DMA transfer complete and error CH13 */
  DMATCD14_IRQn                = 18,               /**< DMA transfer complete and error CH14 */
  DMATCD15_IRQn                = 19,               /**< DMA transfer complete and error CH15 */
  DMATCD16_IRQn                = 20,               /**< DMA transfer complete and error CH16 */
  DMATCD17_IRQn                = 21,               /**< DMA transfer complete and error CH17 */
  DMATCD18_IRQn                = 22,               /**< DMA transfer complete and error CH18 */
  DMATCD19_IRQn                = 23,               /**< DMA transfer complete and error CH19 */
  DMATCD20_IRQn                = 24,               /**< DMA transfer complete and error CH20 */
  DMATCD21_IRQn                = 25,               /**< DMA transfer complete and error CH21 */
  DMATCD22_IRQn                = 26,               /**< DMA transfer complete and error CH22 */
  DMATCD23_IRQn                = 27,               /**< DMA transfer complete and error CH23 */
  DMATCD24_IRQn                = 28,               /**< DMA transfer complete and error CH24 */
  DMATCD25_IRQn                = 29,               /**< DMA transfer complete and error CH25 */
  DMATCD26_IRQn                = 30,               /**< DMA transfer complete and error CH26 */
  DMATCD27_IRQn                = 31,               /**< DMA transfer complete and error CH27 */
  DMATCD28_IRQn                = 32,               /**< DMA transfer complete and error CH28 */
  DMATCD29_IRQn                = 33,               /**< DMA transfer complete and error CH29 */
  DMATCD30_IRQn                = 34,               /**< DMA transfer complete and error CH30 */
  DMATCD31_IRQn                = 35,               /**< DMA transfer complete and error CH31 */
  ERM_0_IRQn                   = 36,               /**< Single bit ECC error */
  ERM_1_IRQn                   = 37,               /**< Multi bit ECC error */
  MCM_IRQn                     = 38,               /**< Multi bit ECC error */
  STM0_IRQn                    = 39,               /**< Single interrupt vector for all four channels */
  STM1_IRQn                    = 40,               /**< Single interrupt vector for all four channels */
  SWT0_IRQn                    = 42,               /**< Platform watchdog initial time-out */
  CTI0_IRQn                    = 45,               /**< CTI Interrupt 0 */
  FLASH_0_IRQn                 = 48,               /**< Program or erase operation is completed */
  FLASH_1_IRQn                 = 49,               /**< Main watchdog timeout interrupt */
  FLASH_2_IRQn                 = 50,               /**< Alternate watchdog timeout interrupt */
  RGM_IRQn                     = 51,               /**< Interrupt request to the system */
  PMC_IRQn                     = 52,               /**< One interrupt for all LVDs, One interrupt for all HVDs */
  SIUL_0_IRQn                  = 53,               /**< External Interrupt Vector 0 */
  SIUL_1_IRQn                  = 54,               /**< External Interrupt Vector 1 */
  SIUL_2_IRQn                  = 55,               /**< External Interrupt Vector 2 */
  SIUL_3_IRQn                  = 56,               /**< External Interrupt Vector 3 */
  EMIOS0_0_IRQn                = 61,               /**< Interrupt request 23,22,21,20 */
  EMIOS0_1_IRQn                = 62,               /**< Interrupt request 19,18,17,16 */
  EMIOS0_2_IRQn                = 63,               /**< Interrupt request 15,14,13,12 */
  EMIOS0_3_IRQn                = 64,               /**< Interrupt request 11,10,9,8 */
  EMIOS0_4_IRQn                = 65,               /**< Interrupt request 7,6,5,4 */
  EMIOS0_5_IRQn                = 66,               /**< Interrupt request 3,2,1,0 */
  EMIOS1_0_IRQn                = 69,               /**< Interrupt request 23,22,21,20 */
  EMIOS1_1_IRQn                = 70,               /**< Interrupt request 19,18,17,16 */
  EMIOS1_2_IRQn                = 71,               /**< Interrupt request 15,14,13,12 */
  EMIOS1_3_IRQn                = 72,               /**< Interrupt request 11,10,9,8 */
  EMIOS1_4_IRQn                = 73,               /**< Interrupt request 7,6,5,4 */
  EMIOS1_5_IRQn                = 74,               /**< Interrupt request 3,2,1,0 */
  EMIOS2_0_IRQn                = 77,               /**< Interrupt request 23,22,21,20 */
  EMIOS2_1_IRQn                = 78,               /**< Interrupt request 19,18,17,16 */
  EMIOS2_2_IRQn                = 79,               /**< Interrupt request 15,14,13,12 */
  EMIOS2_3_IRQn                = 80,               /**< Interrupt request 11,10,9,8 */
  EMIOS2_4_IRQn                = 81,               /**< Interrupt request 7,6,5,4 */
  EMIOS2_5_IRQn                = 82,               /**< Interrupt request 3,2,1,0 */
  WKPU_IRQn                    = 83,               /**< Interrupts from pad group 0,1,2,3, Interrupts from pad group 0_64, Interrupts from pad group 1_64, Interrupts from pad group 2_64, Interrupts from pad group 3_64 */
  CMU0_IRQn                    = 84,               /**< CMU0 interrupt */
  CMU1_IRQn                    = 85,               /**< CMU1 interrupt */
  CMU2_IRQn                    = 86,               /**< CMU2 interrupt */
  BCTU_IRQn                    = 87,               /**< An interrupt is requested when a conversion is issued to the ADC, An interrupt is requested when new data is available from ADC0 conversion, An interrupt is requested when new data is available from ADC1 conversion, An interrupt is requested when new data is available from ADC2 conversion, An interrupt is requested when the last command of a list is issued to the ADC,An Interrupt output for FIFO1,An Interrupt output for FIFO2 */
  LCU0_IRQn                    = 92,               /**< Interrupt 0, Interrupt 1 Interrupt 2 */
  LCU1_IRQn                    = 93,               /**< Interrupt 0, Interrupt 1 Interrupt 2 */
  PIT0_IRQn                    = 96,               /**< Interrupt for Channel0,Interrupt for Channel1,Interrupt for Channel2,Interrupt for Channel3,Interrupt for Channel4 */
  PIT1_IRQn                    = 97,               /**< Interrupt for Channel0,Interrupt for Channel1,Interrupt for Channel2,Interrupt for Channel3 */
  PIT2_IRQn                    = 98,               /**< Interrupt for Channel0,Interrupt for Channel1,Interrupt for Channel2,Interrupt for Channel3 */
  RTC_IRQn                     = 102,              /**< RTCF or ROVRF interrupt to be serviced by the system controller, APIF interrupt to be serviced by the system controller */
  EMAC_0_IRQn                  = 105,              /**< Common interrupt */
  EMAC_1_IRQn                  = 106,              /**< Tx interrupt 0, Tx interrupt 1 */
  EMAC_2_IRQn                  = 107,              /**< Rx interrupt 0, Rx interrupt 1 */
  EMAC_3_IRQn                  = 108,              /**< Safety interrupt correctable, Safety interrupt un-correctable */
  FlexCAN0_0_IRQn              = 109,              /**< Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN0_1_IRQn              = 110,              /**< Message Buffer Interrupt line 0-31,ORed Interrupt for Message Buffers */
  FlexCAN0_2_IRQn              = 111,              /**< Message Buffer Interrupt line 32-63 */
  FlexCAN0_3_IRQn              = 112,              /**< Message Buffer Interrupt line 64-95 */
  FlexCAN1_0_IRQn              = 113,              /**< Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN1_1_IRQn              = 114,              /**< Message Buffer Interrupt line 0-31 */
  FlexCAN1_2_IRQn              = 115,              /**< Message Buffer Interrupt line 32-63 */
  FlexCAN2_0_IRQn              = 116,              /**< Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN2_1_IRQn              = 117,              /**< Message Buffer Interrupt line 0-31 */
  FlexCAN2_2_IRQn              = 118,              /**< Message Buffer Interrupt line 32-63 */
  FlexCAN3_0_IRQn              = 119,              /**< Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN3_1_IRQn              = 120,              /**< Message Buffer Interrupt line 0-31 */
  FlexCAN4_0_IRQn              = 121,              /**< Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN4_1_IRQn              = 122,              /**< Message Buffer Interrupt line 0-31 */
  FlexCAN5_0_IRQn              = 123,              /**< Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN5_1_IRQn              = 124,              /**< Message Buffer Interrupt line 0-31 */
  FLEXIO_IRQn                  = 139,              /**< FlexIO Interrupt */
  LPUART0_IRQn                 = 141,              /**< TX and RX interrupt */
  LPUART1_IRQn                 = 142,              /**< TX and RX interrupt */
  LPUART2_IRQn                 = 143,              /**< TX and RX interrupt */
  LPUART3_IRQn                 = 144,              /**< TX and RX interrupt */
  LPUART4_IRQn                 = 145,              /**< TX and RX interrupt */
  LPUART5_IRQn                 = 146,              /**< TX and RX interrupt */
  LPUART6_IRQn                 = 147,              /**< TX and RX interrupt */
  LPUART7_IRQn                 = 148,              /**< TX and RX interrupt */
  LPUART8_IRQn                 = 149,              /**< TX and RX interrupt */
  LPUART9_IRQn                 = 150,              /**< TX and RX interrupt */
  LPUART10_IRQn                = 151,              /**< TX and RX interrupt */
  LPUART11_IRQn                = 152,              /**< TX and RX interrupt */
  LPUART12_IRQn                = 153,              /**< TX and RX interrupt */
  LPUART13_IRQn                = 154,              /**< TX and RX interrupt */
  LPUART14_IRQn                = 155,              /**< TX and RX interrupt */
  LPUART15_IRQn                = 156,              /**< TX and RX interrupt */
  LPI2C0_IRQn                  = 161,              /**< LPI2C Master Interrupt, LPI2C Interrupt */
  LPI2C1_IRQn                  = 162,              /**< LPI2C Master Interrupt, LPI2C Interrupt */
  LPSPI0_IRQn                  = 165,              /**< LPSPI Interrupt */
  LPSPI1_IRQn                  = 166,              /**< LPSPI Interrupt */
  LPSPI2_IRQn                  = 167,              /**< LPSPI Interrupt */
  LPSPI3_IRQn                  = 168,              /**< LPSPI Interrupt */
  LPSPI4_IRQn                  = 169,              /**< LPSPI Interrupt */
  LPSPI5_IRQn                  = 170,              /**< LPSPI Interrupt */
  QSPI_IRQn                    = 173,              /**< TX Buffer Fill interrupt, Transfer Complete / Transaction Finished, RX Buffer Drain interrupt, Buffer Overflow / Underrun interrupt, Serial Flash Communication Error interrupt, All interrupts ORed output */
  SAI0_IRQn                    = 174,              /**< RX interrupt,TX interrupt */
  SAI1_IRQn                    = 175,              /**< RX interrupt,TX interrupt */
  JDC_IRQn                     = 178,              /**< Indicates new data to be read from JIN_IPS register or can be written to JOUT_IPS register */
  ADC0_IRQn                    = 180,              /**< End of conversion, Error interrupt, Watchdog interrupt */
  ADC1_IRQn                    = 181,              /**< End of conversion, Error interrupt, Watchdog interrupt */
  ADC2_IRQn                    = 182,              /**< End of conversion, Error interrupt, Watchdog interrupt */
  LPCMP0_IRQn                  = 183,              /**< Async interrupt */
  LPCMP1_IRQn                  = 184,              /**< Async interrupt */
  LPCMP2_IRQn                  = 185,              /**< Async interrupt */
  FCCU_0_IRQn                  = 189,              /**< Interrupt request(ALARM state) */
  FCCU_1_IRQn                  = 190,              /**< Interrupt request(miscellaneous conditions) */
  STCU_LBIST_MBIST_IRQn        = 191,              /**< Interrupt request(miscellaneous conditions) */
  HSE_MU0_TX_IRQn              = 192,              /**< ORed TX interrupt to MU-0 */
  HSE_MU0_RX_IRQn              = 193,              /**< ORed RX interrupt to MU-0 */
  HSE_MU0_ORED_IRQn            = 194,              /**< ORed general purpose interrupt request to MU-0 */
  HSE_MU1_TX_IRQn              = 195,              /**< ORed TX interrupt to MU-1 */
  HSE_MU1_RX_IRQn              = 196,              /**< ORed RX interrupt to MU-1 */
  HSE_MU1_ORED_IRQn            = 197,              /**< ORed general purpose interrupt request to MU-1 */
  SoC_PLL_IRQn                 = 212               /**< PLL LOL interrupt */
} IRQn_Type;


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#elif defined (__ghs__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* --------  Configuration of Core Peripherals  ----------------------------------- */
#define __CM7_REV                 0x0000U   /* Core revision r0p0 */
#define __MPU_PRESENT             1U        /* MPU present */
#define __VTOR_PRESENT            1U        /* VTOR present */
#define __NVIC_PRIO_BITS          3U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1U        /* FPU present */
#define __FPU_DP                  1U        /* double precision FPU */
#define __ICACHE_PRESENT          1U        /* Instruction Cache present */
#define __DCACHE_PRESENT          1U        /* Data Cache present */
#define __DTCM_PRESENT            1U        /* Data Tightly Coupled Memory present */
#define __ECC_PRESENT             1U
#include "core_cm7.h"                       /* Processor and core peripherals */
#include "system_ARMCM7.h"                  /* System Header */



/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#elif defined (__ghs__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


#ifdef __cplusplus
}
#endif

#endif  /* ARMCM7_DP_H */
