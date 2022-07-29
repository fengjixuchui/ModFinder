#pragma once

#include "../Globals/Include.hpp"

enum PROTECTION_TYPE {
    DEFAULT = 0,
    INITIAL
};

namespace Query {
    void MemoryRegions( std::string processToQuery );
    std::string ProtectionType( MEMORY_BASIC_INFORMATION mInfo, PROTECTION_TYPE protType );
    void NativeAddresses( std::string processToQuery );

    inline std::vector<void*>suspect;
    inline std::vector<void*>linked;
}