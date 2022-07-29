#include "Query.hpp"

std::string Query::ProtectionType( MEMORY_BASIC_INFORMATION mInfo, PROTECTION_TYPE protType ) {
    switch ( protType ) {
        case DEFAULT:
            if ( !mInfo.Protect )
                return "Unable to parse protection";

            // Only check these two protection types because its the only two we check
            switch ( mInfo.Protect ) {
                case PAGE_READONLY:
                    return "R";
                    break;

                case PAGE_EXECUTE_READWRITE:
                    return "RWX";
                    break;
            }
            break;

        case INITIAL:
            if ( !mInfo.AllocationProtect )
                return "Unable to parse initial protection";

            // Only check these two protection types because its the only two we check
            switch ( mInfo.AllocationProtect ) {
                case PAGE_READONLY:
                    return "R";
                    break;

                case PAGE_EXECUTE_READWRITE:
                    return "RWX";
                    break;
            }
            break;
    }
}