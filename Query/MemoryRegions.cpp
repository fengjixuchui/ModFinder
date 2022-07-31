#include "Query.hpp"

void Query::MemoryRegions(std::string const& processToQuery)
{
    IMAGE_DOS_HEADER dosHeader = { 0 };
    MEMORY_BASIC_INFORMATION memInfo = { 0 };

    const HANDLE processHandle = Process::GetHandle(processToQuery.c_str());

    uintptr_t currentAddress = 0;
    void* suspectAddress = nullptr;

    // If we cannot read the process handle, stop here.
    if (!processHandle)
        return;

    // Enumerate all base addresses in the process.
    while (VirtualQueryEx(processHandle, (LPCVOID)currentAddress, &memInfo, sizeof(memInfo)))
    {
        // Calculation for next address.
        currentAddress = (uintptr_t)memInfo.BaseAddress + memInfo.RegionSize;

        // Ignore 0x0 address or a NULL address.
        if (!memInfo.BaseAddress)
            continue;

        // Ignore non private regions.
        // Manual-mapped regions should always be private.
        if (!(memInfo.Type == MEM_PRIVATE))
            continue;

        // Manual-mapped region state's should always be commit.
        if (!(memInfo.State == MEM_COMMIT))
            continue;

        // Ignore regions that don't contain an initial allocation type of RWX.
        // Manual-mapped regions should always start with this type.
        // Initial cannot be modified, only current.
        if (!(memInfo.AllocationProtect & PAGE_EXECUTE_READWRITE))
            continue;

        // Manual-mapped regions should have at least one of the rights.
        // X, RX, RWX, RW
        if (!(memInfo.Protect & PAGE_EXECUTE || memInfo.Protect & PAGE_EXECUTE_READ ||
            memInfo.Protect & PAGE_EXECUTE_READWRITE || memInfo.Protect & PAGE_READWRITE))
            continue;

        bool linkedAddressFound = false;

        // Loop through linked dll address count.
        for (unsigned int i = 0; i < linked.size(); i++)
        {
            linkedAddressFound = memInfo.BaseAddress == linked[i];
        }

        // Ignore addresses that are created natively from the process.
        if (linkedAddressFound)
            continue;

        // Enumerate addresses for the DOS header.
        ReadProcessMemory(processHandle, memInfo.BaseAddress, &dosHeader, sizeof(dosHeader), NULL);

        bool hasValidDosHeader = dosHeader.e_magic == IMAGE_DOS_SIGNATURE;

        // Only allow read only pages if the DOS header is found.
        if (memInfo.Protect & PAGE_READONLY && !hasValidDosHeader)
            continue;

        std::cout << "0x" << std::hex << memInfo.BaseAddress << "\n";

        if (hasValidDosHeader)
        {
            // Set to current looped address.
            suspectAddress = memInfo.BaseAddress;

            // Append current suspect address to array.
            suspect.push_back(suspectAddress);
        }
    }

    // Done.
    std::cout << "\nFinished\n";
    std::cout << "Suspicious: ";

    // Cleanup.
    CloseHandle(processHandle);

    // Enumerate suspect addresses.
    for (std::size_t i = 0; i < suspect.size(); i++)
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