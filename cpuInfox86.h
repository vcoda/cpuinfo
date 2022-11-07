#pragma once
#include <cstdint>
#include <vector>

/* References:
    1. Intel 64 and IA-32 Architectures Software Developer's Manual
       Volume 2A: Instruction Set Reference
    2. Software Optimization Guide for AMD Family 17h Processors
    3. AMD CPUID Specification (September 2010)
    4. https://en.wikipedia.org/wiki/CPUID */

enum class x86VendorId : uint8_t
{
    Unknown, Intel, AMD, VIA, Hygon, Zhaoxin
};

/* */

union x86ProcessorSignature
{
    struct
    {
        uint32_t steppingId: 4;             // bits 3:0
        uint32_t model: 4;                  // bits 7:4
        uint32_t familyId: 4;               // bits 11:8
        uint32_t processorType: 2;          // bits 13:12
        uint32_t reserved1: 2;              // bits 15:14
        uint32_t extendedModelId: 4;        // bits 19:16
        uint32_t extendedFamilyId: 8;       // bits 27:20
        uint32_t reserved2: 4;              // bits 31:28
    };

    uint32_t eax;
};

/* */

union x86ProcessorMiscInfo
{
    struct
    {
        uint32_t brandIndex: 8;                                 // bits 7:0
        uint32_t cacheLineFlushSize: 8;                         // bits 15:8
        uint32_t maxAddressableIdsForLogicalProcessors: 8;      // bits 23:16   (Former use: number of logical processors per physical processor)
        uint32_t defaultApicId: 8;                              // bits 31:24
    };

    uint32_t ebx;
};

/* The processor feature flags are manufacturer specific
   but usually the Intel values are used by other manufacturers
   for the sake of compatibility. */

union x86ProcessorFeatures
{
    struct
    {
        uint64_t floatingPointUnit: 1;                          // fpu
        uint64_t virtualModeExtensions: 1;                      // vme
        uint64_t debuggingExtensions: 1;                        // de
        uint64_t pageSizeExtension: 1;                          // pse
        uint64_t timestampCounter: 1;                           // tsc
        uint64_t modelSpecificRegisters: 1;                     // msr
        uint64_t physicalAddressExtension: 1;                   // pae
        uint64_t machineCheckException: 1;                      // mce
        uint64_t compareAndExchange8: 1;                        // cx8
        uint64_t advancedProgrammableInterruptController: 1;    // apic
        uint64_t reserved: 1;
        uint64_t sysEnterSysExit: 1;                            // sep
        uint64_t memoryTypeRangeRegisters: 1;                   // mtrr
        uint64_t pageGlobalEnable: 1;                           // pge
        uint64_t machineCheckArchitecture: 1;                   // mca
        uint64_t conditionalMove: 1;                            // cmov
        uint64_t pageAttributeTable: 1;                         // pat
        uint64_t pageSizeExtension36Bit: 1;                     // pse-36
        uint64_t processorSerialNumber: 1;                      // psn
        uint64_t cacheLineFlush: 1;                             // clfsh
        uint64_t reserved2: 1;
        uint64_t debugStore: 1;                                 // ds
        uint64_t advancedConfigurationAndPowerInterface: 1;     // acpi
        uint64_t multiMediaExtension: 1;                        // mmx
        uint64_t fxSaveRestore: 1;                              // fxsr
        uint64_t streamingSimdExtensions: 1;                    // sse
        uint64_t streamingSimdExtensions2: 1;                   // ss2
        uint64_t selfSnoop: 1;                                  // ss
        uint64_t hyperThreading: 1;                             // htt
        uint64_t thermalMonitor: 1;                             // tm
        uint64_t ia64Processor: 1;                              // ia64
        uint64_t pendingBreakEnable: 1;                         // pbe
        uint64_t streamingSimdExtensions3: 1;                   // sse3
        uint64_t carryLessMultiplication: 1;                    // pclmulqdq
        uint64_t debugTraceAndEmonStore64: 1;                   // dtes64
        uint64_t monitor: 1;                                    // monitor
        uint64_t debugStoreCplQualified: 1;                     // ds-cpl
        uint64_t virtualMachineExtensions: 1;                   // vmx
        uint64_t saferModeExtensions: 1;                        // smx
        uint64_t enhancedSpeedStep: 1;                          // est
        uint64_t thermalMonitor2: 1;                            // tm2
        uint64_t supplementalStreamingSimdExtensions3: 1;       // ssse3
        uint64_t contextId: 1;                                  // cnxt-id
        uint64_t siliconDebugInterface: 1;                      // sdbg
        uint64_t fusedMultiplyAdd: 1;                           // fma
        uint64_t compareAndExchange16: 1;                       // cx16
        uint64_t taskPriorityMessages: 1;                       // xtpr
        uint64_t performanceAndDebugCapability: 1;              // pdcm
        uint64_t reserved3: 1;
        uint64_t processorContextIdentifiers: 1;                // pcid
        uint64_t directCacheAccess: 1;                          // dca
        uint64_t streamingSimdExtensions4_1: 1;                 // sse4.1
        uint64_t streamingSimdExtensions4_2: 1;                 // sse4.2
        uint64_t advancedProgrammableInterruptController2: 1;   // x2apic
        uint64_t moveBigEndian: 1;                              // movbe
        uint64_t popCount: 1;                                   // popcnt
        uint64_t timestampCounterDeadline: 1;                   // tsc-deadline
        uint64_t advancedEncryptionStandard: 1;                 // aes
        uint64_t xsaveRestore: 1;                               // xsave
        uint64_t operatingSystemXSaveRestore: 1;                // osxsave
        uint64_t advancedVectorExtensions: 1;                   // avx
        uint64_t f16C: 1;                                       // f16c
        uint64_t readRandom: 1;                                 // rdrnd
        uint64_t hypervisor: 1;                                 // hypervisor
    };

