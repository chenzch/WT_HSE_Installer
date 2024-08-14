/**************************************************************************/ /**
 * @file     core_cm7.h
 * @brief    CMSIS Cortex-M7 Core Peripheral Access Layer Header File
 * @version  V5.2.0
 * @date     04. April 2023
 ******************************************************************************/
/*
 * Copyright (c) 2009-2023 Arm Limited. All rights reserved.
 * Copyright 2018-2019, 2024 NXP
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

#if defined(__ICCARM__)
#pragma system_include /* treat file as system include file for MISRA check */
#elif defined(__clang__)
#pragma clang system_header /* treat file as system include file */
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  \page CMSIS_MISRA_Exceptions  MISRA-C:2004 Compliance Exceptions
  CMSIS violates the following MISRA-C:2004 rules:

   \li Required Rule 8.5, object/function definition in header file.<br>
     Function definitions in header files are used to allow 'inlining'.

   \li Required Rule 18.4, declaration of union type or object of union type: '{...}'.<br>
     Unions are used for effective representation of core registers.

   \li Advisory Rule 19.7, Function-like macro defined.<br>
     Function-like macros are used to allow more efficient code.
 */

/*******************************************************************************
 *                 CMSIS definitions
 ******************************************************************************/
/**
  \ingroup Cortex_M7
  @{
 */

#include "cmsis_gcc.h" /* CMSIS compiler specific defines */

/* Memory mapping of Core Hardware */

/* IO definitions (access restrictions to peripheral registers) */
/**
    \defgroup CMSIS_glob_defs CMSIS Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.
*/
/* following defines should be used for structure members */
#define __IM  volatile const /*! Defines 'read only' structure member permissions */
#define __OM  volatile       /*! Defines 'write only' structure member permissions */
#define __IOM volatile       /*! Defines 'read / write' structure member permissions */

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_SCB     System Control Block (SCB)
  \brief    Type definitions for the System Control Block Registers
  @{
 */

/**
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct {
    __IM uint32_t  CPUID; /*!< Offset: 0x000 (R/ )  CPUID Base Register */
    __IOM uint32_t ICSR;  /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
    __IOM uint32_t VTOR;  /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
    __IOM uint32_t
        AIRCR; /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
    __IOM uint32_t SCR; /*!< Offset: 0x010 (R/W)  System Control Register */
    __IOM uint32_t CCR; /*!< Offset: 0x014 (R/W)  Configuration Control Register */
    __IOM uint8_t  SHPR
        [12U]; /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
    __IOM uint32_t SHCSR; /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
    __IOM uint32_t CFSR;  /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
    __IOM uint32_t HFSR;  /*!< Offset: 0x02C (R/W)  HardFault Status Register */
    __IOM uint32_t DFSR;  /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
    __IOM uint32_t MMFAR; /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
    __IOM uint32_t BFAR;  /*!< Offset: 0x038 (R/W)  BusFault Address Register */
    __IOM uint32_t AFSR;  /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
    __IM uint32_t  ID_PFR[2U];  /*!< Offset: 0x040 (R/ )  Processor Feature Register */
    __IM uint32_t  ID_DFR;      /*!< Offset: 0x048 (R/ )  Debug Feature Register */
    __IM uint32_t  ID_AFR;      /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
    __IM uint32_t  ID_MFR[4U];  /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
    __IM uint32_t  ID_ISAR[5U]; /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
    uint32_t       RESERVED0[1U];
    __IM uint32_t  CLIDR;  /*!< Offset: 0x078 (R/ )  Cache Level ID register */
    __IM uint32_t  CTR;    /*!< Offset: 0x07C (R/ )  Cache Type register */
    __IM uint32_t  CCSIDR; /*!< Offset: 0x080 (R/ )  Cache Size ID Register */
    __IOM uint32_t CSSELR; /*!< Offset: 0x084 (R/W)  Cache Size Selection Register */
    __IOM uint32_t CPACR;  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
    uint32_t       RESERVED3[93U];
    __OM uint32_t  STIR; /*!< Offset: 0x200 ( /W)  Software Triggered Interrupt Register */
    uint32_t       RESERVED4[15U];
    __IM uint32_t  MVFR0; /*!< Offset: 0x240 (R/ )  Media and VFP Feature Register 0 */
    __IM uint32_t  MVFR1; /*!< Offset: 0x244 (R/ )  Media and VFP Feature Register 1 */
    __IM uint32_t  MVFR2; /*!< Offset: 0x248 (R/ )  Media and VFP Feature Register 2 */
    uint32_t       RESERVED5[1U];
    __OM uint32_t  ICIALLU; /*!< Offset: 0x250 ( /W)  I-Cache Invalidate All to PoU */
    uint32_t       RESERVED6[1U];
    __OM uint32_t  ICIMVAU;  /*!< Offset: 0x258 ( /W)  I-Cache Invalidate by MVA to PoU */
    __OM uint32_t  DCIMVAC;  /*!< Offset: 0x25C ( /W)  D-Cache Invalidate by MVA to PoC */
    __OM uint32_t  DCISW;    /*!< Offset: 0x260 ( /W)  D-Cache Invalidate by Set-way */
    __OM uint32_t  DCCMVAU;  /*!< Offset: 0x264 ( /W)  D-Cache Clean by MVA to PoU */
    __OM uint32_t  DCCMVAC;  /*!< Offset: 0x268 ( /W)  D-Cache Clean by MVA to PoC */
    __OM uint32_t  DCCSW;    /*!< Offset: 0x26C ( /W)  D-Cache Clean by Set-way */
    __OM uint32_t  DCCIMVAC; /*!< Offset: 0x270 ( /W)  D-Cache Clean and Invalidate by MVA to PoC */
    __OM uint32_t  DCCISW;   /*!< Offset: 0x274 ( /W)  D-Cache Clean and Invalidate by Set-way */
    __OM uint32_t  BPIALL;   /*!< Offset: 0x278 ( /W)  Branch Predictor Invalidate All */
    uint32_t       RESERVED7[5U];
    __IOM uint32_t
        ITCMCR; /*!< Offset: 0x290 (R/W)  Instruction Tightly-Coupled Memory Control Register */
    __IOM uint32_t
        DTCMCR; /*!< Offset: 0x294 (R/W)  Data Tightly-Coupled Memory Control Registers */
    __IOM uint32_t AHBPCR; /*!< Offset: 0x298 (R/W)  AHBP Control Register */
    __IOM uint32_t CACR;   /*!< Offset: 0x29C (R/W)  L1 Cache Control Register */
    __IOM uint32_t AHBSCR; /*!< Offset: 0x2A0 (R/W)  AHB Slave Control Register */
    uint32_t       RESERVED8[1U];
    __IOM uint32_t ABFSR; /*!< Offset: 0x2A8 (R/W)  Auxiliary Bus Fault Status Register */
} SCB_Type;

#define SCS_BASE (0xE000E000UL)        /*!< System Control Space Base Address */
#define SCB_BASE (SCS_BASE + 0x0D00UL) /*!< System Control Block Base Address */

#define SCB ((SCB_Type *)SCB_BASE) /*!< SCB configuration struct */

/*@} */

#ifdef __cplusplus
}
#endif
