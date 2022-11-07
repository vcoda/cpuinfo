#include <functional>
#include "cpuInfox86.h"
#include "printUtils.h"

std::string booleanString(uint32_t value)
{
    return value ? "Yes" : "No";
}

void printProcessorSignature(const x86ProcessorSignature& signature)
{
    printLn("Stepping", signature.steppingId);
    printLn("Model", signature.model);
    printLn("Family", signature.familyId);
    printLn("Processor type", signature.processorType);
    printLn("Extended model ID", signature.extendedModelId);
    printLn("Extended family ID", signature.extendedFamilyId);
}

void printProcessorMiscInfo(const x86ProcessorMiscInfo& info, bool isIntel)
{
    printLn("Brand ID", info.brandIndex);
    printLn("Cache line flush size", info.cacheLineFlushSize);
    if (isIntel)
        printLn("Max addressable IDs for logical processors", info.maxAddressableIdsForLogicalProcessors);
    printLn("Number of physical threads", getProcessorPhysicalThreadCount());
    printLn("Default APIC ID", info.defaultApicId);
}

void printProcessorFeatures(const x86ProcessorFeatures& features)
{
    printLn("FPU", booleanString(features.floatingPointUnit));
    printLn("VME", booleanString(features.virtualModeExtensions));
    printLn("Debugging Extensions", booleanString(features.debuggingExtensions));
    printLn("Page Size Extension", booleanString(features.pageSizeExtension));
    printLn("Timestamp Counter", booleanString(features.timestampCounter));
    printLn("Model Specific Registers", booleanString(features.modelSpecificRegisters));
    printLn("PAE", booleanString(features.physicalAddressExtension));
    printLn("Machine Check Exception", booleanString(features.machineCheckException));
    printLn("Compare And Exchange 8-bit", booleanString(features.compareAndExchange8));
    printLn("APIC", booleanString(features.advancedProgrammableInterruptController));
    printLn("SysEnter/SysExit", booleanString(features.sysEnterSysExit));
    printLn("Memory Type Range Registers", booleanString(features.memoryTypeRangeRegisters));
    printLn("Page Global Enable", booleanString(features.pageGlobalEnable));
    printLn("Machine Check Architecture", booleanString(features.machineCheckArchitecture));
    printLn("Conditional Move", booleanString(features.conditionalMove));
    printLn("Page Attribute Table", booleanString(features.pageAttributeTable));
    printLn("Page Size Extension 36-bit", booleanString(features.pageSizeExtension36Bit));
    printLn("Processor Serial Number", booleanString(features.processorSerialNumber));
    printLn("Cache Line Flush", booleanString(features.cacheLineFlush));
    printLn("Debug Store", booleanString(features.debugStore));
    printLn("ACPI", booleanString(features.advancedConfigurationAndPowerInterface));
    printLn("MMX", booleanString(features.multiMediaExtension));
    printLn("FXSAVE/FXRESTOR", booleanString(features.fxSaveRestore));
    printLn("SSE", booleanString(features.streamingSimdExtensions));
    printLn("SSE2", booleanString(features.streamingSimdExtensions2));
    printLn("Self Snoop", booleanString(features.selfSnoop));
    printLn("Hyper Threading", booleanString(features.hyperThreading));
    printLn("Thermal Monitor", booleanString(features.thermalMonitor));
    printLn("IA64 Processor", booleanString(features.ia64Processor));
    printLn("Pending Break Enable", booleanString(features.pendingBreakEnable));
    printLn("SSE3", booleanString(features.streamingSimdExtensions3));
    printLn("Carry Less Multiplication", booleanString(features.carryLessMultiplication));
    printLn("Debug Trace And Emon Store 64-bit", booleanString(features.debugTraceAndEmonStore64));
    printLn("Monitor", booleanString(features.monitor));
    printLn("CPL Qualified Debug Store", booleanString(features.debugStoreCplQualified));
    printLn("VMX", booleanString(features.virtualMachineExtensions));
    printLn("SMX", booleanString(features.saferModeExtensions));
    printLn("Enhanced Speed Step", booleanString(features.enhancedSpeedStep));
    printLn("Thermal Monitor 2", booleanString(features.thermalMonitor2));
    printLn("Supplemental SSE3", booleanString(features.supplementalStreamingSimdExtensions3));
    printLn("Context ID", booleanString(features.contextId));
    printLn("Silicon Debug Interface", booleanString(features.siliconDebugInterface));
    printLn("FMA", booleanString(features.fusedMultiplyAdd));
    printLn("Compare And Exchange 16-bit", booleanString(features.compareAndExchange16));
    printLn("Task Priority Messages", booleanString(features.taskPriorityMessages));
    printLn("Performance And Debug Capability", booleanString(features.performanceAndDebugCapability));
    printLn("Processor Context Identifiers", booleanString(features.processorContextIdentifiers));
    printLn("Direct Cache Access", booleanString(features.directCacheAccess));
    printLn("SSE 4.1", booleanString(features.streamingSimdExtensions4_1));
    printLn("SSE 4.2", booleanString(features.streamingSimdExtensions4_2));
    printLn("X2 APIC", booleanString(features.advancedProgrammableInterruptController2));
    printLn("Move Big Endian", booleanString(features.moveBigEndian));
    printLn("Population Count", booleanString(features.popCount));
    printLn("Timestamp Counter Deadline", booleanString(features.timestampCounterDeadline));
    printLn("AES", booleanString(features.advancedEncryptionStandard));
    printLn("XSAVE/XRESTOR", booleanString(features.xsaveRestore));
    printLn("OS XSAVE", booleanString(features.operatingSystemXSaveRestore));
    printLn("AVX", booleanString(features.advancedVectorExtensions));
    printLn("F16C", booleanString(features.f16C));
    printLn("Random Number Generator", booleanString(features.readRandom));
    printLn("Hypervisor", booleanString(features.hypervisor));
}

