//---------------------------------------------------------------------------------------------------------------------
//
// WTMEC CORPORATION CONFIDENTIAL
// ________________________________
//
// [2024] Wtmec Corporation
// All Rights Reserved.
//
// NOTICE: This is an unpublished work of authorship, which contains trade secrets.
// Wtmec Corporation owns all rights to this work and intends to maintain it in confidence to
// preserve its trade secret status. Wtmec Corporation reserves the right, under the copyright
// laws of the United States or those of any other country that may have jurisdiction, to protect
// this work as an unpublished work, in the event of an inadvertent or deliberate unauthorized
// publication. Wtmec Corporation also reserves its rights under all copyright laws to protect
// this work as a published work, when appropriate. Those having access to this work may not copy
// it, use it, modify it, or disclose the information contained in it without the written
// authorization of Wtmec Corporation.
//
//---------------------------------------------------------------------------------------------------------------------
#if !defined(DEVICE_H)
#define DEVICE_H (1)

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <cmsis_gcc.h>

#if defined(S32K312)
#include <S32K312.h>
#endif

#if defined(S32K314)
#include <S32K314.h>
#endif

#include <hse_interface.h>

#endif // DEVICE_H
