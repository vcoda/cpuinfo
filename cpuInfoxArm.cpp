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