    struct
    {
        uint32_t edx, ecx;
    };
};

/* AMD specific processor features (Function 80000001h). */

union x86ProcessorFeaturesAMD
{
    struct
    {
        uint64_t floatingPointUnit: 1;                          // fpu
        uint64_t virtualModeExtensions: 1;                      // vme
        uint64_t debuggingExtensions: 1;                        // de
        uint64_t pageSizeExtension: 1;                          // pse
        uint64_t timestampCounter: 1;                           // tsc
        uint64_t modelSpecificRegisters: 1;                     // msr
        uint64_t physicalAddressExtension: 1;                   // pae
        uint64_t machineCheckException: 1;                      // mce
        uint64_t compareAndExchange8: 1;                        // cx8
        uint64_t advancedProgrammableInterruptController: 1;    // apic
        uint64_t reserved: 1;
        uint64_t sysCallSysRet: 1;                              // syscall
        uint64_t memoryTypeRangeRegisters: 1;                   // mtrr
        uint64_t pageGlobalExtension: 1;                        // pge
        uint64_t machineCheckArchitecture: 1;                   // mca
        uint64_t conditionalMove: 1;                            // cmov
        uint64_t pageAttributeTable: 1;                         // pat
        uint64_t pageSizeExtensions36Bit: 1;                    // pse-36
        uint64_t reserved2: 1;
        uint64_t multiprocessorCapable: 1;                      // mp
        uint64_t noExecutePageProtection: 1;                    // nx
        uint64_t reserved3: 1;
        uint64_t extendedMmx: 1;                                // mmxext
        uint64_t multiMediaExtension: 1;                        // mmx
        uint64_t fxSaveRestore: 1;                              // fxsr
        uint64_t fxSaveRestoreOptimization: 1;                  // fxsr_opt
        uint64_t oneGigabytePage: 1;                            // pdpe1gb
        uint64_t readTimestampCounter: 1;                       // rdtscp
        uint64_t reserved4: 1;
        uint64_t longMode: 1;                                   // lm
        uint64_t extended3DNow: 1;                              // 3dnowext
        uint64_t _3DNow: 1;                                     // 3dnow
        uint64_t loadStoreAhFlagsLegacyMode: 1;                 // lahf_lm
        uint64_t coreMultiProcessingLegacyMode: 1;              // cmp_legacy
        uint64_t secureVirtualMachine: 1;                       // svm
        uint64_t extendedApicSpace: 1;                          // extapic
        uint64_t altMovCr8: 1;                                  // cr8_legacy
        uint64_t advancedBitManipulation: 1;                    // abm
        uint64_t streamingSimdExtensions4a: 1;                  // sse4a
        uint64_t misalignedSseMode: 1;                          // misalignsse
        uint64_t prefetch3DNow: 1;                              // 3dnowprefetch
        uint64_t operatingSystemVisibleWorkaround: 1;           // osvw
        uint64_t instructionBasedSampling: 1;                   // ibs
        uint64_t extendedOperation: 1;                          // xop
        uint64_t securityKernel: 1;                             // skinit
        uint64_t watchdogTimer: 1;                              // wdt
        uint64_t reserved5: 1;
        uint64_t lightweightProfiling: 1;                       // lwp
        uint64_t fusedMultiplyAdd4: 1;                          // fma4
        uint64_t translationCacheExtension: 1;                  // tce
        uint64_t reserved6: 1;
        uint64_t nodeIdModelSpecificRegisters: 1;               // nodeid_msr
        uint64_t reserved7: 1;
        uint64_t trailingBitManipulation: 1;                    // tbm
        uint64_t topologyExtensions: 1;                         // topoext
        uint64_t corePerformanceCounter: 1;                     // perfctr_core
        uint64_t nbPerformanceCounter: 1;                       // perfctr_nb
        uint64_t reserved8: 1;
        uint64_t dataBreakpointExtensions: 1;                   // dbx
        uint64_t timestampPerformanceCounter: 1;                // perftsc
        uint64_t l2InstructionCachePerformanceCounter: 1;       // pcx_l2i
        uint64_t monitorX: 1;                                   // monitorx
        uint64_t addressMaskExtension: 1;                       // addr_mask_ext
        uint64_t reserved9: 1;
    };

