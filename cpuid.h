#pragma once
#include <intrin.h>
#include <cstring>

#define CPUID_VENDOR_INTEL      "GenuineIntel"
#define CPUID_VENDOR_AMD        "AuthenticAMD"
#define CPUID_VENDOR_VIA        "VIA VIA VIA "
#define CPUID_VENDOR_HYGON      "HygonGenuine"
#define CPUID_VENDOR_ZHAOXIN    "  Shanghai  "
#define CPUID_VENDOR_UNKNOWN    nullptr

#define CPUID_EXTENDED_ID       0x80000000

struct CpuId
{
    int eax, ebx, ecx, edx;
};

inline bool cpuidIsVendor(const char *vendor,
    const CpuId& cpuId) noexcept
{   
    if (!vendor || strlen(vendor) < 12)
        return false;
    // A twelve-character ASCII string stored in ebx, edx, ecx
    const int ascii[3] = {cpuId.ebx, cpuId.edx, cpuId.ecx};
    return 0 == strncmp((const char *)ascii, vendor, sizeof(ascii));
}