void printProcessorFeatures(const x86ProcessorFeaturesAMD& features)
{
    printLn("FPU", booleanString(features.floatingPointUnit));
    printLn("VME", booleanString(features.virtualModeExtensions));
    printLn("Debugging Extensions", booleanString(features.debuggingExtensions));
    printLn("Page Size Extension", booleanString(features.pageSizeExtension));
    printLn("Timestamp Counter", booleanString(features.timestampCounter));
    printLn("Model Specific Registers", booleanString(features.modelSpecificRegisters));
    printLn("PAE", booleanString(features.physicalAddressExtension));
    printLn("Machine Check Exception", booleanString(features.machineCheckException));
    printLn("Compare And Exchange 8-bit", booleanString(features.compareAndExchange8));
    printLn("APIC", booleanString(features.advancedProgrammableInterruptController));
    printLn("SYSCALL/SYSRET", booleanString(features.sysCallSysRet));
    printLn("Memory Type Range Registers", booleanString(features.memoryTypeRangeRegisters));
    printLn("Page Global Extension", booleanString(features.pageGlobalExtension));
    printLn("Machine Check Architecture", booleanString(features.machineCheckArchitecture));
    printLn("Conditional Move", booleanString(features.conditionalMove));
    printLn("Page Attribute Table", booleanString(features.pageAttributeTable));
    printLn("Page Size Extensions 36-bit", booleanString(features.pageSizeExtensions36Bit));
    printLn("Multi-Processor Capable", booleanString(features.multiprocessorCapable));
    printLn("No-execute Page Protection", booleanString(features.noExecutePageProtection));
    printLn("Extended MMX", booleanString(features.extendedMmx));
    printLn("MMX", booleanString(features.multiMediaExtension));
    printLn("FXSAVE/FXRSTOR", booleanString(features.fxSaveRestore));
    printLn("FXSAVE/FXRSTOR Optimization", booleanString(features.fxSaveRestoreOptimization));
    printLn("One Gigabyte Page", booleanString(features.oneGigabytePage));
    printLn("Read Timestamp Counter", booleanString(features.readTimestampCounter));
    printLn("Long mode", booleanString(features.longMode));
    printLn("3DNow!", booleanString(features._3DNow));
    printLn("Extended 3DNow!", booleanString(features.extended3DNow));
    printLn("Load/Store AH Flags Legacy Mode", booleanString(features.loadStoreAhFlagsLegacyMode));
    printLn("Core Multi-processing Legacy Mode", booleanString(features.coreMultiProcessingLegacyMode));
    printLn("Secure Virtual Machine", booleanString(features.secureVirtualMachine));
    printLn("Extended APIC Space", booleanString(features.extendedApicSpace));
    printLn("AltMov CR8", booleanString(features.altMovCr8));
    printLn("Advanced Bit Manipulation", booleanString(features.advancedBitManipulation));
    printLn("SSE 4a", booleanString(features.streamingSimdExtensions4a));
    printLn("Misaligned SSE Mode", booleanString(features.misalignedSseMode));
    printLn("3D Now! Prefetch", booleanString(features.prefetch3DNow));
    printLn("OS Visible Workaround", booleanString(features.operatingSystemVisibleWorkaround));
    printLn("Instruction Based Sampling", booleanString(features.instructionBasedSampling));
    printLn("Extended Operation", booleanString(features.extendedOperation));
    printLn("Security Kernel", booleanString(features.securityKernel));
    printLn("Watchdog Timer", booleanString(features.watchdogTimer));
    printLn("Lightweight Profiling", booleanString(features.lightweightProfiling));
    printLn("FMA4", booleanString(features.fusedMultiplyAdd4));
    printLn("Translation Cache Extension", booleanString(features.translationCacheExtension));
    printLn("NodeID Model Specific Registers", booleanString(features.nodeIdModelSpecificRegisters));
    printLn("Trailing Bit Manipulation", booleanString(features.trailingBitManipulation));
    printLn("Topology Extensions", booleanString(features.topologyExtensions));
    printLn("Core Performance Counter", booleanString(features.corePerformanceCounter));
    printLn("NB Performance Counter ", booleanString(features.nbPerformanceCounter));
    printLn("Data Breakpoint Extensions", booleanString(features.dataBreakpointExtensions));
    printLn("Timestamp Performance Counter", booleanString(features.timestampPerformanceCounter));
    printLn("L2I Cache Performance Counter", booleanString(features.l2InstructionCachePerformanceCounter));
    printLn("MonitorX", booleanString(features.monitorX));
    printLn("Address Mask Extension", booleanString(features.addressMaskExtension));
}

