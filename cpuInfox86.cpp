#ifdef _WIN32
#include <windows.h>
#pragma comment(lib, "advapi32.lib")
#endif
#include "cpuInfox86.h"
#include "cpuid.h"

struct CpuVendor
{
    const char *name;
    x86VendorId vendorId;
};

static const CpuVendor vendorIds[] = {
    {CPUID_VENDOR_INTEL, x86VendorId::Intel},
    {CPUID_VENDOR_AMD, x86VendorId::AMD},
    {CPUID_VENDOR_VIA, x86VendorId::VIA},
    {CPUID_VENDOR_HYGON, x86VendorId::Hygon},
    {CPUID_VENDOR_ZHAOXIN, x86VendorId::Zhaoxin},
    {CPUID_VENDOR_UNKNOWN, x86VendorId::Unknown}
};

x86ProcessorInfo getProcessorInfo()
{
    x86ProcessorInfo cpuInfo = {};
    CpuId cpuId;
    __cpuid(&cpuId.eax, 0);
    // A twelve-character ASCII string stored in ebx, edx, ecx
    const int vendor[3] = {cpuId.ebx, cpuId.edx, cpuId.ecx};
    memcpy(cpuInfo.vendor, vendor, sizeof(vendor));
    for (const auto& it: vendorIds)
    {
        if (cpuidIsVendor(it.name, cpuId))
        {
            cpuInfo.vendorId = it.vendorId;
            break;
        }
    }
    const bool isIntel = (x86VendorId::Intel == cpuInfo.vendorId);
    const bool isAMD = (x86VendorId::AMD == cpuInfo.vendorId);
    const int numIds = cpuId.eax;
    std::vector<CpuId> cpuIds(numIds + 1);
    for (int i = 0; i <= numIds; ++i)
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
    if (numIds >= 0x4 && isIntel)
    {   // Intel deterministic cache parameters
        int ecx = 0;
        while (true)
        {
            x86DeterministicCacheInfo cacheInfo;
            __cpuidex(cacheInfo.reg, 0x4, ecx++);
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
    if (numIds >= 0x6)
    {   // Thermal power management feature flags
        cpuInfo.tpmFeatures.eax = cpuIds[0x6].eax;
        cpuInfo.tpmFeatures.ebx = cpuIds[0x6].ebx;
        cpuInfo.tpmFeatures.ecx = cpuIds[0x6].ecx;
    }
    if (numIds >= 0x7)
    {   // Extended feature flags
        cpuInfo.extendedFeatures.ebx = cpuIds[0x7].ebx;
        cpuInfo.extendedFeatures.ecx = cpuIds[0x7].ecx;
        cpuInfo.extendedFeatures.edx = cpuIds[0x7].edx;
    }
    if (numIds >= 0x16 && isIntel)
    {   // Processor frequency information
        cpuInfo.frequency.eax = cpuIds[0x16].eax;
        cpuInfo.frequency.ebx = cpuIds[0x16].ebx;
        cpuInfo.frequency.ecx = cpuIds[0x16].ecx;
    } else
    {   // Use fallback for frequency information
    #ifdef _WIN32
        HKEY key = NULL;
        if (ERROR_SUCCESS == RegOpenKeyExA(HKEY_LOCAL_MACHINE,
            "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
            0, KEY_READ, &key))
        {   // Read processor base frequency from registry
            DWORD bufferSize = sizeof(DWORD);
            RegQueryValueExA(key, "~MHz", nullptr, nullptr,
                (LPBYTE)&cpuInfo.frequency.eax,
                &bufferSize);
        }
    #else
    #endif // _WIN32
    }
    __cpuid(&cpuId.eax, CPUID_EXTENDED_ID); // Get highest valid extended ID
    const int numIdsEx = cpuId.eax;
    std::vector<CpuId> cpuIdsEx;
    for (int id = CPUID_EXTENDED_ID; id <= numIdsEx; ++id)
    {
        __cpuid(&cpuId.eax, id);
        cpuIdsEx.push_back(cpuId);
    }
    if ((numIdsEx >= CPUID_EXTENDED_ID + 0x1) && isAMD)
    {   // AMD processor extended feature flags
        cpuInfo.featuresAMD.edx = cpuIdsEx[0x1].edx;
        cpuInfo.featuresAMD.ecx = cpuIdsEx[0x1].ecx;
    }
    if (numIdsEx >= CPUID_EXTENDED_ID + 0x4)
    {   // Interpret processor brand string if supported
        memcpy(cpuInfo.brand, &cpuIdsEx[0x2], sizeof(CpuId) * 3); // 0x2, 0x3, 0x4
    }
    if ((numIdsEx >= CPUID_EXTENDED_ID + 0x5) && isAMD)
    {   // L1 Cache and TLB Identifiers
        cpuInfo.l1CacheAMD.eax = cpuIdsEx[0x5].eax;
        cpuInfo.l1CacheAMD.ebx = cpuIdsEx[0x5].ebx;
        cpuInfo.l1CacheAMD.ecx = cpuIdsEx[0x5].ecx;
        cpuInfo.l1CacheAMD.edx = cpuIdsEx[0x5].edx;
    }
    if (numIdsEx >= CPUID_EXTENDED_ID + 0x6)
    {   // Extended L2 Cache Features
        cpuInfo.l2Cache.ecx = cpuIdsEx[0x6].ecx;
    }
    if (numIdsEx >= CPUID_EXTENDED_ID + 0x7)
    {   // Advanced power management feature flags
        cpuInfo.apmFeatures.edx = cpuIdsEx[0x7].edx;
    }
    return cpuInfo;
}

enum TopologyLevelType : uint8_t
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

#define CMP_LEGACY_BIT      (1 << 1)
#define HTT_BIT             (1 << 28)
#define TSC_BIT             (1 << 4)
#define INVARIANT_TSC_BIT   (1 << 8)

uint32_t getProcessorPhysicalThreadCount() noexcept
{
    uint32_t physicalThreadCount = 1;
    CpuId cpuId;
    __cpuid(&cpuId.eax, 0);
    if (cpuidIsVendor(CPUID_VENDOR_INTEL, cpuId))
    {   // Get highest topology leaf
        const int numIds = cpuId.eax;
        const int id = numIds >= 0x1F ? 0x1F : (numIds > 0xB ? 0xB : 0);
        if (id > 0)
        {   // Enumerate topology levels
            CpuExtTopology topology = {};
            int level = 0;
            while (topology.levelType != TopologyLevelType::Core)
            {   // SMT related to physical cores, Core related to logical ones
                __cpuidex((int *)&topology, id, level++);
                if (!topology.numLogicalProcessors)
                    break;
            }
            if (topology.numLogicalProcessors)
                physicalThreadCount = topology.numLogicalProcessors;
        }
    } else if (cpuidIsVendor(CPUID_VENDOR_AMD, cpuId))
    {   // Get highest valid extended ID
        __cpuid(&cpuId.eax, CPUID_EXTENDED_ID);
        const int numIdsEx = cpuId.eax;
        if (numIdsEx >= CPUID_EXTENDED_ID + 0x8)
        {   // Use extended size identifiers
            __cpuid(&cpuId.eax, CPUID_EXTENDED_ID + 0x8);
            physicalThreadCount = (cpuId.ecx & 0x000000FF) + 1;
        } else if (numIdsEx >= CPUID_EXTENDED_ID + 0x1)
        {   // Check that legacy method is supported
            __cpuid(&cpuId.eax, CPUID_EXTENDED_ID + 0x1);
            const bool coreMultiProcessingLegacyMode = cpuId.ecx & CMP_LEGACY_BIT;
            if (coreMultiProcessingLegacyMode)
            {   // When HTT = 1 and CmpLegacy = 1, LogicalProcessorCount represents
                // the number of logical processors per package
                __cpuid(&cpuId.eax, 0x1);
                const bool hyperThreading = cpuId.edx & HTT_BIT;
                if (hyperThreading)
                    physicalThreadCount = (cpuId.ebx & 0x00FF0000) >> 16; // bits 23:16
            }
        }
    }
    return physicalThreadCount;
}

uint64_t waitNanoseconds(uint64_t ns) noexcept;

uint64_t getProcessorFrequency(uint64_t period /* 1000000000 */) noexcept
{
    CpuId cpuId[2] = {};
    __cpuid(&cpuId[0].eax, 0);
    if (cpuId[0].eax >= 0x1)
        __cpuid(&cpuId[0].eax, 0x1); // Processor feature flags
    __cpuid(&cpuId[1].eax, CPUID_EXTENDED_ID); // Get highest valid extended ID
    if (cpuId[1].eax >= CPUID_EXTENDED_ID + 0x7)
        __cpuid(&cpuId[1].eax, CPUID_EXTENDED_ID + 0x7); // Advanced power management feature flags
    if ((cpuId[0].edx & TSC_BIT) &&
        (cpuId[1].edx & INVARIANT_TSC_BIT))
    {
        uint64_t begin = __rdtsc();
        {   // Wait for specified period and store the actual wait period
            period = waitNanoseconds(period);
            __cpuid(&cpuId[0].eax, 0); // Insert barrier
        }
        uint64_t end = __rdtsc();
        // Adjust multiplier according to returned wait period
        double multiplier = 1e+9/period;
        uint64_t frequency = (uint64_t)((end - begin) * multiplier);
        return frequency;
    }
    return 0ull;
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