    struct
    {
        uint32_t edx, ecx;
    };
};

/* Extended Feature Identifiers (Function 00000007h) */

union x86ProcessorFeaturesEx
{
    struct
    {
        uint32_t fsGsBaseAccess: 1;                             // fsgsbase
        uint32_t timestampCounterAdjust: 1;
        uint32_t softwareGuardExtensions: 1;                    // sgx
        uint32_t bitManipulationInstructionSet1: 1;             // bmi1
        uint32_t hardwareLockElision: 1;                        // hle
        uint32_t advancedVectorExtensions2: 1;                  // avx2
        uint32_t fpuDataPointerExceptionOnly: 1;
        uint32_t supervisorModeExecutionPrevention: 1;          // smep
        uint32_t bitManipulationInstructionSet2: 1;             // bmi2
        uint32_t enhancedRepMovsbStosb: 1;                      // erms
        uint32_t invalidateProcessContextIdentifier: 1;         // invpcid
        uint32_t restrictedTransactionalMemory: 1;              // rtm
        uint32_t resourceDirectorMonitoring: 1;                 // rdt-m
        uint32_t fpuCsDsDeprecated: 1;
        uint32_t memoryProtectionExtensions: 1;                 // mpx
        uint32_t resourceDirectorAllocation: 1;                 // rdt-a
        uint32_t avx512Foundation: 1;                           // avx512-f
        uint32_t avx512DoubleAndQuadWord: 1;                    // avx512-dq
        uint32_t randomSeed: 1;                                 // rdseed
        uint32_t addCarryExtensions: 1;                         // adx
        uint32_t supervisorModeAccessPrevention: 1;             // smap
        uint32_t avx512IntegerFusedMultiplyAdd: 1;              // avx512-ifma
        uint32_t persistentCommit: 1;                           // pcommit
        uint32_t cacheLineFlushOpt: 1;                          // clflushopt
        uint32_t cacheLineWriteBack: 1;                         // clwb
        uint32_t processorTrace: 1;                             // pt
        uint32_t avx512Prefetch: 1;                             // avx512-pf
        uint32_t avx512ExponentialAndReciprocal: 1;             // avx512-er
        uint32_t avx512ConflictDetection: 1;                    // avx512-cd
        uint32_t secureHashAlgorithm: 1;                        // sha
        uint32_t avx512ByteAndWord: 1;                          // avx512-bw
        uint32_t avx512VectorLength: 1;                         // avx512-vl
        uint32_t prefetchWriteT1: 1;                            // prefetchwt1
        uint32_t avx512VectorBitManipulationInstructions: 1;    // avx512-vbmi
        uint32_t userModeInstructionPrevention: 1;              // umip
        uint32_t protectionKeysForUserModePages: 1;             // pku
        uint32_t operatingSystemEnabledPku: 1;                  // ospke
        uint32_t userLevelMonitorWait: 1;                       // waitpkg
        uint32_t avx512VectorBitManipulationInstructions2: 1;   // avx512-vbmi2
        uint32_t controlFlowEnforcementShadowStack: 1;          // cet_ss
        uint32_t galoisFieldInstructions: 1;                    // gfni
        uint32_t vectorAdvancedEncryptionStandard: 1;           // vaes
        uint32_t vectorCarryLessMultiplication: 1;              // vpclmulqdq
        uint32_t avx512VectorNeuralNetworkInstructions: 1;      // avx512-vnni
        uint32_t avx512BitAlgorithms: 1;                        // avx512-bitalg
        uint32_t totalMemoryEncryption: 1;                      // tme
        uint32_t avx512VectorPopCountDoubleAndQuadWord: 1;      // avx512-vpopcntdq
        uint32_t reserved2: 1;
        uint32_t fiveLevelPaging: 1;                            // la57
        uint32_t addressWidthAdjust: 5;                         // mawau
        uint32_t readProcessorId: 1;                            // rdpid
        uint32_t keyLocker: 1;                                  // kl
        uint32_t busLockDetect: 1;                              // bus_lock_detect
        uint32_t cacheLineDemote: 1;                            // cldemote
        uint32_t reserved3: 1;
        uint32_t moveDoubleWordDirectStore: 1;                  // movdiri
        uint32_t move64BytesDirectStore: 1;                     // movdir64b
        uint32_t enqueueStores: 1;                              // enqcmd
        uint32_t softwareGuardExtensionsLaunchConfiguration: 1; // sgx-lc
        uint32_t protectionKeysForSupervisorModePages: 1;       // pks
        uint32_t avx512NeuralNetworkInstructions4Register: 1;   // avx512-4vnniw
        uint32_t avx512FusedMultiplyAdd4Register: 1;            // avx512-4fmaps
        uint32_t fastShortRepMovsb: 1;                          // fsrm
        uint32_t userInterprocessorInterrupts: 1;               // uintr
        uint32_t reserved4: 2;
        uint32_t avx512Vp2Intersect: 1;                         // avx512-vp2intersect
        uint32_t specialRegisterDataBufferSampling: 1;          // srdbs-ctrl
        uint32_t verwInstructionClearsCpuBuffers: 1;            // mc-clear
        uint32_t restrictedTransactionalMemoryAlwaysAbort: 1;   // rtm-always-abort
        uint32_t reserved5: 1;
        uint32_t tsxForceAbort: 1;
        uint32_t serialize: 1;                                  // serialize
        uint32_t hybridTopology: 1;                             // hybrid
        uint32_t tsxLoadAddressTracking: 1;                     // tsxldtrk
        uint32_t platformConfiguration: 1;                      // pconfig
        uint32_t lastBranchRecords: 1;                          // lbr
        uint32_t cetIndirectBranchTracking: 1;                  // cet-ibt
        uint32_t reserved6: 1;
        uint32_t bfloat16: 1;                                   // amx-bf16
        uint32_t avx512HalfPrecisionInstructions: 1;            // avx512-fp16
        uint32_t amxTile: 1;                                    // amx-tile
        uint32_t amxInt8: 1;                                    // amx-int8
        uint32_t speculationControl: 1;                         // spec_ctrl
        uint32_t singleThreadIndirectBranchPredictor: 1;        // stibp
        uint32_t l1DCacheFlush: 1;                              // l1d_flush
        uint32_t architetureCapabilities: 1;
        uint32_t coreCapabilities: 1;
        uint32_t speculativeStoreBypassDisable: 1;              // ssbd
    };