void printExtendedProcessorFeatures(const x86ProcessorFeaturesEx& features)
{
    printLn("FS/GS Base Access", booleanString(features.fsGsBaseAccess));
    printLn("Timestamp Counter Adjust", booleanString(features.timestampCounterAdjust));
    printLn("Software Guard Extensions", booleanString(features.softwareGuardExtensions));
    printLn("Bit Manipulation Instruction Set 1", booleanString(features.bitManipulationInstructionSet1));
    printLn("Hardware Lock Elision", booleanString(features.hardwareLockElision));
    printLn("AVX2", booleanString(features.advancedVectorExtensions2));
    printLn("FPU Data Pointer Exception Only", booleanString(features.fpuDataPointerExceptionOnly));
    printLn("Supervisor Mode Execution Prevention", booleanString(features.supervisorModeExecutionPrevention));
    printLn("Bit Manipulation Instruction Set 2", booleanString(features.bitManipulationInstructionSet2));
    printLn("Enhanced REP/MOVSB/STOSB", booleanString(features.enhancedRepMovsbStosb));
    printLn("Invalidate Process Context Identifier", booleanString(features.invalidateProcessContextIdentifier));
    printLn("Restricted Transactional Memory", booleanString(features.restrictedTransactionalMemory));
    printLn("Resource Director Monitoring", booleanString(features.resourceDirectorMonitoring));
    printLn("FPU CS/DS Deprecated", booleanString(features.fpuCsDsDeprecated));
    printLn("Memory Protection Extensions", booleanString(features.memoryProtectionExtensions));
    printLn("Resource Director Allocation", booleanString(features.resourceDirectorAllocation));
    printLn("AVX512 Foundation", booleanString(features.avx512Foundation));
    printLn("AVX512 Double/Quad Word", booleanString(features.avx512DoubleAndQuadWord));
    printLn("Random Seed", booleanString(features.randomSeed));
    printLn("Add Carry Extensions", booleanString(features.addCarryExtensions));
    printLn("Supervisor Mode Access Prevention", booleanString(features.supervisorModeAccessPrevention));
    printLn("AVX512 Integer FMA", booleanString(features.avx512IntegerFusedMultiplyAdd));
    printLn("PCOMMIT", booleanString(features.persistentCommit));
    printLn("Cache Line Flush Opt", booleanString(features.cacheLineFlushOpt));
    printLn("Cache Line Write Back", booleanString(features.cacheLineWriteBack));
    printLn("Processor Trace", booleanString(features.processorTrace));
    printLn("AVX512 Prefetch", booleanString(features.avx512Prefetch));
    printLn("AVX512 Exponential And Reciprocal", booleanString(features.avx512ExponentialAndReciprocal));
    printLn("AXV512 Conflict Detection", booleanString(features.avx512ConflictDetection));
    printLn("SHA", booleanString(features.secureHashAlgorithm));
    printLn("AVX512 Byte/Word", booleanString(features.avx512ByteAndWord));
    printLn("AVX512 Vector Length", booleanString(features.avx512VectorLength));
    printLn("Prefetch/Write T1", booleanString(features.prefetchWriteT1));
    printLn("AVX512 Vector Bit Manipulation Instructions", booleanString(features.avx512VectorBitManipulationInstructions));
    printLn("User Mode Instruction Prevention", booleanString(features.userModeInstructionPrevention));
    printLn("Protection Keys For User Mode Pages", booleanString(features.protectionKeysForUserModePages));
    printLn("PKU Enables by OS", booleanString(features.operatingSystemEnabledPku));
    printLn("User Level Monitor Wait", booleanString(features.userLevelMonitorWait));
    printLn("AVX512 Vector Bit Manipulation Instructions 2", booleanString(features.avx512VectorBitManipulationInstructions2));
    printLn("Control Flow Enforcement Shadow Stack", booleanString(features.controlFlowEnforcementShadowStack));
    printLn("Galois Field Instructions", booleanString(features.galoisFieldInstructions));
    printLn("Vector AES", booleanString(features.vectorAdvancedEncryptionStandard));
    printLn("Vector Carry Less Multiplication", booleanString(features.vectorCarryLessMultiplication));
    printLn("AVX512 Vector Neural Network Instructions", booleanString(features.avx512VectorNeuralNetworkInstructions));
    printLn("AVX512 Bit Algorithms", booleanString(features.avx512BitAlgorithms));
    printLn("Total Memory Encryption", booleanString(features.totalMemoryEncryption));
    printLn("AVX512 Vector Population Count Double/Quad Word", booleanString(features.avx512VectorPopCountDoubleAndQuadWord));
    printLn("Five Level Paging", booleanString(features.fiveLevelPaging));
    printLn("Address Width Adjust", booleanString(features.addressWidthAdjust));
    printLn("Read Processor ID", booleanString(features.readProcessorId));
    printLn("Key Locker", booleanString(features.keyLocker));
    printLn("Bus Lock Detect", booleanString(features.busLockDetect));
    printLn("Cache Line Demote", booleanString(features.cacheLineDemote));
    printLn("Move Double Word Direct Store", booleanString(features.moveDoubleWordDirectStore));
    printLn("Move 64 Bytes Direct Store", booleanString(features.move64BytesDirectStore));
    printLn("Enqueue Stores", booleanString(features.enqueueStores));
    printLn("Software Guard Extensions Launch Configuration", booleanString(features.softwareGuardExtensionsLaunchConfiguration));
    printLn("Protection Keys For Supervisor Mode Pages", booleanString(features.protectionKeysForSupervisorModePages));
    printLn("AVX512 4-register Neural Network Instructions", booleanString(features.avx512NeuralNetworkInstructions4Register));
    printLn("AVX512 4-register FMA Single Precision", booleanString(features.avx512FusedMultiplyAdd4Register));
    printLn("Fast Short REP/MOVSB", booleanString(features.fastShortRepMovsb));
    printLn("User Interprocessor Interrupts", booleanString(features.userInterprocessorInterrupts));
    printLn("AVX512 VP2 Intersect", booleanString(features.avx512Vp2Intersect));
    printLn("Special Register Data Buffer Sampling", booleanString(features.specialRegisterDataBufferSampling));
    printLn("VERW Instruction Clears CPU Buffers", booleanString(features.verwInstructionClearsCpuBuffers));
    printLn("Restricted Transactional Memory Always Abort", booleanString(features.restrictedTransactionalMemoryAlwaysAbort));
    printLn("TSX Force Abort", booleanString(features.tsxForceAbort));
    printLn("Serialize", booleanString(features.serialize));
    printLn("Hybrid Topology", booleanString(features.hybridTopology));
    printLn("TSX Load Address Tracking", booleanString(features.tsxLoadAddressTracking));
    printLn("Platform Configuration", booleanString(features.platformConfiguration));
    printLn("Last Branch Records", booleanString(features.lastBranchRecords));
    printLn("CET Indirect Branch Tracking", booleanString(features.cetIndirectBranchTracking));
    printLn("bfloat16", booleanString(features.bfloat16));
    printLn("AVX512 FP16 Instructions", booleanString(features.avx512HalfPrecisionInstructions));
    printLn("AMX Tile Architecture", booleanString(features.amxTile));
    printLn("AMX 8-bit Integers", booleanString(features.amxInt8));
    printLn("Speculation Control", booleanString(features.speculationControl));
    printLn("Single Thread Indirect Branch Predictor", booleanString(features.singleThreadIndirectBranchPredictor));
    printLn("Level1 Data Cache Flush", booleanString(features.l1DCacheFlush));
    printLn("Architeture Capabilities", booleanString(features.architetureCapabilities));
    printLn("Model-Specific Core Capabilities", booleanString(features.coreCapabilities));
    printLn("Speculative Store Bypass Disable", booleanString(features.speculativeStoreBypassDisable));
}

