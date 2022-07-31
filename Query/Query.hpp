#pragma once

#include "../Globals/Include.hpp"

enum PROTECTION_TYPE
{
    DEFAULT = 0,
    INITIAL
};

namespace Query
{
    void MemoryRegions(std::string const& processToQuery);
    void NativeAddresses(std::string const& processToQuery);
    std::string ProtectionType(MEMORY_BASIC_INFORMATION mInfo, PROTECTION_TYPE protType);

    inline std::vector<void*>suspect;
    inline std::vector<void*>linked;
}