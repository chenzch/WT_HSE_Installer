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

#include <hse_interface.h>

// clang-format off

/* Start Copy from generate/src/Crypto_43_HSE_Cfg.c */

/* Table containing NVM key catalog entries */
const hseKeyGroupCfgEntry_t aHseNvmKeyCatalog[] = {
    /* NvmKeyGroup_0 */
    {HSE_MU0_MASK, HSE_KEY_OWNER_ANY , HSE_KEY_TYPE_SHE,        12U, HSE_KEY128_BITS , {0U, 0U}}, /* MASTER_ECU_KEY, BOOT_MAC_KEY, KEY_1 to KEY_10 */
    {HSE_MU0_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES,         4U, HSE_KEY128_BITS , {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES,         7U, HSE_KEY256_BITS , {0U, 0U}}, /* HMAC key */
    {HSE_MU0_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_HMAC,        2U, HSE_KEY512_BITS , {0U, 0U}}, /* ECC keys */
    {HSE_MU0_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_ECC_PAIR,    3U, HSE_KEY521_BITS , {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_ECC_PUB,     1U, HSE_KEY521_BITS , {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_ECC_PUB_EXT, 1U, HSE_KEY521_BITS , {0U, 0U}}, /* RSA keys */
    {HSE_MU0_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PAIR,    2U, HSE_KEY4096_BITS, {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PUB,     1U, HSE_KEY4096_BITS, {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PUB_EXT, 1U, HSE_KEY4096_BITS, {0U, 0U}}, /* OEM keys */
    {HSE_MU0_MASK, HSE_KEY_OWNER_OEM , HSE_KEY_TYPE_AES,         3U, HSE_KEY128_BITS , {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_OEM , HSE_KEY_TYPE_AES,         3U, HSE_KEY256_BITS , {0U, 0U}}, /* HMAC key */
    {HSE_MU0_MASK, HSE_KEY_OWNER_OEM , HSE_KEY_TYPE_HMAC,        1U, HSE_KEY1024_BITS, {0U, 0U}}, /* ECC keys */
    {HSE_MU0_MASK, HSE_KEY_OWNER_OEM , HSE_KEY_TYPE_ECC_PAIR,    1U, HSE_KEY521_BITS , {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_OEM , HSE_KEY_TYPE_ECC_PUB,     1U, HSE_KEY521_BITS , {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_OEM , HSE_KEY_TYPE_ECC_PUB_EXT, 1U, HSE_KEY521_BITS , {0U, 0U}}, /* RSA keys */
    {HSE_MU0_MASK, HSE_KEY_OWNER_OEM , HSE_KEY_TYPE_RSA_PAIR,    1U, HSE_KEY4096_BITS, {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_OEM , HSE_KEY_TYPE_RSA_PUB,     1U, HSE_KEY4096_BITS, {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_OEM , HSE_KEY_TYPE_RSA_PUB_EXT, 1U, HSE_KEY4096_BITS, {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_OEM , HSE_KEY_TYPE_ECC_PUB,     1U, HSE_KEY521_BITS , {0U, 0U}},
    /* Marker to end the key catalog */
    {0U, 0U, 0U, 0U, 0U, {0U, 0U}}
};

/* Table containing RAM key catalog entries */
const hseKeyGroupCfgEntry_t aHseRamKeyCatalog[] = {
    /* RamKeyGroup_0 */
    {HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHE,           1U, HSE_KEY128_BITS , {0U, 0U}}, /* KEY_RAM */
    {HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES,          10U, HSE_KEY128_BITS , {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES,          10U, HSE_KEY256_BITS , {0U, 0U}}, /* HMAC key */
    {HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_HMAC,          6U, HSE_KEY1024_BITS, {0U, 0U}}, /* RSA key */
    {HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_RSA_PUB,       2U, HSE_KEY2048_BITS, {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_RSA_PUB_EXT,   1U, HSE_KEY1024_BITS, {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_ECC_PAIR,      2U, HSE_KEY521_BITS , {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_ECC_PUB,       5U, HSE_KEY521_BITS , {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHARED_SECRET, 2U, HSE_KEY638_BITS , {0U, 0U}},
    {HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHARED_SECRET, 1U, HSE_KEY2048_BITS, {0U, 0U}},
    /* Marker to end the key catalog */
    {0U, 0U, 0U, 0U, 0U, {0U, 0U}}
};

/* End Copy from generate/src/Crypto_43_HSE_Cfg.c */

// clang-format on
