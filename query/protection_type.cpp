#include "query.hpp"

std::string query::current_protection_type( MEMORY_BASIC_INFORMATION memory_info, PROTECTION_TYPE protection_type )
{
    switch ( protection_type )
    {
    case CURRENT:
        if ( !memory_info.Protect )
            return "Unable to parse current protection";

        switch ( memory_info.Protect )
        {
        case PAGE_NOACCESS:
            return "NA";
            break;

        case PAGE_READONLY:
            return "R";
            break;

        case PAGE_READWRITE:
            return "RW";
            break;

        case PAGE_WRITECOPY:
            return "WC";
            break;

        case PAGE_EXECUTE:
            return "X";
            break;

        case PAGE_EXECUTE_READ:
            return "RX";
            break;

        case PAGE_EXECUTE_READWRITE:
            return "RWX";
            break;

        case PAGE_EXECUTE_WRITECOPY:
            return "WCX";
            break;

        case PAGE_WRITECOMBINE:
            return "WC";
            break;

        case PAGE_GUARD:
            return "G";
            break;

        case PAGE_NOCACHE:
            return "NC";
            break;
        }
        break;

    case INITIAL:
        if ( !memory_info.AllocationProtect )
            return "Unable to parse initial protection";

        switch ( memory_info.AllocationProtect )
        {
        case PAGE_NOACCESS:
            return "NA";
            break;

        case PAGE_READONLY:
            return "R";
            break;

        case PAGE_READWRITE:
            return "RW";
            break;

        case PAGE_WRITECOPY:
            return "WC";
            break;

        case PAGE_EXECUTE:
            return "X";
            break;

        case PAGE_EXECUTE_READ:
            return "RX";
            break;

        case PAGE_EXECUTE_READWRITE:
            return "RWX";
            break;

        case PAGE_EXECUTE_WRITECOPY:
            return "WCX";
            break;

        case PAGE_WRITECOMBINE:
            return "WC";
            break;

        case PAGE_GUARD:
            return "G";
            break;

        case PAGE_NOCACHE:
            return "NC";
            break;
        }
        break;
    }
}