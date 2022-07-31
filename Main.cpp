#include "Globals/Include.hpp"

int main()
{
	SetConsoleTitleA("");

	std::string processName;

	std::cout << "Process name: ";
	std::getline(std::cin, processName);

	if (processName.find(".exe") == std::string::npos)
		processName += ".exe";

	if (HANDLE hHandle = Process::GetHandle(processName.c_str()))
	{
		CloseHandle(hHandle);
		system("cls");
		Query::NativeAddresses(processName);
		Query::MemoryRegions(processName);
	}
	else
	{
		system("cls");
		std::cout << "Unable to parse process\nClosing in 2 seconds\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		exit(0);
	}
}