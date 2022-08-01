#include "query.hpp"

void query::memory_regions(std::string const& process_name) {
    IMAGE_DOS_HEADER dos_header = { 0 };
    MEMORY_BASIC_INFORMATION memory_info = { 0 };

    const HANDLE process_handle = process::get_handle_by_name(process_name.c_str());

    uintptr_t currentAddress = 0;
    void* suspectAddress = nullptr;

    // If we cannot read the process handle, stop here.
    if (!process_handle)
        return;

    // Enumerate all base addresses in the process.
    while (VirtualQueryEx(process_handle, (LPCVOID)currentAddress, &memory_info, sizeof(memory_info))) {
        // Calculation for next address.
        currentAddress = (uintptr_t)memory_info.BaseAddress + memory_info.RegionSize;

        // Ignore 0x0 address or a NULL address.
        if (!memory_info.BaseAddress)
            continue;

        // Ignore non private regions.
        // Manual-mapped regions should always be private.
        if (!(memory_info.Type == MEM_PRIVATE))
            continue;

        // Manual-mapped region state's should always be commit.
        if (!(memory_info.State == MEM_COMMIT))
            continue;

        // Ignore regions that don't contain an initial allocation type of RWX.
        // Manual-mapped regions should always start with this type.
        // Initial cannot be modified, only current.
        if (!(memory_info.AllocationProtect & PAGE_EXECUTE_READWRITE))
            continue;

        // Manual-mapped regions should have at least one of the rights.
        // X, RX, RWX, RW
        if (!(memory_info.Protect & PAGE_EXECUTE || memory_info.Protect & PAGE_EXECUTE_READ ||
            memory_info.Protect & PAGE_EXECUTE_READWRITE || memory_info.Protect & PAGE_READWRITE))
            continue;

        bool is_linked_address_found = false;

        // Loop through linked dll address count.
        for (unsigned int i = 0; i < linked.size(); i++) {
            is_linked_address_found = memory_info.BaseAddress == linked[i];
        }

        // Ignore addresses that are created natively from the process.
        if (is_linked_address_found)
            continue;

        // Enumerate addresses for the DOS header.
        ReadProcessMemory(process_handle, memory_info.BaseAddress, &dos_header, sizeof(dos_header), NULL);

        bool has_dos_header = dos_header.e_magic == IMAGE_DOS_SIGNATURE;

        // Only allow read only pages if the DOS header is found.
        if (memory_info.Protect & PAGE_READONLY && !has_dos_header)
            continue;

        std::cout << "0x" << std::hex << memory_info.BaseAddress << "\n";

        if (has_dos_header) {
            // Set to current looped address.
            suspectAddress = memory_info.BaseAddress;

            // Append current suspect address to array.
            suspect.push_back(suspectAddress);
        }
    }

    // Done.
    std::cout << "\nFinished\n";
    std::cout << "Suspicious: ";

    // Cleanup.
    CloseHandle(process_handle);

    // Enumerate suspect addresses.
    for (std::size_t i = 0; i < suspect.size(); i++) {
        std::cout << "0x" << suspect[i];

        // Seperate when the value is less then max - 1.
        if (i != suspect.size() - 1)
            std::cout << ", ";
    }

    std::cout << "\n";

    // Prevent auto closing.
    std::cin.get();
}