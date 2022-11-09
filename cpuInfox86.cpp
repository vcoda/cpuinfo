#include <intrin.h>
#include <string.h>
#include "cpuInfox86.h"

struct CpuId
{
    int eax, ebx, ecx, edx;
};

struct CpuVendor
{
    const char *name;
    x86VendorId vendorId;
};

x86ProcessorInfo getProcessorInfo()
{
    const CpuVendor vendorIds[] = {
        {"GenuineIntel", x86VendorId::Intel},
        {"AuthenticAMD", x86VendorId::AMD},
        {"VIA VIA VIA ", x86VendorId::VIA},
        {"HygonGenuine", x86VendorId::Hygon},
        {"  Shanghai  ", x86VendorId::Zhaoxin},
        {nullptr, x86VendorId::Unknown}
    };
    x86ProcessorInfo cpuInfo = {};
    CpuId cpuId;
    __cpuid(&cpuId.eax, 0);
    // A twelve-character ASCII string stored in ebx, edx, ecx
    const int vendor[3] = {cpuId.ebx, cpuId.edx, cpuId.ecx};
    memcpy(cpuInfo.vendor, vendor, sizeof(vendor));
    for (auto it = vendorIds; it->vendorId != x86VendorId::Unknown; ++it)
    {
        if (0 == strcmp(cpuInfo.vendor, it->name))
        {
            cpuInfo.vendorId = it->vendorId;
            break;
        }
    }
    const bool isAMD = (x86VendorId::AMD == cpuInfo.vendorId);
    const int numIds = cpuId.eax;
    std::vector<CpuId> cpuIds(numIds);
    for (int i = 0; i < numIds; ++i)
        __cpuidex(&cpuIds[i].eax, i, 0);
    if (numIds >= 1)
    {   // Signature of a CPU
        cpuInfo.signature.eax = cpuIds[1].eax;
        // Additional info
        cpuInfo.misc.ebx = cpuIds[1].ebx;
        // Processor feature flags
        cpuInfo.features.edx = cpuIds[1].edx;
        cpuInfo.features.ecx = cpuIds[1].ecx;
    }
    if (numIds >= 4 && !isAMD)
    {   // Intel deterministic cache parameters
        int ecx = 0;
        while (true)
        {
            x86DeterministicCacheInfo cacheInfo;
            __cpuidex(cacheInfo.reg, 4, ecx++);
            if (!cacheInfo.cacheType)
               break;
            cacheInfo.maxAddressableIdsForLogicalProcessors += 1;
            cacheInfo.maxAddressableIdsForProcessorCores += 1;
            cacheInfo.systemCoherencyLineSize += 1;
            cacheInfo.physicalLinePartitions += 1;
            cacheInfo.associativity += 1;
            cacheInfo.numSets += 1;
            cpuInfo.cacheInfos.push_back(cacheInfo);
        }
    }
    if (numIds >= 6)
    {   // Thermal power management feature flags
        cpuInfo.tpmFeatures.eax = cpuIds[6].eax;
        cpuInfo.tpmFeatures.ebx = cpuIds[6].ebx;
        cpuInfo.tpmFeatures.ecx = cpuIds[6].ecx;
    }
    if (numIds >= 7)
    {   // Extended feature flags
        cpuInfo.extendedFeatures.ebx = cpuIds[7].ebx;
        cpuInfo.extendedFeatures.ecx = cpuIds[7].ecx;
        cpuInfo.extendedFeatures.edx = cpuIds[7].edx;
    }
    __cpuid(&cpuId.eax, 0x80000000); // Get highest valid extended ID
    const int numIdsEx = cpuId.eax;
    std::vector<CpuId> cpuIdsEx;
    for (int i = 0x80000000; i <= numIdsEx; ++i)
    {
        __cpuidex(&cpuId.eax, i, 0);
        cpuIdsEx.push_back(cpuId);
    }
    if ((numIdsEx >= 0x80000001) && isAMD)
    {   // AMD processor extended feature flags
        cpuInfo.featuresAMD.edx = cpuIdsEx[1].edx;
        cpuInfo.featuresAMD.ecx = cpuIdsEx[1].ecx;
    }
    if (numIdsEx >= 0x80000004)
    {   // Interpret processor brand string if supported
        memcpy(cpuInfo.brand, &cpuIdsEx[2], sizeof(CpuId) * 3);
    }
    if ((numIdsEx >= 0x80000005) && isAMD)
    {   // L1 Cache and TLB Identifiers
        cpuInfo.l1CacheAMD.eax = cpuIdsEx[5].eax;
        cpuInfo.l1CacheAMD.ebx = cpuIdsEx[5].ebx;
        cpuInfo.l1CacheAMD.ecx = cpuIdsEx[5].ecx;
        cpuInfo.l1CacheAMD.edx = cpuIdsEx[5].edx;
    }
    if (numIdsEx >= 0x80000006)
    {   // Extended L2 Cache Features
        cpuInfo.l2Cache.ecx = cpuIdsEx[6].ecx;
    }
    if (numIdsEx >= 0x80000007)
    {   // Advanced power management feature flags
        cpuInfo.apmFeatures.edx = cpuIdsEx[7].edx;
    }
    return cpuInfo;
}

