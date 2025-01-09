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
#if !defined(MU_H)
#define MU_H (1)

#if defined(__cplusplus)
extern "C" {
#endif

bool MU_GetHseStatus(void);

hseSrvResponse_t TrigUpdateHSEFW(void);
hseSrvResponse_t TrigUpdateSBAF(void);

hseSrvResponse_t HSE_GetVersion(hseAttrFwVersion_t *pHseFwVersion);

hseSrvResponse_t HSE_SwitchBlock(void);

bool HSE_Write(uint32_t Data);

hseSrvResponse_t HSE_Read(void);

bool MU_IsFormated(void);

hseSrvResponse_t HSE_Format(void);

hseSrvResponse_t HSE_Import(void);

#if defined(__cplusplus)
}
#endif

#endif // MU_H