void printThermalPowerManagementFeatures(const x86ThermalPowerManagementFeatures& features, bool isAMD)
{
    if (isAMD)
    {
        printLn("Always Running APIC Timer", booleanString(features.amd.alwaysRunningApicTimer));
        printLn("Effective Frequency Interface", booleanString(features.amd.effectiveFrequencyInterface));
    }
    else
    {
        printLn("Digital Thermal Sensor", booleanString(features.digitalThermalSensor));
        printLn("Intel Turbo Boost", booleanString(features.turboBoost));
        printLn("Always Running APIC Timer", booleanString(features.alwaysRunningApicTimer));
        printLn("Power Limit Notification", booleanString(features.powerLimitNotification));
        printLn("Extended Clock Modulation Duty", booleanString(features.extendedClockModulationDuty));
        printLn("Package Thermal Management", booleanString(features.packageTermalManagement));
        printLn("Number of Interrupt Thresholds", booleanString(features.numIterruptThresholds));
        printLn("Hardware Coordination Feedback", booleanString(features.hardwareCoordinationFeedback));
        printLn("APERF Counter", booleanString(features.acnt2));
        printLn("Performance/Energy Bias", booleanString(features.performanceEnergyBias));
    }
}

void printAdvancedPowerManagementFeatures(const x86AdvancedPowerManagementFeatures& features, bool isAMD)
{
    if (isAMD)
    {
        printLn("Temperature Sensor", booleanString(features.amd.temperatureSensor));
        printLn("Frequency ID Control", booleanString(features.amd.frequencyIdControl));
        printLn("Voltage ID Control", booleanString(features.amd.voltageIdControl));
        printLn("Thermal Trip", booleanString(features.amd.thermalTrip));
        printLn("Hardware Thermal Control", booleanString(features.amd.hardwareThermalControl));
        printLn("100 MHz Multiplier Control", booleanString(features.amd.oneHundredMhzStep));
        printLn("Hardware P-state Control", booleanString(features.amd.hardwarePstateControl));
        printLn("Invariant Timestamp Counter", booleanString(features.amd.invariantTimestampCounter));
        printLn("Core Performance Boost", booleanString(features.amd.corePerformanceBoost));
        printLn("Read-only Effective Frequency Interface", booleanString(features.amd.readOnlyEffectiveFrequencyInterface));
        printLn("Processor Feedback Interface", booleanString(features.amd.processorFeedbackInterface));
        printLn("Processor Power Reporting Interface", booleanString(features.amd.processorPowerReporting));
    }
    else
    {
        printLn("Invariant Timestamp Counter", booleanString(features.invariantTimestampCounter));
    }
}

