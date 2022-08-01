#pragma once

#include "../Globals/include.hpp"

enum PROTECTION_TYPE
{
    CURRENT = 0,
    INITIAL
};

namespace query
{
    void memory_regions( std::string const& process_name );
    void natively_imported_addresses( std::string const& process_name );
    std::string current_protection_type( MEMORY_BASIC_INFORMATION memory_info, PROTECTION_TYPE protection_type );

    inline std::vector<void*>suspect;
    inline std::vector<void*>linked;
}