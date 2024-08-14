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
} SCB_Type;

#define SCB_BASE (0xE000ED00UL) /*!< System Control Block Base Address */
#define SCB ((SCB_Type *)SCB_BASE) /*!< SCB configuration struct */

/*@} */

#ifdef __cplusplus
}
#endif
