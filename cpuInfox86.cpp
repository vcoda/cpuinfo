#include <intrin.h>
#include <algorithm>
#include <unordered_map>
#include "cpuInfox86.h"

enum
{
    Eax = 0, Ebx, Ecx, Edx
};

struct CpuId
{
    int reg[4];
};

x86ProcessorInfo getProcessorInfo()
{
    const std::unordered_map<const char *, x86VendorId> vendorIds = {
        {"GenuineIntel", x86VendorId::Intel},
        {"AuthenticAMD", x86VendorId::AMD},
        {"VIA VIA VIA ", x86VendorId::VIA},
        {"HygonGenuine", x86VendorId::Hygon},
        {"  Shanghai  ", x86VendorId::Zhaoxin}
    };
    x86ProcessorInfo cpuInfo = {};
    CpuId cpuId;
    __cpuid(cpuId.reg, 0);
    int vendor[3];
    // A twelve-character ASCII string stored in ebx, edx, ecx
    vendor[0] = cpuId.reg[Ebx];
    vendor[1] = cpuId.reg[Edx];
    vendor[2] = cpuId.reg[Ecx];
    memcpy(cpuInfo.vendor, vendor, sizeof(vendor));
    auto it = std::find_if(vendorIds.begin(), vendorIds.end(),
        [&cpuInfo](auto& pair)
        {
            return strcmp(cpuInfo.vendor, pair.first) == 0;
        });
    if (it != vendorIds.end())
        cpuInfo.vendorId = it->second;
    const int numIds = cpuId.reg[Eax];
    std::vector<CpuId> cpuIds(numIds);
    for (int i = 0; i < numIds; ++i)
        __cpuidex(cpuIds[i].reg, i, 0);
    if (numIds >= 1)
    {   // Signature of a CPU
        cpuInfo.signature.eax = cpuIds[1].reg[Eax];
        // Additional info
        cpuInfo.misc.ebx = cpuIds[1].reg[Ebx];
        // Processor feature flags
        cpuInfo.features.edx = cpuIds[1].reg[Edx];
        cpuInfo.features.ecx = cpuIds[1].reg[Ecx];
    }
    if (numIds >= 4)
    {
        // TODO: L1 cache info for Intel CPU
        // https://stackoverflow.com/questions/14283171/how-to-receive-l1-l2-l3-cache-size-using-cpuid-instruction-in-x86
    }
    if (numIds >= 6)
    {   // Thermal power management feature flags
        cpuInfo.tpmFeatures.eax = cpuIds[6].reg[Eax];
        cpuInfo.tpmFeatures.ebx = cpuIds[6].reg[Ebx];
        cpuInfo.tpmFeatures.ecx = cpuIds[6].reg[Ecx];
    }
    if (numIds >= 7)
    {   // Extended feature flags
        cpuInfo.extendedFeatures.ebx = cpuIds[7].reg[Ebx];
        cpuInfo.extendedFeatures.ecx = cpuIds[7].reg[Ecx];
        cpuInfo.extendedFeatures.edx = cpuIds[7].reg[Edx];
    }
     __cpuid(cpuId.reg, 0x80000000); // Get highest valid extended ID
    const int numIdsEx = cpuId.reg[Eax];
    std::vector<CpuId> cpuIdsEx;
    for (int i = 0x80000000; i <= numIdsEx; ++i)
    {
        __cpuidex(cpuId.reg, i, 0);
        cpuIdsEx.push_back(cpuId);
    }
    const bool isAMD = (x86VendorId::AMD == cpuInfo.vendorId);
    if ((numIdsEx >= 0x80000001) && isAMD)
    {   // AMD processor extended feature flags
        cpuInfo.featuresAMD.edx = cpuIdsEx[1].reg[Edx];
        cpuInfo.featuresAMD.ecx = cpuIdsEx[1].reg[Ecx];
    }
    if (numIdsEx >= 0x80000004)
    {   // Interpret processor brand string if supported
        memcpy(cpuInfo.brand, cpuIdsEx[2].reg, sizeof(CpuId) * 3);
    }
    if ((numIdsEx >= 0x80000005) && isAMD)
    {   // L1 Cache and TLB Identifiers
        cpuInfo.l1CacheAMD.eax = cpuIdsEx[5].reg[Eax];
        cpuInfo.l1CacheAMD.ebx = cpuIdsEx[5].reg[Ebx];
        cpuInfo.l1CacheAMD.ecx = cpuIdsEx[5].reg[Ecx];
        cpuInfo.l1CacheAMD.edx = cpuIdsEx[5].reg[Edx];
    }
    if (numIdsEx >= 0x80000006)
    {   // Extended L2 Cache Features
        cpuInfo.l2Cache.ecx = cpuIdsEx[6].reg[Ecx];
    }
    return cpuInfo;
}

static_assert(sizeof(x86ProcessorFeatures) == sizeof(uint32_t) * 2,
    "x86ProcessorFeatures structure size mismatch");
static_assert(sizeof(x86ProcessorFeaturesAMD) == sizeof(uint32_t) * 2,
    "x86ProcessorFeaturesAMD structure size mismatch");
static_assert(sizeof(x86ProcessorFeaturesEx) == sizeof(uint32_t) * 3,
    "x86ProcessorFeaturesEx structure size mismatch");