const char *stringifyCacheType(uint8_t type)
{
    switch ((x86CacheType)type)
    {
    case x86CacheType::Data: return "Data";
    case x86CacheType::Instruction: return "Instruction";
    case x86CacheType::Unified: return "Unified";
    default: return "Null";
    }
}

const char *stringifyCacheAssociativity(uint8_t associativity)
{
    switch ((x86CacheAssociativity)associativity)
    {
    case x86CacheAssociativity::Reserved: return "Reserved";
    case x86CacheAssociativity::DirectMapped: return "Direct mapped";
    case x86CacheAssociativity::TwoWay: return "2-way";
    case x86CacheAssociativity::FourWay: return "4-way";
    case x86CacheAssociativity::SixWay: return "6-way";
    case x86CacheAssociativity::EightWay: return "8-way";
    case x86CacheAssociativity::TwelveWay: return "12-way";
    case x86CacheAssociativity::SixteenWay: return "16-way";
    case x86CacheAssociativity::Full:
    case x86CacheAssociativity::Fully:
        return "Fully associative";
    default: return "Unknown";
    }
}

const char *stringifyIntegerCacheAssociativity(uint8_t associativity)
{
    switch (associativity)
    {
    case 1: return "Direct mapped";
    case 2: return "2-way";
    case 4: return "4-way";
    case 6: return "6-way";
    case 8: return "8-way";
    case 12: return "12-way";
    case 16: return "16-way";
    default: return "Unknown";
    }
}