enum LevelType : uint8_t
{
    Invalid, SMT, Core, Module, Tile, Die
};

struct CpuExtTopology
{
    uint32_t bitsToShiftRightX2ApicId: 5;
    uint32_t reserved: 27;
    uint32_t numLogicalProcessors: 16;
    uint32_t reserved2: 16;
    uint32_t levelNumber: 8;
    uint32_t levelType: 8;
    uint32_t reserved3: 16;
    uint32_t x2ApicId: 32;
};

uint32_t getProcessorPhysicalThreadCount() noexcept
{
    uint32_t physicalThreadCount = 1;
    CpuId cpuId;
    __cpuid(&cpuId.eax, 0);
    // A twelve-character ASCII string stored in ebx, edx, ecx
    const int ascii[3] = {cpuId.ebx, cpuId.edx, cpuId.ecx};
    const char *vendor = (const char *)ascii;
    if (0 == strncmp("AuthenticAMD", vendor, sizeof(ascii)))
    {   // Get highest valid extended ID
        __cpuid(&cpuId.eax, 0x80000000);
        const int numIdsEx = cpuId.eax;
        if (numIdsEx >= 0x80000008)
        {   // Use extended size identifiers
            __cpuidex(&cpuId.eax, 0x80000008, 0);
            physicalThreadCount = (cpuId.ecx & 0x000000FF) + 1;
        } else
        {   // Use legacy method
            __cpuidex(&cpuId.eax, 0x1, 0);
            physicalThreadCount = (cpuId.ebx & 0x00FF0000) >> 16; // bits 23:16
        }
    } else if (0 == strncmp("GenuineIntel", vendor, sizeof(ascii)))
    {   // Get highest topology leaf
        const int numIds = cpuId.eax;
        const int eax = numIds >= 0x1F ? 0x1F : (numIds > 0xB ? 0xB : 0);
        if (eax > 0)
        {   // Enumerate topology levels
            CpuExtTopology topology = {0};
            int level = 0;
            while (topology.levelType != LevelType::Core)
            {   // SMT related to physical cores, Core related to logical ones
                __cpuidex((int *)&topology, eax, level++);
                if (!topology.numLogicalProcessors)
                    break;
            }
            if (topology.numLogicalProcessors)
                physicalThreadCount = topology.numLogicalProcessors;
        }
    }
    return physicalThreadCount;
}

static_assert(sizeof(x86ProcessorFeatures) == sizeof(uint32_t) * 2,
    "x86ProcessorFeatures structure size mismatch");
static_assert(sizeof(x86ProcessorFeaturesAMD) == sizeof(uint32_t) * 2,
    "x86ProcessorFeaturesAMD structure size mismatch");
static_assert(sizeof(x86ProcessorFeaturesEx) == sizeof(uint32_t) * 3,
    "x86ProcessorFeaturesEx structure size mismatch");
static_assert(sizeof(x86DeterministicCacheInfo) == sizeof(uint32_t) * 4,
    "x86DeterministicCacheInfo structure size mismatch");
static_assert(sizeof(x86L1CacheAndTlbFeaturesAMD) == sizeof(uint32_t) * 4,
    "x86L1CacheAndTlbFeaturesAMD structure size mismatch");
static_assert(sizeof(x86ThermalPowerManagementFeatures) == sizeof(uint32_t) * 3,
    "x86ThermalPowerManagementFeatures structure size mismatch");
static_assert(sizeof(x86AdvancedPowerManagementFeatures) == sizeof(uint32_t),
    "x86AdvancedPowerManagementFeatures structure size mismatch");
static_assert(sizeof(CpuExtTopology) == sizeof(CpuId),
    "Topology structure size mismatch");
