#include <cstdint>
#include <cmath>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <time.h>
#endif

uint64_t waitNanoseconds(uint64_t ns) noexcept
{
    constexpr uint64_t second = 1000000000ull;
#ifdef _WIN32
    uint64_t frequency;
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    uint64_t dt = (uint64_t)std::round(ns/1e+9 * frequency);
    uint64_t start;
    QueryPerformanceCounter((LARGE_INTEGER *)&start);
    uint64_t end = start + dt, now;
    do {
        QueryPerformanceCounter((LARGE_INTEGER *)&now);
    } while (now < end);
    return (now - start) * second/frequency;
#else
    https://github.com/z4ziggy/nanodelay
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    uint64_t dt = 0;
    while (dt < ns)
    {
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        dt = now.tv_nsec - start.tv_nsec;
        if (now.tv_sec > start.tv_sec)
            dt += 1000000000ull;
    }
    return dt;
#endif
}