void printDeterministicCacheInfo(const x86DeterministicCacheInfo& cache)
{
    std::cout << stringifyCacheType(cache.cacheType) << " cache: " << std::endl << std::endl;
    printLn("System coherency line size", cache.systemCoherencyLineSize);
    printLn("Physical line partitions", cache.physicalLinePartitions);
    printLn("Associativity", stringifyIntegerCacheAssociativity(cache.associativity));
    printLn("Number of sets", cache.numSets);
    printString("");
    printLn("Self initializing", booleanString(cache.selfInitializing));
    printLn("Fully associative", booleanString(cache.fullyAssociative));
    printLn("Write-back invalidate/invalidate", booleanString(cache.writeBackInvalidate));
    printLn("Cache inclusiveness", booleanString(cache.inclusiveness));
    printLn("Complex cache indexing", !cache.complexCacheIndexing ? "Direct mapped" : "Complex function");

    const uint32_t cacheSizeInBytes = cache.associativity * cache.physicalLinePartitions *
        cache.systemCoherencyLineSize * cache.numSets;

    printString("");
    printLn("Cache size in kilobytes", cacheSizeInBytes/1024);
}

void printLevel1CacheAndTlbFeatures(const x86L1CacheAndTlbFeatures& l1Cache)
{
}

void printLevel1CacheAndTlbFeatures(const x86L1CacheAndTlbFeaturesAMD& l1Cache)
{
    printString("2MB and 4MB pages:\n");
    printLn("Instruction TLB entries", l1Cache.tlb2And4M.instructionNumEntries);
    printLn("Instruction TLB associativity", stringifyCacheAssociativity(l1Cache.tlb2And4M.instructionAssociativity));
    printLn("Data TLB entries", l1Cache.tlb2And4M.dataNumEntries);
    printLn("Data TLB associativity", stringifyCacheAssociativity(l1Cache.tlb2And4M.dataAssociativity));

    printString("\n4KB pages:\n");
    printLn("Instruction TLB entries", l1Cache.tlb4K.instructionNumEntries);
    printLn("Instruction TLB associativity", stringifyCacheAssociativity(l1Cache.tlb4K.instructionAssociativity));
    printLn("Data TLB entries", l1Cache.tlb4K.dataNumEntries);
    printLn("Data TLB associativity", stringifyCacheAssociativity(l1Cache.tlb4K.dataAssociativity));

    printString("\nData cache:\n");
    printLn("Cache line size in bytes", l1Cache.dataCache.lineSize);
    printLn("Cache lines per tag", l1Cache.dataCache.linesPerTag);
    printLn("Associativity", stringifyCacheAssociativity(l1Cache.dataCache.associativity));
    printLn("Cache size in kilobytes", l1Cache.dataCache.cacheSize);

    printString("\nInstruction cache:\n");
    printLn("Cache line size in bytes", l1Cache.instructionCache.lineSize);
    printLn("Cache lines per tag", l1Cache.instructionCache.linesPerTag);
    printLn("Associativity", stringifyCacheAssociativity(l1Cache.instructionCache.associativity));
    printLn("Cache size in kilobytes", l1Cache.instructionCache.cacheSize);
}

