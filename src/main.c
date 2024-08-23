/* Copyright 2023 NXP */
/* License: BSD 3-clause
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/
/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "device.h"
#include "misc.h"
#include "mu.h"

extern uint32_t __HSE_BIN_START;

int main(void) {
    if (IsPOR()) {
        ((LPRAM_Status)&__SRAM_STATUS_START)->raw[0] = 0;
        ((LPRAM_Status)&__SRAM_STATUS_START)->raw[1] = 0;
        Status_Data.status                           = RAM_STATUS_UNKNWON;
        Status_Data.firstBlock                       = true;
    }

    switch (Status_Data.status) {
    case RAM_STATUS_UNKNWON:
        if (checkHseFwFeatureFlagEnabled()) {
            Status_Data.status = RAM_STATUS_UTEST_OK;
        } else {
            EnableHseFeature();
            FunctionalReset();
        }
        /* no break */
    case RAM_STATUS_UTEST_OK: {
        uint32_t WaitCount = 770000U;
        while (!MU_GetHseStatus()) {
            if (--WaitCount == 0) {
                if (HSE_GPR_3 & HSE_GPR_3_FW_PRESENT) {
                } else {
                    DCM_GPR_DCMRWP1    = (DCM_GPR_DCMRWP1 & 0x00FFFFFF) | (0xA5000000);
                    Status_Data.status = RAM_STATUS_START_MU_INSTALL;
                }
                FunctionalReset();
            }
        }
        Status_Data.status = RAM_STATUS_FW_INIT_OK;
    }
    /* no break */
    case RAM_STATUS_FW_INIT_OK: {
        hseAttrFwVersion_t gHseFwVersion = {0U};
        hseAttrFwVersion_t CurrVersion   = HSE_FW_VERSION;
        bool               isLowAddress  = false;

        if (HSE_SRV_RSP_OK != HSE_GetVersion(&gHseFwVersion)) {
            FunctionalReset();
        }

        if (DCMDone()) {
            isLowAddress = DCMLowAddress();
        }

        if ((gHseFwVersion.socTypeId == CurrVersion.socTypeId) &&
            ((gHseFwVersion.majorVersion != CurrVersion.majorVersion) ||
             (gHseFwVersion.minorVersion != CurrVersion.minorVersion) ||
             (gHseFwVersion.patchVersion != CurrVersion.patchVersion))) {
            if (HSE_SRV_RSP_OK != TrigUpdateHSEFW()) {
                // Update failed force reboot
                FunctionalReset();
            }
        }

        switch (gHseFwVersion.reserved) {
        case 1: // AB_SWAP
            if (Status_Data.firstBlock) {
                // Updated in current block, switch to another block
                Status_Data.firstBlock = false;
                Status_Data.status     = RAM_STATUS_UTEST_OK;
                HSE_SwitchBlock();
                FunctionalReset();
            } else if (isLowAddress) {
                Status_Data.status = RAM_STATUS_UPDATE_FINISHED;
            } else {
                Status_Data.status = RAM_STATUS_UTEST_OK;
                HSE_SwitchBlock();
                FunctionalReset();
            }
            break;
        case 0: // Full Mem
            // Full Mem, Check and Update SBAF
            if (CheckSBAF(gHseFwVersion.socTypeId)) {
                TrigUpdateSBAF();
            }
            Status_Data.status = RAM_STATUS_UPDATE_FINISHED;
            break;
        default:
            for (;;)
                ;
            break;
        }
    }
    /* no break */
    case RAM_STATUS_UPDATE_FINISHED:
        if (!MU_IsFormated()) {
#if defined(FORMAT_AFTER_FINISH)
            if (HSE_SRV_RSP_OK == HSE_Format()) {
#if defined(IMPORT_KEY_AFTER_FORMAT)
                HSE_Import();
#endif
            }
#endif
        }
        for (;;)
            ;
        break;
    case RAM_STATUS_START_MU_INSTALL:
        if (HSE_GPR_3 & HSE_GPR_3_MU_READY) {
            bool firstTime = true;
            for (;;) {
                hseSrvResponse_t cmd = HSE_Read();
                switch (cmd) {
                case 0xAA55A55A: // Valid HSE Firmware in Passive Block
                    if (firstTime) {
                        firstTime = false;
                        HSE_Write(0xF0F00F0F); // Install Firmware in Active Block
                    } else {
                        HSE_Write(0x5A5AA5A5); // switch to passive block
                    }
                    break;
                case 0xFF00F00F:           // No Valid HSE FW in Passive Block
                    HSE_Write(0xF0F00F0F); // Install Firmware in Active Block
                    break;
                case 0xDABABADA: // Block switching success
                    Status_Data.firstBlock = false;
                case 0xDACACADA: // Full Mem HSE FW install success
                    while (HSE_GPR_3 & HSE_GPR_3_MU_READY)
                        ;
                    Status_Data.status = RAM_STATUS_UTEST_OK;
                    FunctionalReset();
                    break;
                case 0xDADABABA: // Get HSE FW base address
                    HSE_Write((uint32_t)&__HSE_BIN_START);
                    break;
                }
            }
        } else {
            Status_Data.status     = RAM_STATUS_UNKNWON;
            Status_Data.firstBlock = true;
            FunctionalReset();
        }
        break;
    default:
        Status_Data.status     = RAM_STATUS_UNKNWON;
        Status_Data.firstBlock = true;
        FunctionalReset();
        break;
    }

    return 0;
}