    struct
    {
        uint32_t ebx, ecx, edx;
    };
};

/* Cache Type */

enum class x86CacheType : uint8_t
{
    Null, Data, Instruction, Unified
};

enum class x86CacheAssociativity : uint8_t
{
    Reserved = 0x0,
    DirectMapped = 0x1,
    TwoWay = 0x2,
    FourWay = 0x4,
    SixWay = 0x5,
    EightWay = 0x6,
    TwelveWay = 0x7,
    SixteenWay = 0x8,
    Full = 0xF,
    Fully = 0xFF // AMD
};

/* L1 Cache and Translation Lookaside Buffer Features (Function 00000002h) */

union x86L1CacheAndTlbFeatures
{
};

/* Intel Deterministic Cache Parameters (Function 00000004h) */

union x86DeterministicCacheInfo
{
    struct
    {
        // eax
        uint32_t cacheType: 5;                              // bits 4:0
        uint32_t level: 3;                                  // bits 7:5
        uint32_t selfInitializing: 1;                       // bit 8
        uint32_t fullyAssociative: 1;                       // bit 9
        uint32_t reserved: 4;                               // bits 13:10
        uint32_t maxAddressableIdsForLogicalProcessors: 12; // bits 25:14;
        uint32_t maxAddressableIdsForProcessorCores: 6;     // bits 31:26
        // ebx
        uint32_t systemCoherencyLineSize: 12;               // bits 11:0
        uint32_t physicalLinePartitions: 10;                // bits 21:12
        uint32_t associativity: 10;                         // bits 31:22
        // ecx
        uint32_t numSets: 32;                               // bits 31:0
        // edx
        uint32_t writeBackInvalidate: 1;                    // bit 0
        uint32_t inclusiveness: 1;                          // bit 1
        uint32_t complexCacheIndexing: 1;                   // bit 2
        uint32_t reserved2: 29;                             // bits 31:3
    };

