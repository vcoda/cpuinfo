#pragma once
#include <cstdint>

enum class ArmVendorId : uint8_t
{
    Unknown, Apple, Amazon, Samsung, Qualcomm, Broadcom, LG,
    NVidia, AMD, Marvell, MediaTek, TexasInstruments, Microchip,
    NXP, STMicroelectronics, Huawei, HiSilicon
};

/* ARM CPU description. */

struct ArmProcessorInfo
{
    char vendor[];
    char brand[];
    ArmVendorId vendorId;
};

/* */

ArmProcessorInfo getProcessorInfo();
uint32_t getProcessorPhysicalThreadCount() noexcept;
