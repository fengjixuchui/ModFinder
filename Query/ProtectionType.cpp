#include "Query.hpp"

std::string Query::ProtectionType(MEMORY_BASIC_INFORMATION mInfo, PROTECTION_TYPE protType)
{
    switch (protType)
    {
        case DEFAULT:
            if (!mInfo.Protect)
                return "Unable to parse current protection";

            switch (mInfo.Protect)
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
            if (!mInfo.AllocationProtect)
                return "Unable to parse initial protection";

            switch (mInfo.AllocationProtect)
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