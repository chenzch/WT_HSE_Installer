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
#include "device.h"
#include "misc.h"

#define UTEST_BASE_ADDR (0x1B000000UL)

void FunctionalReset(void) {

    __DSB();
    __ISB();

    MC_ME.MODE_CONF.B.FUNC_RST = 1;
    MC_ME.MODE_UPD.B.MODE_UPD  = 1;
    MC_ME.CTL_KEY.B.KEY        = (uint32_t)0x00005AF0U;
    MC_ME.CTL_KEY.B.KEY        = (uint32_t)0x0000A50FU;
}

bool checkHseFwFeatureFlagEnabled(void) {
    uint64_t default_val      = 0xFFFFFFFFFFFFFFFFUL;
    uint64_t hsefwfeatureflag = *(uint64_t *)UTEST_BASE_ADDR;

    //check the default value
    if (default_val != hsefwfeatureflag) {
        return true;
    } else {
        return false;
    }
}

bool EnableHseFeature(void) {
    register uint8_t domain_id = XRDC.HWCFG1.B.DID;

    bool status;

    /* unlock UTEST data flash sector */
    PFLASH.PFCBLKU_SPELOCK[0].B.SLCK = 0;

    /* entry semaphore loop */
    do {
        PFLASH.PFCPGM_PEADR_L.B.PEADR_L = (uint32_t)UTEST_BASE_ADDR;
    } while (FLASH.MCR.B.PEID != domain_id);

    /* clear any pending program & erase errors */
    FLASH.MCRS.B.PEP = 1;
    FLASH.MCRS.B.PES = 1;

    FLASH.DATA[0].B.PDATA = 0xDDCCBBAA;
    FLASH.DATA[1].B.PDATA = 0xAABBCCDD;

    FLASH.MCR.B.PGM = 1;
    FLASH.MCR.B.EHV = 1;
    while (!FLASH.MCRS.B.DONE)
        ;
    FLASH.MCR.B.EHV = 0;
    status          = FLASH.MCRS.B.PEG;
    FLASH.MCR.B.PGM = 0;

    return status;
}

bool IsPOR(void) {
    if (MC_RGM.DES.B.F_POR) {
        MC_RGM_DES_tag value;
        value.R       = 0;
        value.B.F_POR = 1;
        MC_RGM.DES    = value;
        return true;
    } else {
        return false;
    }
}

bool CheckSBAF(uint8_t socType) {
    /*
     * 05 - S32K344, S32K324, S32K314
     * 0C - S32K311, S32K310
     * 0D - S32K312, S32K342, S32K322, S32K341
     * 0E - S32K358, S32K348, S32K338, S32K328, S32K336, S32K356
     * 0F - S32K396, S32K376, S32K394, S32K374
     * 10 - S32K388
     */
    bool     ret     = false;
    uint64_t SBAFVer = *(uint64_t *)0x4039C020;
    switch (socType) {
    case 0x05: // S32K344, S32K324, S32K314
        if ((SBAFVer == (0x0004090000000500UL)) || (SBAFVer == (0x03000A0000000500UL))) {
            ret = true;
        }
        break;
    case 0x0D: // S32K312, S32K342, S32K322, S32K341
        if ((SBAFVer == (0x0000080000000D00UL)) || (SBAFVer == (0x0100090000000D00UL))) {
            ret = true;
        }
        break;
    case 0x0E: // S32K358
        if ((SBAFVer == (0x03000C0000000E00UL))) {
            ret = true;
        }
        break;
    default:
        break;
    }
    return ret;
}

bool DCMDone(void) {
    return DCM.DCMSTAT.B.DCMDONE;
}

bool DCMLowAddress(void) {
    return (DCM_DCMSTAT & (1 << 17)) ? false : true;
}