    struct
    {
        int32_t reg[4];
    };
};

/* AMD L1 Cache and Translation Lookaside Buffer Features (Function 80000005h) */

union x86L1CacheAndTlbFeaturesAMD
{
    struct
    {
        struct L1Tlb
        {
            uint32_t instructionNumEntries: 8;      // bits 7:0
            uint32_t instructionAssociativity: 8;   // bits 15:8
            uint32_t dataNumEntries: 8;             // bits 23:16
            uint32_t dataAssociativity: 8;          // bits 31:24
        } tlb2And4M, tlb4K;

        struct L1Cache
        {
            uint32_t lineSize: 8;                   // In bytes
            uint32_t linesPerTag: 8;
            uint32_t associativity: 8;              // x86CacheAssociativity
            uint32_t cacheSize: 8;                  // In kilobytes
        } dataCache, instructionCache;
    };

    struct
    {
        uint32_t eax, ebx, ecx, edx;
    };
};

/* Thermal Power Management (Function 00000006h) */

union x86ThermalPowerManagementFeatures
{
    struct
    {
        uint32_t digitalThermalSensor: 1;           // DTS
        uint32_t turboBoost: 1;                     // Intel Turbo Boost
        uint32_t alwaysRunningApicTimer: 1;         // ARAT
        uint32_t reserved: 1;
        uint32_t powerLimitNotification: 1;         // PLN
        uint32_t extendedClockModulationDuty: 1;    // ECMD
        uint32_t packageTermalManagement: 1;        // PTM
        uint32_t reserved2: 25;                     // bits 31:7

        uint32_t numIterruptThresholds: 4;          // bit 3:0
        uint32_t reserved3: 28;                     // bits 31:4

        uint32_t hardwareCoordinationFeedback: 1;   // bit 0
        uint32_t acnt2: 1;                          // bit 1
        uint32_t reserved4: 1;                      // bit 2
        uint32_t performanceEnergyBias: 1;          // bit 3
        uint32_t reserved5: 28;                     // bits 31:4
    };

    struct
    {
        uint32_t eax, ebx, ecx;
    };
};

/* AMD Thermal Power Management (Function 00000006h) */

union x86ThermalPowerManagementFeaturesAMD
{
    struct
    {
        uint32_t reserved: 1;                       // bit 0
        uint32_t reserved1: 1;                      // bit 1
        uint32_t alwaysRunningApicTimer: 1;         // bit 2        ARAT
        uint32_t reserved2: 29;                     // bits 31:3
        uint32_t reserved3: 32;                     // bits 31:0
        uint32_t effectiveFrequencyInterface: 1;    // bit 0
        uint32_t reserved4: 31;                     // bits 31:1
    };

    struct
    {
        uint32_t eax, ebx, ecx;
    };
};

/* Extended L2 Cache Features (Function 80000006h) */

union x86L2CacheFeatures
{
    struct
    {
        uint32_t lineSize: 8;               // In bytes
        uint32_t reserved: 4;
        uint32_t associativity: 4;          // x86CacheAssociativity
        uint32_t cacheSize: 16;             // In kilobytes
    };

    uint32_t ecx;
};

/* x86 CPU description. */

struct x86ProcessorInfo
{
    char vendor[12 + 1];
    char brand[48];
    x86VendorId vendorId;
    x86ProcessorSignature signature;
    x86ProcessorMiscInfo misc;
    x86ProcessorFeatures features;
    x86ProcessorFeaturesAMD featuresAMD;
    x86ProcessorFeaturesEx extendedFeatures;
    union
    {
        x86ThermalPowerManagementFeatures tpmFeatures;
        x86ThermalPowerManagementFeaturesAMD tpmFeaturesAMD;
    };
    union
    {
        x86L1CacheAndTlbFeatures l1Cache;
        x86L1CacheAndTlbFeaturesAMD l1CacheAMD;
    };
    x86L2CacheFeatures l2Cache;
    std::vector<x86DeterministicCacheInfo> cacheInfos;
};

/* */

x86ProcessorInfo getProcessorInfo();
uint32_t getProcessorPhysicalThreadCount() noexcept;
