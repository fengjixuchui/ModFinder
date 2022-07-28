#include "Query.hpp"

void Query::MemoryRegions(std::string processToQuery)
{
    IMAGE_DOS_HEADER dosHeader = { 0 };
    MEMORY_BASIC_INFORMATION memInfo = { 0 };

    const HANDLE processHandle = Process::GetHandle(processToQuery.c_str());
    const HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    uintptr_t currentAddress = 0;
    void* suspectAddress = 0;

    unsigned int addressCount = 0;
    unsigned int totalReadCount = 0;
    unsigned int linkedCount = 0;

    while (VirtualQueryEx(processHandle, (LPCVOID)currentAddress, &memInfo, sizeof(memInfo)))
    {
        // Don't repeatedly set.
        if (!SetConsoleTitleA("ModFinder | Scanning..."))
            SetConsoleTitleA("ModFinder | Scanning...");

        // Calculation for next address.
        currentAddress = (uintptr_t)memInfo.BaseAddress + memInfo.RegionSize;

        // Ignore 0x0 address or a NULL address.
        if (!memInfo.BaseAddress)
            continue;

        // Ignore any region with a size less than 4Kb.
        if (memInfo.RegionSize < 4096)
            continue;

        // Ignore non private regions.
        // NOTE -> Manual-mapped modules are ALWAYS going to have a private type.
        if (memInfo.Type != MEM_PRIVATE)
            continue;

        bool linkedAddressFound = false;

        // Loop through linked dll address count.
        for (unsigned int i = 0; i < linked.size(); i++)
        {
            linkedAddressFound = memInfo.BaseAddress == linked[i] ? true : false;

            // If we found a linked address, add to the counter.
            if (linkedAddressFound)
                linkedCount++;
        }

        // Ignore addresses that are created natively from the process.
        if (linkedAddressFound)
            continue;

        // Start counting valid reads from here.
        totalReadCount++;

        // Enumerate addresses for the DOS header.
        ReadProcessMemory(Process::GetHandle(processToQuery.c_str()), memInfo.BaseAddress, &dosHeader, sizeof(dosHeader), NULL);

        bool hasValidDosHeader = dosHeader.e_magic == IMAGE_DOS_SIGNATURE;

        // Initial protection is ERW && current protection is R = typically mapped code.
        // Initial protection is ERW && current protection is ERW = typically mapped code.
        if (memInfo.AllocationProtect == PAGE_EXECUTE_READWRITE && memInfo.Protect == PAGE_READONLY || memInfo.AllocationProtect == PAGE_EXECUTE_READWRITE && memInfo.Protect == PAGE_EXECUTE_READWRITE)
        {
            addressCount++;

            std::cout << "\n0x" << std::hex << memInfo.BaseAddress << "\n";
            std::cout << "  |_ Region size:       " << "0x" << std::hex << memInfo.RegionSize << " (" << std::dec << memInfo.RegionSize << ")" << "\n";
            std::cout << "  |_ Initial rights:    " << GetProtectionType(memInfo, PROTECTION_TYPE::INITIAL_PROTECT) << "\n";
            std::cout << "  |_ Current rights:    " << GetProtectionType(memInfo, PROTECTION_TYPE::DEFAULT) << "\n";
            std::cout << "  |_ DOS header:        ";

            if (hasValidDosHeader)
            {
                // Set to current looped address.
                suspectAddress = memInfo.BaseAddress;

                // Append current suspect address to array.
                suspect.push_back(suspectAddress);

                // Green
                SetConsoleTextAttribute(consoleHandle, 10);

                printf("True\n");

                // Normal
                SetConsoleTextAttribute(consoleHandle, 7);
            }
            else
                printf("False\n");
            
            std::cout << "__________________________________________" << "\n";
        }
    }

    SetConsoleTitleA("ModFinder | Finished");

    std::cout << "\nSummary\n";
    std::cout << "  |_ Address count:     " << addressCount << "\n";
    std::cout << "  |_ Checked count:     " << totalReadCount << "\n";
    std::cout << "  |_ Linked count:      " << linkedCount << "\n";
    std::cout << "  |_ Suspicious:        ";

    for (unsigned int i = 0; i < suspect.size(); i++)
    {
        std::cout << "0x" << suspect[i];

        // Seperate when the value is less then max - 1.
        if (i != suspect.size() - 1)
            std::cout << ", ";
    }

    std::cout << "\n";

    // Prevent auto closing.
    std::cin.get();
}