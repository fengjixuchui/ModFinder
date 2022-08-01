#include "Globals/Include.hpp"

int main() {
	SetConsoleTitleA("");

	std::string processName;

	std::cout << "Process name: ";
	std::getline(std::cin, processName);

	if (processName.find(".exe") == std::string::npos)
		processName += ".exe";

	if (HANDLE process_handle = process::get_handle_by_name(processName.c_str())) {
		CloseHandle(process_handle);
		system("cls");
		query::natively_imported_addresses(processName);
		query::memory_regions(processName);
	}
	else {
		system("cls");
		std::cout << "Unable to parse process\nClosing in 2 seconds\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		exit(0);
	}
}