void printLevel2CacheFeatures(const x86L2CacheFeatures& l2Cache)
{
    printLn("Cache line size", l2Cache.lineSize);
    printLn("Associativity", stringifyCacheAssociativity(l2Cache.associativity));
    printLn("Cache size in kilobytes", l2Cache.cacheSize);
}

void forEachCacheLevel(uint32_t level, const x86ProcessorInfo& info,
    std::function<void(const x86DeterministicCacheInfo& cacheInfo)> cbFn)
{
    for (const auto& cache: info.cacheInfos)
    {
        if (cache.level == level)
            cbFn(cache);
    }
}

int main()
{
    std::cout << "Processor information utility v. 1.0" << std::endl;

    const x86ProcessorInfo info = getProcessorInfo();
    printHeading("Processor Vendor");
    std::cout << "Vendor: " << info.vendor << std::endl;
    std::cout << "Brandname: " << info.brand << std::endl;

    printHeading("Processor Signature");
    setFieldWidth(25);
    printProcessorSignature(info.signature);

    printHeading("Processor Misc Information");
    setFieldWidth(45);
    printProcessorMiscInfo(info.misc, (x86VendorId::Intel == info.vendorId));

    printHeading("Processor Features");
    setFieldWidth(35);
    const bool isAMD = (x86VendorId::AMD == info.vendorId);
    if (isAMD)
        printProcessorFeatures(info.featuresAMD);
    else
        printProcessorFeatures(info.features);

    printHeading("Extended Processor Features");
    setFieldWidth(50);
    printExtendedProcessorFeatures(info.extendedFeatures);

    printHeading("Thermal Power Management Features");
    printThermalPowerManagementFeatures(info.tpmFeatures, isAMD);

    printHeading("Advanced Power Management Features");
    printAdvancedPowerManagementFeatures(info.apmFeatures, isAMD);

    printHeading("L1 Cache Identifiers");
    setFieldWidth(35);
    if (isAMD)
        printLevel1CacheAndTlbFeatures(info.l1CacheAMD);
    else
        printLevel1CacheAndTlbFeatures(info.l1Cache);
    forEachCacheLevel(1, info,
        [](const x86DeterministicCacheInfo& cache)
        {
            printString("");
            printDeterministicCacheInfo(cache);
        });

    printHeading("L2 Cache Identifiers");
    forEachCacheLevel(2, info,
        [](const x86DeterministicCacheInfo& cache)
        {
            printDeterministicCacheInfo(cache);
            printString("");
        });
    printLevel2CacheFeatures(info.l2Cache);

    printHeading("L3 Cache Identifiers");
    forEachCacheLevel(3, info,
        [](const x86DeterministicCacheInfo& cache)
        {
            printDeterministicCacheInfo(cache);
        });

    return 0;
}
