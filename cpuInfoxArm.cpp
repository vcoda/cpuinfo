#include "cpuInfoArm.h"

struct CpuVendor
{
    const char *name;
    ArmVendorId vendorId;
};

ArmProcessorInfo getProcessorInfo()
{
    ArmProcessorInfo cpuInfo = {};
    return cpuInfo;
}

uint32_t getProcessorPhysicalThreadCount() noexcept
{
    uint32_t physicalThreadCount = 1;
    return physicalThreadCount;
}
