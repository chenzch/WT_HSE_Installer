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
#include "mu.h"

extern uint32_t __HSE_BIN_START;
extern uint32_t __SBAF_BIN_START;

bool MU_GetHseStatus(void) {
	return MU_0__MUB.FSR.B.F24;
}

static hseSrvResponse_t GetAttr(hseAttrId_t attrId, uint32_t attrLen, void *pAttr);
static hseSrvResponse_t HSE_Send(hseSrvDescriptor_t* pHseSrvDesc);

hseSrvResponse_t TrigUpdateHSEFW(void) {

    hseSrvDescriptor_t hseSrvDesc = { HSE_SRV_ID_FIRMWARE_UPDATE };
    hseSrvDesc.hseSrv.firmwareUpdateReq.accessMode = HSE_ACCESS_MODE_ONE_PASS;
    hseSrvDesc.hseSrv.firmwareUpdateReq.pInFwFile  = (uint32_t)&__HSE_BIN_START;

    return HSE_Send(&hseSrvDesc);
}

hseSrvResponse_t TrigUpdateSBAF(void) {

    hseSrvDescriptor_t hseSrvDesc = { HSE_SRV_ID_SBAF_UPDATE };
    hseSrvDesc.hseSrv.firmwareUpdateReq.accessMode = HSE_ACCESS_MODE_ONE_PASS;
    hseSrvDesc.hseSrv.firmwareUpdateReq.pInFwFile  = (uint32_t)&__SBAF_BIN_START;

    return HSE_Send(&hseSrvDesc);
}

hseSrvResponse_t HSE_GetVersion(hseAttrFwVersion_t *pHseFwVersion) {
    return GetAttr(HSE_FW_VERSION_ATTR_ID, sizeof(hseAttrFwVersion_t), pHseFwVersion);
}

bool HSE_Write(uint32_t Data) {
    uint32_t u32TimeOutCount;

    MU_0__MUB.TR[0].B.TR_DATA = Data;

    u32TimeOutCount = -1UL;

    /* Wait until HSE process the request and send the response */
    while((0UL < u32TimeOutCount--) && (0 == MU_0__MUB.RSR.B.RF0));

    /* Response received if TIMEOUT did not occur */
    if(u32TimeOutCount > 0UL) {
        return true;
    } else {
        return false;
    }
}

hseSrvResponse_t HSE_Read(void) {
    /* Get HSE response */
    hseSrvResponse_t u32HseMuResponse = MU_0__MUB.RR[0].B.RR_DATA;
    while (MU_0__MUB.FSR.B.F0);
    return u32HseMuResponse;
}

hseSrvResponse_t HSE_Send(hseSrvDescriptor_t* pHseSrvDesc) {
    /* Response received if TIMEOUT did not occur */
    if(HSE_Write((uint32_t)pHseSrvDesc)) {
        return HSE_Read();
    }
    else {
        return HSE_SRV_RSP_GENERAL_ERROR;
    }
}

hseSrvResponse_t GetAttr(hseAttrId_t attrId, uint32_t attrLen, void *pAttr) {
    hseSrvDescriptor_t hseSrvDesc = { HSE_SRV_ID_GET_ATTR };
    hseSrvDesc.hseSrv.getAttrReq.attrId   = attrId;
    hseSrvDesc.hseSrv.getAttrReq.attrLen  = attrLen;
    hseSrvDesc.hseSrv.getAttrReq.pAttr    = (HOST_ADDR)pAttr;

    return HSE_Send(&hseSrvDesc);
}

hseSrvResponse_t HSE_SwitchBlock(void) {
    hseSrvDescriptor_t hseSrvDesc = { HSE_SRV_ID_ACTIVATE_PASSIVE_BLOCK };
    return HSE_Send(&hseSrvDesc);
}
